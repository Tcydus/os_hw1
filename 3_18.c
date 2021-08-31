#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    // Fork proces
    pid_t pid = fork();
  
    // parent process 
    if (pid > 0)
        sleep(50);
  
    // child process
    else        
        exit(0);
  
    return 0;
}
