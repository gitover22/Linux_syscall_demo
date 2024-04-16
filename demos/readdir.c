#include<stdio.h>
#include<dirent.h>
#include<string.h>
int main(int argc,char* argv[])
{
    DIR * dir;
    dir = opendir(argv[1]);
    if(dir == NULL){
        perror("opendir error!");
    }
    struct dirent * denty;
    while((denty = readdir(dir)) != NULL){
        if(strcmp(denty->d_name,".") == 0 || strcmp(denty->d_name,"..") == 0) continue; 
        printf("%s\t",denty->d_name);
    }
    closedir(dir);
    return 0;
}