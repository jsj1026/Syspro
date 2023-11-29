#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // fork 함수를 사용하기 위해 추가

/* 부모 프로세스가 자식 프로세스를 생성하고 서로 다른 메시지를 프린트 */
int main() 
{
   int pid;
   pid = fork();
   if (pid == 0) {   // 자식 프로세스
      printf("[Child] : Hello, world pid=%d\n", getpid());
   }
   else if (pid > 0) {   // 부모 프로세스
      printf("[Parent] : Hello, world pid=%d\n", getpid());
   }
   else {
      perror("fork"); // fork 실패 시 오류 메시지 출력
      return 1; // 에러 코드 반환
   }
   return 0; // main 함수 종료
}
