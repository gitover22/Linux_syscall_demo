#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
struct stu{
    int num;
    char name[20];
};
int main()
{
    struct stu s = {1, "zhangsan"};
    struct stu *p = NULL;
    int i;
    int fd;
    fd = open("/dev/zero", O_RDWR);
    // ftruncate(fd, sizeof(struct stu));
    p = mmap(NULL, sizeof(struct stu), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
    while(1){
        sleep(1);
        memcpy(p, &s, sizeof(struct stu)); // 写
        printf( "read from mmap: %d, %s\n",p->num,p->name);

        s.num++;
    }
    munmap(p, sizeof(struct stu));
    close(fd);
    return 0;
}