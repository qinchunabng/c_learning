#define __GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <linux/sched.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define STACK_SIZE (1024*1024)

static char container_stack[STACK_SIZE];
char * const container_args[]={"/bin/bash",NULL};

int container_main(void* arg){
    printf("Container - inside the container!\n");
    sethostname("container",10);
    execv(container_args[0], container_args);
    printf("something is wrong!\n");
    return -1;
}

int main(){
    int container_id;
    printf("Parent - start a container!\n");

    container_id = clone(container_main, container_stack + STACK_SIZE, CLONE_NEWUTS | SIGCHLD, NULL);
    if(container_id < 0){
        perror("clone()");
        exit(1);
    }
    waitpid(container_id, NULL, 0);
    printf("Parent - container stopped!\n");
    exit(0);
}