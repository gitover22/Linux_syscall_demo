#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#define WAITINFO "wait for!\n"
int main(){
    int f = open("/dev/tty",O_RDONLY|O_NONBLOCK);
    printf("%d",f); // 3 
    char buff[32];
    while(1){
        ssize_t s =  read(f,buff,sizeof(buff)); // 3
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