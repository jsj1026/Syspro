#include <stdio.h>
#define SIZE 100

int main(int argc, char *argv[]){
        FILE *fp1;
        FILE *fp2;
        FILE *fp3;
        int c1, c2, c3;

        if(argc < 2){
                fp1 = stdin;
                fp2 = stdin;
                fp3 = stdin;
        }

        else{
            if((fp1 = fopen(argv[1], "r")) != NULL){
                c1 = getc(fp1);
                while(c1 != EOF){
                        putc(c1, stdout);
                        c1 = getc(fp1);
                }
                fclose(fp1);
         }

         if((fp2 = fopen(argv[2], "r")) != NULL){
                c2 = getc(fp2);
                while(c2 != EOF){
                        putc(c2, stdout);
                        c2 = getc(fp2);
                }
                fclose(fp2);
         }

         if((fp3 = fopen(argv[3], "r")) != NULL){
                c3 = getc(fp3);
                while(c3 != EOF){
                        putc(c3, stdout);
                        c3 = getc(fp3);
                }
                fclose(fp3);
         }
        }

}
