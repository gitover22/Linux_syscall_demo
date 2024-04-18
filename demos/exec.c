/**
 * @author huafeng
 * @date 2024/4/18
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
void test_execl(){
    // execl
    // man 3 exec
    printf("before fork()\n");

    pid_t ret = fork();
    if(ret == -1){
        perror("fork error");
    }else if(ret == 0){
        //子进程
        execl("./exec","./exec",NULL);
        perror("execl error");
    }else if(ret > 0){
        printf("父进程");
    }

    printf("end\n");
}
void test_execlp(){
    // execl
    // man 3 exec
    printf("before fork()\n");

    pid_t ret = fork();
    if(ret == -1){
        perror("fork error");
    }else if(ret == 0){
        //子进程
        execlp("ls","ls","-l",NULL);
        perror("execl error");
    }else if(ret > 0){
        printf("父进程");
    }
    sleep(2);
    printf("end\n");
}
int main()
{
    test_execlp();
    return 0;
}