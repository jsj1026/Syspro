#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> 

/* 부모 프로세스가 자식 프로세스를 생성하고 끝나기를 기다린다. */
int main()
{
   int pid, child, status;
   printf("[%d] 부모 프로세스 시작 \n", getpid( ));
   pid = fork();
   if (pid == 0) {
      printf("[%d] 자식 프로세스 시작 \n", getpid( ));
      exit(0); // 자식 프로세스 정상 종료를 나타내기 위해 exit(0)을 사용하는 것이 일반적
   }

   // wait 함수의 반환 값 확인
   if ((child = wait(&status)) == -1) {
      perror("wait");
      exit(EXIT_FAILURE);
   }

   printf("[%d] 자식 프로세스 %d 종료 \n", getpid(), child);
   printf("\t종료 코드 %d\n", WEXITSTATUS(status)); // WEXITSTATUS를 사용하여 정확한 종료 코드 출력

   return 0;
}
