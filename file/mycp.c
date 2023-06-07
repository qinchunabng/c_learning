#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc,char *argv[]){
    FILE *fps,*fpd;
    int c;
    char buf[BUFSIZE];

    if(argc < 3){
        fprintf(stderr,"Usage:%s <src_file> <dest_file>\n",argv[0]);
        exit(1);
    }

    fps=fopen(argv[1],"r");
    if(fps==NULL){
        perror("fopen()");
        exit(1);
    }

    fpd=fopen(argv[2],"w");
    if(fpd==NULL){
        //如果目标文件打开失败，记得关闭第一个文件，否则会出现内存泄漏
        fclose(fps);
        perror("fopen()");
        exit(1);
    }
    
    while(fgets(buf,BUFSIZE,fps)!=NULL)
        fputs(buf,fpd);

    fclose(fps);
    fclose(fpd);
    return 0;
}