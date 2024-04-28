#include <stdio.h>
#include <signal.h>
int main()
{
    int pid, status;
    printf("Enter the process id: ");
    scanf("%d", &pid);
    status = kill(pid, SIGSEGV); // Segmentation fault
    if (status == 0)
        printf("Process killed successfully\n");
    else
        printf("Error in killing process\n");
    return 0;
}