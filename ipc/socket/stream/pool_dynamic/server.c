#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <sys/mman.h>

#include "proto.h"
#define MINSPARESERVER 5
#define MAXSPARESERVER 10
#define MAXCLIENTS 20
#define SIG_NOTIFY SIGUSR2
#define LINEBUFSIZE 80

enum{
    STATE_IDLE=1,
    STATE_BUSY,
    STATE_OVER
};

struct server_st{
    pid_t pid;
    int state;
};

static struct server_st *server_pool;
static int idle_count=0,busy_count=0;
static int sd;

static void usr2_handler(int s){
    // printf("[%d]%s:%d\n", getpid(), __FUNCTION__, __LINE__);
}

static void server_job(int pos){
    pid_t ppid;
    struct sockaddr_in raddr;
    socklen_t raddr_len;
    int client_sd;
    time_t stamp;
    int len;
    char ipstr[IPSTRSIZE];
    char linebuf[LINEBUFSIZE];
    // ssize_t size;

    ppid = getppid(); 
    raddr_len = sizeof(raddr);
    while(1){
        server_pool[pos].state=STATE_IDLE;
        kill(ppid, SIG_NOTIFY);
        // printf("[%d][%d]%s:%d\n", ppid, getpid(), __FUNCTION__, __LINE__);

        client_sd = accept(sd, (void *)&raddr, &raddr_len);
        if(client_sd < 0){
            if(errno != EINTR || errno != EAGAIN){
                perror("accept()");
                exit(1);
            }
        }
        
        server_pool[pos].state= STATE_BUSY;
        kill(ppid, SIG_NOTIFY);
        inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
        // printf("[%d]client:%s:%d\n", getpid(), ipstr, ntohs(raddr.sin_port));

        stamp = time(NULL);
        len = snprintf(linebuf, LINEBUFSIZE, FMT_STAMP, stamp);
        if(send(client_sd, linebuf, len, 0) < 0){
            perror("send()");
            exit(1);
        }

        // printf("[%d]%s:%d\n", getpid(), __FUNCTION__, __LINE__);
        sleep(1);
        close(client_sd);
    }
}

static int add_1_server(){
    int slot;
    pid_t pid;
    if(idle_count + busy_count >= MAXCLIENTS){
        return -1;
    }
    for(slot=0;slot<MAXCLIENTS;slot++){
        if(server_pool[slot].pid==-1){
            break;
        }
    }

    server_pool[slot].state=STATE_IDLE;
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){   //child process 
        server_job(slot);
        exit(0);
    }else{          //parent process
        server_pool[slot].pid=pid;
        idle_count++;
    }
    return 0;
}

static int del_1_server(){
    int i;
    if(idle_count==0){
        return -1;
    }
    for(i=0;i<MAXCLIENTS;i++){
        if(server_pool[i].pid != -1 && server_pool[i].state == STATE_IDLE){
            kill(server_pool[i].pid, SIGTERM);
            server_pool[i].pid=-1;
            idle_count--;
            break;
        }
    }
    return 0;
}

static int scan_pool(){
    int i;
    int idle=0,busy=0;
    for(i=0;i<MAXCLIENTS;i++){
        if(server_pool[i].pid == -1){
            continue;
        }
        if(kill(server_pool[i].pid, 0)){
            server_pool[i].pid = -1;
            continue;
        }
        if(server_pool[i].state == STATE_IDLE){
            idle++;
        }else if(server_pool[i].state == STATE_BUSY){
            busy++;
        }else{
            fprintf(stderr, "Unknow state.\n");
            //kill current process and produce a core dump.
            abort();
        }
    }
    idle_count=idle;
    busy_count=busy;
    return 0;
}

int main(){
    struct sigaction act,oldact;
    int val;
    struct sockaddr_in laddr;
    sigset_t set,oset;
    int i;

    act.sa_handler=SIG_IGN;
    sigemptyset(&act.sa_mask);
    act.sa_flags=SA_NOCLDWAIT;

    sigaction(SIGCHLD, &act, &oldact);

    act.sa_handler=usr2_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIG_NOTIFY, &act, &oldact);

    sigemptyset(&set);
    sigaddset(&set, SIG_NOTIFY);
    sigprocmask(SIG_BLOCK, &set, &oset);

    server_pool = mmap(NULL, sizeof(struct server_st) * MAXCLIENTS, PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if(server_pool == MAP_FAILED){
        perror("mmap()");
        exit(1);
    }

    for(i=0;i<MAXCLIENTS;i++){
        server_pool[i].pid=-1;
    }

    sd = socket(AF_INET,SOCK_STREAM, 0);
    if(sd < 0){
        perror("socket()");
        exit(1);
    }

    if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val,sizeof(val)) < 0){
        perror("setsockopt()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port=htons(atoi(SERVER_PORT));
    inet_pton(AF_INET,"0.0.0.0", &laddr.sin_addr);

    if(bind(sd,(void *)&laddr, sizeof(laddr)) < 0){
        perror("bind()");
        exit(1);
    }
    
    if(listen(sd, 100) < 0){
        perror("listen()");
        exit(1);
    }

    for(i=0;i<MINSPARESERVER;i++){
        add_1_server();
    }

    while(1){
        // printf("%s:%d\n", __FUNCTION__, __LINE__);
        sigsuspend(&oset);

        // printf("%s:%d\n", __FUNCTION__, __LINE__);
        scan_pool();

        // printf("%s:%d\n", __FUNCTION__, __LINE__);
        //control the pool
        if(idle_count > MAXSPARESERVER){
            for(i=0;i<(idle_count - MAXSPARESERVER);i++){
                del_1_server();
            }
        }else if(idle_count < MINSPARESERVER){
            for(i=0;i<(MINSPARESERVER - idle_count);i++){
                add_1_server();
            }
        }

        // printf("%s:%d\n", __FUNCTION__, __LINE__);
        //print the pool
        for(i=0;i<MAXCLIENTS;i++){
            if(server_pool[i].pid==-1)
                putchar(' ');
            else if(server_pool[i].state == STATE_IDLE)
                putchar('.');
            else
                putchar('x');
        }
        putchar('\n');
    }

    sigprocmask(SIG_SETMASK, &oset, NULL);
    exit(0);
}