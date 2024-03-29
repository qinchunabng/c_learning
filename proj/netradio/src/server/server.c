#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>

#include "server_conf.h"
#include <proto.h>
#include "medialib.h"
#include "thr_list.h"
#include "thr_channel.h"

struct server_conf_st server_conf = {.rcvport = DEFAULT_RCVPORT,
                                     .mgroup = DEFAULT_MGROUP,
                                     .media_dir = DEFAULT_MEDIADIR,
                                     .runmode = RUN_DAEMON,
                                     .ifname = DEFAULT_IF};

int serversd;
struct sockaddr_in sndaddr;

static void printhelp(){
    printf("-M   指定多播组\n");
    printf("-P   指定运行端口\n");
    printf("-F   前台运行\n");
    printf("-D   指定媒体库位置\n");
    printf("-I   指定网络设备\n");
    printf("-H   显示帮助\n");
}

static int daemonize(void){
    int fd;
    pid_t pid;
    pid = fork();

    if(pid < 0){
        // perror("fork()");
        syslog(LOG_ERR, "fork():%s",strerror(errno));
        return -1;
    }

    if(pid > 0) // parent process
        exit(0);

    int fd = open("/dev/null", O_RDWR);
    if(fd < 0){
        // perror("open()");
        syslog(LOG_WARNING, "open():%s", strerror(errno));
        return -2;
    }else{
        dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);
        if(fd > 2)
            close(fd);
    }

    setsid();
    chdir("/");
    umask(0);
    return 0;
}

static void daemon_exit(int s){
    closelog();
    exit(0);
}

static int socket_init(){
    struct ip_mreqn mreq;

    serversd = socket(AF_INET, SOCK_DGRAM, 0);
    if(serversd < 0){
        syslog(LOG_ERR, "socket():%s", strerror(errno));
        exit(0);
    }

    inet_pton(AF_INET, server_conf.mgroup, &mreq.imr_multiaddr);
    inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
    mreq.imr_ifindex = if_nametoindex(server_conf.ifname);

    if(setsockopt(serversd, IPPROTO_IP, IP_MULTICAST_IF, &mreq, sizeof(mreq)) < 0){
        syslog(LOG_ERR, "setsockopt():%s", strerror(errno));
    }

    sndaddr.sin_family = AF_INET;
    sndaddr.sin_port = htons(atoi(server_conf.rcvport));
    inet_pton(AF_INET, server_conf.mgroup, sndaddr.sin_addr.s_addr);

    return 0;
}

/**
 * -M   指定多播组
 * -P   指定运行端口
 * -F   前台运行
 * -D   指定媒体库位置
 * -I   指定网络设备
 * -H   显示帮助
 */
int main(int argc, char *argv[])
{
    int c,i;
    struct sigaction sa;
    struct mlib_listentry_st *list;
    int list_size;
    int err;

    sa.sa_handler = daemon_exit;
    sigempty(&sa.sa_mask);
    sigaddset(&sa.sa_mask,SIGINT);
    sigaddset(&sa.sa_mask,SIGQUIT);
    sigaddset(&sa.sa_mask,SIGTERM);

    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);

    openlog("netradio", LOG_PID|LOG_ERROR, LOG_DAEMON);
    /*命令行分析*/
    while(1){
        c = getopt(argc, argv, "M:P:FD:I:H");
        if(c < 0){
            break;
        }
        switch (c)
        {
        case 'M':
            server_conf.mgroup = optarg;
            break;
        case 'P':
            server_conf.rcvport = optarg;
            break;
        case 'F':
            server_conf.runmode = RUN_FOREFEGROUND;
            break;
        case 'D':
            server_conf.media_dir = optarg;
            break;
        case 'I':
            server_conf.ifname = optarg;
            break;
        case 'H':
            printhelp();
            break;
        default:
            abort();
            break;
        }
    }
    

    /*守护进程的实现*/
    if(server_conf.runmode == RUN_DAEMON){
        if(daemonize() != 0)
            exit(1);
    }else if(server_conf.runmode == RUN_FOREFEGROUND){
        //do nothing
    }else{
        // fprintf(stderr , "EINVAL\n");
        syslog(LOG_ERR, "EINVAL server_conf.runmode");
        exit(1);
    }
    /*SOCKET初始化*/
    socket_init();

    /*获取频道信息*/
    err = mlib_getchnlist(&list,&list_ize);
    if(err){

    }
    /*创建节目单线程*/
    thr_list_create(list, list_size);

    /*创建频道线程*/
    for(i=0;i<list_size;i++){
        err = thr_channel_create(list+i); 
        if(err){
            syslog(LOG_ERR, "thr_channel_create():%s", strerror(-err));
            exit(1);
        }
    }

    syslog(LOG_DEBUG, "%d channel threads created.", i);
    
    while (1)
        pause();

    closelog();

    exit(0);
}