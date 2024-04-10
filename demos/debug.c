#include <stdio.h>
#include <stdlib.h>
int sum(int a,int b){
    printf("计算int型二值的和\n");
    return a+b;
}
int main(int argc ,char* argv[]){
    printf("%s    %s\n",argv[1],argv[2]);
    int a = atoi(argv[1]), b = atoi(argv[2]);
    int s = sum(a , b);
    return 0;
}
/**
 * bt 查看栈帧
 * info locals 查看局部变量
 * frame 切换栈帧
 * finish 结束当前函数
 * ptype 查看变量类型
 * continue 执行到结束
 * 
*/