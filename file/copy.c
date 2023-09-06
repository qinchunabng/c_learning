#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc,char **argv){
    int sfd,dfd;
    char buf[BUF_SIZE];
    int len,ret,pos;
    if(argc < 3){
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    sfd = open(argv[1],O_RDONLY);
    if(sfd < 0){
        perror("open()");
        exit(1);
    }
    dfd = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0600);
    if(sfd < 0){
        close(sfd);
        perror("open()");
        exit(1);
    }

    while(1){
        len=read(sfd,buf,BUF_SIZE);
        if(len<0){
            perror("read()");
            break;
        }
        if(len==0)
            break;

        pos=0;
        while(len>0){
            ret=write(dfd,buf+pos,len);
            if(ret<0){
                perror("write()");
                exit(1);
            }
            len-=ret;
        }
        
    }

    close(sfd);
    close(dfd);

    exit(0);
}