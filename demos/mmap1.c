#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
int main()
{
    char *p = NULL;
    int i;
    int fd;
    fd = open("mmap.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
    ftruncate(fd, 100);
    int len = lseek(fd, 0, SEEK_END);
    p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    pid_t pid =fork();
    if(pid == 0){
        printf("child process\n");
        strcpy(p,"child :hello world");
    }else if(pid > 0){
        wait(NULL);
        printf("parent process\n");
        printf("parent read: %s\n", p);
        munmap(p, len);
    }else{
        printf("fork error\n");
        perror("fork");
    }
    close(fd);
    return 0;
}