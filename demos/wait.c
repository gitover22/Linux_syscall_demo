#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main(){
    pid_t ret, ret2;
    int status;
    ret = fork();
    if(ret == -1){
        perror("fork error");
        return -1;
    }else if(ret ==0){
        printf("child process:%d\n",getpid());
        sleep(10);
        printf("child process exit\n");
        return 0;
    }else{
        printf("parent process\n");
        ret2 = wait(&status);
        if(ret2 == -1){
            perror("wait error");
            return -1;
        }
        if(WIFEXITED(status)){
            printf("child process noramly exit with %d\n", WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("child process exit with signal %d\n", WTERMSIG(status));
        }
        printf("parent process wait child process %d exit\n", ret2);
        return 0;
    }
}