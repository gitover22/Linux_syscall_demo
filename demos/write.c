#include <stdio.h>
#include <unistd.h> // open write
#include <fcntl.h> // O_RDONLY

// 默认情况下，每个Unix/Linux进程会打开三个文件描述符：
// 0：标准输入（stdin）。这是进程读取输入的默认方式。
// 1：标准输出（stdout）。这是进程输出数据的默认方式。
// 2：标准错误（stderr）。这是进程报告错误消息的默认方式。
// man 2 open
int main(){
    const char* str = "12";
   
    size_t n = write(1,str,sizeof(str));
    if(n == -1){
        printf("write() error\n");
        return 0;
    }else{
        printf("write() success, write: %ld bytes\n",n);
    }
    return 0;

}