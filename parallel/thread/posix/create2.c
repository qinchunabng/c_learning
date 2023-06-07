#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static void *func(void *p){

}

int main(){
    int i,err;
    pthread_t tid;
    pthread_attr_t attr;

    //init attr
    pthread_attr_init(&attr);
    //set stack size
    pthread_attr_setstacksize(&attr, 1024*1024);

    for(i=0;;i++){
        err = pthread_create(&tid, NULL, func, NULL);
        if(err){
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            break;
        }
    }

    printf("%d\n",i);

    pthread_attr_destroy(&attr);
    exit(0);
}