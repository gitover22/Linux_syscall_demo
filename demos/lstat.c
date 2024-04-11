#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc,char* argv[])
{
    // stat会穿透符号链接，lstat不会穿透
    struct stat state;
    int ret  = stat(argv[1],&state); //stat： 获取文件属性
    if(S_ISDIR(state.st_mode)){
        printf("is DIR");
    }else if(S_ISLNK(state.st_mode)){
        printf("is LINK");
    }
    return 0;

}