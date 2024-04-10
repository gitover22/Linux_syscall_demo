#include <stdio.h>
#include <unistd.h> // open write
#include <fcntl.h> // O_RDONLY
/**
 * read(fd, buff,size)
 * success: 读取的字节（为0说明读到末尾）
 * fail：-1
 * 
*/
int main(){
    int fd1,fd2;
    fd1 = open("/home/huafeng/syscall_Demos/testfile.txt",O_RDONLY);
    fd2 = open("/home/huafeng/syscall_Demos/newfile.txt",O_RDWR|O_CREAT,0777);
    if(fd1 == -1 || fd2 == -1 ){
        printf("open fail\n");
        return;
    }else{
        printf("open success,fd1:%d   fd2:%d\n",fd1,fd2);
    }
    char buff[1024];
    ssize_t s;
    while((s = read(fd1,buff,sizeof(buff)-1)) > 0){
        buff[s] = '\0'; // 添加结束标志
        printf("%s",buff);
        ssize_t t= write(fd2,buff,s);
        printf("==========写入%ld bytes=======",t);
    }
    // printf("%d",EOF); // -1
    if(s == -1){
        perror("读错");
    }
    close(fd1);
    close(fd2);
    return 0;

}