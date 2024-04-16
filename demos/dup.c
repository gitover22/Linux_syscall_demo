#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc ,char* argv[])
{
    int stdin = dup(STDOUT_FILENO);
    if(stdin == -1){
        perror("dup error");
    }
    printf("stdin ： %d\n",stdin); // 3
    write(stdin,"abcde -- fghij",sizeof("abcde -- fghij"));

    return 0;
}