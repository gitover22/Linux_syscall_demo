#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
    
    int ret = open("myfifo",O_WRONLY);
    if(ret==-1){
        perror("open");
        return 1;
    }
    printf("open success \n");
    char *str ="hello friends";
    while(1){
        sleep(1);
        ssize_t s = write(ret,str,strlen(str));
        if(s==-1){
            perror("write");
            return 1;
        }
        printf("write success %d \n",s);
    }


    close(ret);
    return 0;
}