/**
 * 请使用union联合体实现: 检测本机是大端字节序还是小端字节序
 * 联合体的大小等于其最大成员的大小，不同的成员会共享这一块内存区域
 * 适用于需要用到多种类型但只会同时使用其中一种类型的情况
*/
// tips: 主机字节序都是小端字节序
#include <stdio.h>
void check_endian(){
    union{
        int i;
        char c[sizeof(int)];
    }u;
    u.i = 0x12345678;
    if(u.c[0] == 0x12){ // 低地址处存储的是高字节，那么就是大端字节序
        printf("big endian\n");
    }else{
        printf("little endian\n");
    }
}
int main(){
    check_endian();
    return 0;
}