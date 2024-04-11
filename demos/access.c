#include <stdio.h>
#include <unistd.h>
int main()
{
    int ret = access("/home/huafeng/syscall_Demos/testfile.txt",F_OK);
    return 0;
}