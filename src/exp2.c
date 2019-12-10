#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h> 


int id;
pthread_t tid[2];
int buf;

void P(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
}

void V(int semid, int index) {
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
}

void calculate() {
    for(int i=1; i<=100; i++) {
        P(id,0);
        buf+=i;
        V(id,1);
    }
}

void print() {
    for(int i=1; i<=100; i++) {
        P(id,1);
        printf("%d\n",buf);
        V(id,0);
    }
}

int main() {
    id = semget(1, 2, IPC_CREAT | 0666);

    semctl(id, 0, SETVAL, 1);//信号灯1,表示缓冲区剩余空间，初始值为1
    semctl(id,1,SETVAL,0);//信号灯2,表示缓冲区元素数，初始值为0

    pthread_create(&(tid[0]), NULL , (void * (*)(void*))&calculate, NULL);
    pthread_create(&(tid[1]), NULL , (void * (*)(void*))&print, NULL);
 
    pthread_join(tid[1], NULL);

    for(int i=0;i<2;i++) {
        semctl(id, i, IPC_RMID);
    }

    return 0;
}

