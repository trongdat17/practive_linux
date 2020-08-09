#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

const char *semName = "BuiTrongDat";
int main(int argc, char *argv[])
{
    sem_t *sem_id = sem_open(semName, O_CREAT, 0777, 0);
    if (sem_id == SEM_FAILED){
        perror("Parent  : [sem_open] Failed\n");
    }
    // if (sem_wait(sem_id) < 0)
    // {
    //     printf("Parent  : [sem_wait] Failed\n");
    // }
    //printf("Parent  : Wait for Child to Print\n");
    // if (sem_wait(sem_id) < 0)
    // {
    //     printf("Parent  : [sem_wait] Failed\n");
    // }
    //printf("Parent  : Child Printed! \n");
    if (sem_post(sem_id) < 0)
    {
        printf("Child   : [sem_post] Failed \n");
    }
    printf("Parent  : Child done! \n");
    // if (sem_close(sem_id) != 0)
    // {
    //     perror("Parent  : [sem_close] Failed\n"); 
    // }
    // if (sem_unlink(semName) < 0)
    // {
    //     printf("Parent  : [sem_unlink] Failed\n"); 
    // }
    return 0;
}