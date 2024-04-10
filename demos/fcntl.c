#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h>
#define WAITINFO "waiting!\n"

/**
 * fcntl: 获取或修改文件属性
 * 
*/
int main()
{
    int flags,n;
    flags =fcntl(STDIN_FILENO,F_GETFL); // 获取属性
    flags |= O_NONBLOCK; // 按位或 == 附加
    int ret =fcntl(STDIN_FILENO,F_SETFL,flags); // 设置属性


    // 检测修改是否成功
    char buff[32];
    while(1){
        ssize_t s =  read(STDIN_FILENO,buff,sizeof(buff)); // STDIN_FILENO
        sleep(2);
        if(s > 0){
            write(STDOUT_FILENO,buff,s);
        }else if(errno ==EAGAIN && errno == EWOULDBLOCK){ //EWOULDBLOCK == EAGAIN
            // 读到了空的非阻塞文件
            write(STDOUT_FILENO,WAITINFO,sizeof(WAITINFO));
            continue;

        }else if(errno < 0){
            printf("%s\n",strerror(errno));
            exit(1);
        }
    }
    return 0;
}