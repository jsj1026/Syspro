#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char *argv[]){
    FILE *fp1=NULL;
    FILE *fp2=NULL;
    FILE *fp3=NULL;
    char line[SIZE];

    if((fp1=fopen(argv[1], "r"))==NULL){
        printf("file open error1\n");
        exit(1);
    }

    if((fp2=fopen(argv[2], "a"))==NULL){
        printf("file open error2\n");
        exit(1);
    }

    fgets(line,SIZE,fp1);
    fputs(line,fp3);

    fclose(fp1);
    fclose;
}
