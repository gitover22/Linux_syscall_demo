#include <stdio.h>
#include <unistd.h>
int main()
{
    int ret = access("/home/huafeng/syscall_Demos/testfile.txt",X_OK);
    if(ret == -1){
        perror("access error\n");
        return 0;
    }
    if(ret == 0){
        printf("所属用户可读\n");
    }
    return 0;
}