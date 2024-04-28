#include <stdio.h>
#include <unistd.h> // STDIN_FILENO
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/**
 * dup2: dup to重定向到
 * （oldfd，newfd）
 * man 2 dup2
*/
int main()
{
    // int r = dup2(STDOUT_FILENO,20); // 20 指向了STDOUT_FILENO
    // if(r == -1){
    //     perror("dup2 error");
    // }
    // printf("new fd: %d\n",r);
    // char* str = "123456789";

    // if(write(r,str,sizeof(str)) == -1){
    //     perror("error write");
    // }
    void test_dup2();
    test_dup2();
    return 0;
}
void test_dup2(){
    int ret = open("./test.txt",O_CREAT|O_RDWR,0666);
    if(ret == -1){
        perror("open error");
    }
    printf("open fd: %d\n",ret);
    int r = dup2(ret,STDOUT_FILENO); // 20 指向了STDOUT_FILENO
    if(r == -1){
        perror("dup2 error");
    }
    printf("new fd: %d\n",r);
    char* str = "123456789";

    if(write(STDOUT_FILENO,str,sizeof(str)) == -1){
        perror("error write");
    }
}