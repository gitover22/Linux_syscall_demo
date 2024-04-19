#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	int status;
	pid_t pid,ret;
	pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    
	if (pid == 0)
	{
		printf("child process:%d\n",getpid());
		return 19;
	}
	else
	{
		printf("parent process:%d\n",getpid());
		ret = waitpid(pid, &status, 0); // waitpid(-1, NULL, 0)等价于wait(NULL)
        if(ret == -1){
            perror("waitpid error");
            exit(EXIT_FAILURE);
        }else if(ret >0){
            printf("child %d exit\n",ret);
        }
        if(WIFEXITED(status)){
		    printf("child process exit status is %d\n", WEXITSTATUS(status));
        }
	}
}