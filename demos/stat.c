#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main()
{
    struct stat state;
    int ret  = stat("/home/huafeng/syscall_Demos/testfile.txt",&state); //stat： 获取文件属性
    if(ret == -1){
        printf("stat error\n");
        return 0;
    }
    printf("%ld\n",state.st_size);
    printf("%ld\n",state.st_uid); 

    // stat会穿透符号链接，lstat不会穿透
    return 0;

}