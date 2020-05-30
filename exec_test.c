#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




//자식 프로세스 생성 이후에 호출 되는 함수
void afterFork(void)
{
 	printf("이 함 수를 실행 시킨 프로세스는(pid) : %d \n", getpid());

}


int main(int argc, char **argv)
{

	pid_t pid;

    //자식 프로세스가 종료되고 리턴 되는 변수 값.
	int exit_status;
	
	printf("현재 프로세스 pid : %d \n", getpid());

	
	//자식 프로세스 생성
	pid = fork();

	
	//pid 가 0 이면 자식 프로세스이다.
	if(pid == 0){	
		
		printf("자식 프로세스 pid : %d\n ", getpid());


        // "실행 경로", 그 다음으로 프로그램을 실행할 "파라미터"를 넣어준다.그리고 마지막엔 null 값을 넣어줌다.
        // execl를 통해서 현재 디렉토리의 파일들을 보는 자식 프로세스가 새롭게 생성되고 실행된다.
        // 성공하면 리턴 값이 없고, 더 이상 이 코드 이후의 코드를 실행하지 않는다. 부모 프로세스를 떠남..
        // 왜냐면 exec 함수가 호출이 안됬으면, 자식 프로세스는 부모 프로세스의 주소공간과 부모 프로세스가 읽었던 부분
        // 까지 기억했다가 실행할텐데 exec 함수로 인해서 완전히 새로운 주소공간이 생겼기 때문이다.
		if(execl("/bin/ls", "ls", "-al",  NULL)== -1)
		{
			printf("execl() fail! \n");
			return -1;
		}
	

	//pid 가 0이 아니면 부모 프로세스이다.	
	}else if(pid > 0 ){
	
		printf("부모 프로세스 pid : %d , 자식 프로세스 pid : %d \n ", getpid(), pid);
	}

	//함수 호출
	afterFork();

    
    //자식 프로세스가 종료될때까지 기다린다.
    //종료가 되면 exit_status 변수에 자식 상태가 온다.
    //반환 값으로 종료된 자식 프로세스의 pid를 얻어온다.
	pid=wait(&exit_status);
	
    // 자식 프로세스가 정상적으로 종료되었는지 체크
	if(WIFEXITED(exit_status))
	{
		printf("자식 %d 반환 한 값은 : %d \n", pid, WEXITSTATUS(exit_status));	
	}else{
	
		printf("자식 %d 는 정상 종료되지 못했습니다. \n ", pid);
	}


	return 0;

}

