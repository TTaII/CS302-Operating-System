#include"init.h"

void *writer(int *buffer){
    // Writer should change buffer to buffer+1 (e.g., before *buffer==0, after *buffer==1)
    // Writer cannot start to work when there is any reader or writer working
    // You should implement this using semaphore

    // 等待读者释放rc锁和读取readcount的值来判断有没有reader在读
    // 如果没有则锁住rc，保证reader无法使用readcount，即无法继续读
    // 如果有则则释放锁
    while(1){
        sem_wait(&rc);
        if (readcount!=0)sem_post(&rc); 
        else{
            break;
        }
    }

    // while (readcount!=0);
    // sem_wait(&rc); //错的，如果readcount=0后调度到读者，
    // 设为1然后释放锁，会出现在写的时候，读者在读。
    
    sem_wait(&db); // 判断有没有writer在写
    // You should output this just after this thread gets semaphore
    printf("writer gets sem\n");
    *buffer = *buffer+1;
    // you should output this just before this thread releases the semaphore
    printf("writer writes %d and releases\n", *buffer);
    sem_post(&db);
    sem_post(&rc);
    
}

