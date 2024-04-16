#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{


    int ret = link(argv[1],argv[2]);
    if( ret == -1){
        perror("link error! ");
        exit(EXIT_FAILURE);
    }

    ret = unlink(argv[1]);
    if(ret == -1){
        perror("unlink error !");
        exit(EXIT_FAILURE);
    }
    getchar();
    return 0;
}