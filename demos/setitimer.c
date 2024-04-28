#include <sys/time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
struct itimerval it;
void getsignal(){
    printf("signal SIGALRM\n");
}
int main(){
    it.it_value.tv_sec = 1;
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 3;
    it.it_interval.tv_usec = 0;
    signal(SIGALRM, getsignal);
    setitimer(ITIMER_REAL, &it, NULL);
    while(1);
    return 0;
}