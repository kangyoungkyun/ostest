#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//자식 프로세스 생성 이후에 호출 되는 함수
void afterFork(void)
{
 	printf("이 함 수를 실행 시킨 프로세스는(pid) : %d \n", getpid());

}


int main(int argc, char **argv)
{

	printf("fork 함수 예제 시작 ! \n");

	pid_t pid;

	
	printf("현재 프로세스 pid : %d \n", getpid());

	//자식 프로세스 생성
	pid = fork();
	
	//pid 가 0 이면 자식 프로세스이다.
	if(pid == 0){	
		
		printf("자식 프로세스 pid : %d\n ", getpid());

	//pid 가 0이 아니면 부모 프로세스이다.	
	}else if(pid > 0 ){
	
		printf("부모 프로세스 pid : %d , 자식 프로세스 pid : %d \n ", getpid(), pid);
	}

	//함수 호출
	afterFork();

	return 0;

}

