#include <stdio.h>
int main(){
    const char* str = "/home/huafeng/syscall_Demos/testfile.txt";

    FILE *file = fopen(str,"r");
    if(file == NULL){
        printf("fopen error\n");
    }else{
        printf("open sucess!\n");
    }
    char buff[1024]; // 字符数组作为缓冲区
    while(fgets(buff,sizeof(buff),file) != NULL){
        printf("%s",buff);
    }
    fclose(file);

    return 0;

}