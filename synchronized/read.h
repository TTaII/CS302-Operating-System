#include"init.h"

void *reader(int *buffer){
    // Reader should read the value of buffer
    // Reader cannot start to work when there is any writer working
    // You should implement this using semaphore
    sem_wait(&rc);
    readcount++;
    sem_post(&rc); // 删除后无法保证多个读者可以一起读

    // You should output this just after this thread gets semaphore
    printf("Reader gets sem\n");
    int i;
    for(i=0;i<100000;i++);
    // you should output this just before this thread releases the semaphore
    printf("Reader reads %d and releases\n", *buffer);

    sem_wait(&rc); // 删除后无法保证多个读者可以一起读
    readcount--;
    sem_post(&rc);
    
}

