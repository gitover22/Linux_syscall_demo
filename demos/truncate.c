#include <stdio.h>
#include <unistd.h>
int main()
{
    int ret = truncate("/home/huafeng/syscall_Demos/testfile.txt",200);// 设置文件大小
    if(ret == -1){
        perror("truncate false");
        return 0;
    }
    return 0;

}