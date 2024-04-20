#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_NAME "myfifo"

int main() {
    int fd;
    // 创建FIFO（如果已存在则不执行）
    if(mkfifo(FIFO_NAME, 0777) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }
    printf("FIFO created successfully\n");

    // 打开FIFO
    fd = open(FIFO_NAME, O_RDONLY);
    if(fd == -1) {
        perror("open");
        return 1;
    }
    printf("Open successful\n");
    // 读取并打印FIFO中的数据
    char c[20];
    while(1) {
        int bytes_read = read(fd, c, sizeof(c));
        if(bytes_read == -1) {
            perror("read");
            break;
        } else if(bytes_read == 0) { // EOF
            printf("End of data from FIFO\n");
        }
        printf("%s\n", c); //不加换行，无法输出，是因为缓冲区机制，换行能刷新缓冲区
    }

    // 关闭文件描述符
    if(close(fd) == -1) {
        perror("close");
        return 1;
    }
    
    return 0;
}