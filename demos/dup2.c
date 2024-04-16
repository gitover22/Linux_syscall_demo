#include <stdio.h>
#include <unistd.h> // STDIN_FILENO
/**
 * dup2: dup to重定向到
 * （oldfd，newfd）
 * man 2 dup2
*/
int main()
{
    int r = dup2(STDOUT_FILENO,20); // 20 指向了STDOUT_FILENO
    if(r == -1){
        perror("dup2 error");
    }
    printf("new fd: %d\n",r);
    char* str = "123456789";

    if(write(r,str,sizeof(str)) == -1){
        perror("error write");
    }
    return 0;
}