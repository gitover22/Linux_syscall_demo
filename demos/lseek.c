#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main(){
    int fd = open("/home/huafeng/syscall_Demos/testfile.txt",O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 0){
        perror("open error!\n");
        return 0;
    }
    char *buf = "abcdefghijklmn";
    printf("strlen(buf): %d\n",strlen(buf));
    ssize_t ret = write(fd,buf,strlen(buf)); // sizeof(buf) = 8,64位机器的指针大小都是8字节
    if(ret < 0){
        perror("write error");
        return 0;
    }
    lseek(fd,0,SEEK_SET);   // 把读写指针偏移到文件开始位置,,SEEK_SET就是起始位置
    char c;
    while(read(fd , &c , 1)>0){
        printf("%c", c);
    }

    // 通过lseek获取文件的大小 原理：lseek返回起始位置距离偏移后读写指针的大小
    off_t len= lseek(fd, 19,SEEK_END);
    write(fd, "a", 1);
    printf("\ntestfile.txt的大小为:  %d\n",len);
    return 0;
}
