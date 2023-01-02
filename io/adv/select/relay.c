#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <errno.h>

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"

#define BUFSIZE 1024

enum{
    STATE_R=1,
    STATE_W,
    STATE_AUTO,
    STATE_Ex,
    STATE_T
};

struct fsm_st{
    int state;
    int sfd;
    int dfd;
    char buf[BUFSIZE];
    int len;
    int pos;
    char *err;
};



static void fsm_driver(struct fsm_st *fsm){
    int ret;
    switch (fsm->state)
    {
    case STATE_R:
        fsm->len = read(fsm->sfd,fsm->buf, BUFSIZE);
        if(fsm->len == 0)
            fsm->state = STATE_T;
        else if(fsm->len < 0){
            if(errno == EAGAIN){
                fsm->state = STATE_R;
            }else{
                fsm->err = "read()";
                fsm->state = STATE_Ex;
            }
        }else{
            fsm->pos - 0;
            fsm->state = STATE_W;
        }
        break;
    case STATE_W:
        ret = write(fsm->dfd, fsm->buf+fsm->pos, fsm->len);
        if(ret < 0){
            if(errno == EAGAIN){
                fsm->state = STATE_W;
            }else{
                fsm->err = "write()";
                fsm->state = STATE_Ex;
            }
        }else{
            fsm->pos+=ret;
            fsm->len-=ret;
            if(fsm->len - ret == 0) {
                fsm->state = STATE_R;
                // fsm->pos = 0;
            }else{
                fsm->len = fsm->len - ret;
                fsm->state = STATE_W;
            }
        }
        break;
    case STATE_Ex:
        perror(fsm->err);
        fsm->state = STATE_Ex;
        break;
    case STATE_T:
        /* do sth*/
        break;
    default:
        // abrot the process and produce a core dump
        abort();
        break;
    }
}

static int max(int a,int b){
    return a > b ? a : b;
}

static void relay(int fd1, int fd2){
    int fd1_save;
    int fd2_save;
    struct fsm_st fsm12, fsm21;
    fd_set rset,wset;
    fd1_save = fcntl(fd1, F_GETFL);
    fcntl(fd1, F_SETFL, fd1_save|O_NONBLOCK);

    fd2_save = fcntl(fd2, F_GETFL);
    fcntl(fd2, F_SETFL, fd2_save|O_NONBLOCK);

    fsm12.state = STATE_R;
    fsm12.sfd = fd1;
    fsm12.dfd = fd2;

    fsm21.state = STATE_R;
    fsm21.sfd = fd2;
    fsm21.dfd = fd1;

    while(fsm12.state != STATE_T || fsm21.state != STATE_T){
        //arrange monitor task
        FD_ZERO(&rset);
        FD_ZERO(&wset);

        if(fsm12.state == STATE_R){
            FD_SET(fsm12.sfd, &rset);
        }else if(fsm12.state == STATE_W){
            FD_SET(fsm12.dfd, &wset);
        }

        if(fsm21.state == STATE_R){
            FD_SET(fsm21.sfd, &rset);
        }else if(fsm21.state == STATE_W){
            FD_SET(fsm21.dfd, &wset);
        }

        // monitor
        if(fsm12.state < STATE_AUTO || fsm21.state <STATE_AUTO){
            if(select(max(fd1,fd2) + 1, &rset, &wset, NULL, NULL) < 0){
                if(errno == EINTR){
                    continue;
                }
                perror("select()");
                exit(1);
            }
        }

        // inspect monitor result
        if(FD_ISSET(fd1, &rset) || FD_ISSET(fd2, &wset) || fsm12.state > STATE_AUTO){
            fsm_driver(&fsm12);
        }
        if(FD_ISSET(fd2, &rset) || FD_ISSET(fd1, &wset) || fsm21.state > STATE_AUTO){
            fsm_driver(&fsm21);
        }
    }

    fcntl(fd1, F_SETFL, fd1_save);
    fcntl(fd2, F_SETFL, fd2_save);
}

int main(){
    int fd1,fd2;

    fd1 = open(TTY1, O_RDWR);
    if(fd1 < 0){
        perror("open()");
        exit(1);
    }

    fd2 = open(TTY2, O_RDWR|O_NONBLOCK);
    if(fd2 < 0){
        perror("open()");
        exit(1);
    }

    relay(fd1, fd2);

    close(fd1);
    close(fd2);
    exit(0);
}