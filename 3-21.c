#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void collatzConjecture(int num){
	printf("%d\n",num);
	while(num > 1){
    	if(num % 2 == 0){ 
      		num = num / 2;
      		printf("%d\n", num);
    	}
    	else{ 
     		num = num * 3 + 1;
      		printf("%d\n", num);
    	}
  	}
}		
int main(int argc, char *argv[])
{
	// type casting to int 
	int number = atoi(argv[1]);

	// check input is positive integer
	if(number <= 0){
		perror("Please input Positive Interger");
		return 0;
	}

	pid_t pid;
	pid = fork();
	
	//child process
	if (pid == 0) {
		collatzConjecture(number);
		printf("End child process\n");
	}
	// parent process
	else if (pid > 0) {
		wait(NULL);
		printf("End parent process\n");
	}
	return 0;
}