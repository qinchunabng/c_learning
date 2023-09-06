#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <string.h>

#define PAT "/etc/a*.conf"

static int errfunc_(const char *,int);

int main(){
    int err,i;
    glob_t globres;

    err = glob(PAT, 0, errfunc_, &globres);
    if(err){
        fprintf(stderr, "Error code = %d\n", err);
        exit(1);
    }

    for(i=0;i<globres.gl_pathc;i++){
        puts(globres.gl_pathv[i]);
    }

    globfree(&globres);
    exit(0);
}

int errfunc_(const char *errpath, int errno){
    fprintf(stderr, "errpath: %s\n", errpath);
    fprintf(stderr, "ERROR MSG: %s\n", strerror(errno));
}