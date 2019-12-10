#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include <string.h>


#define BUF_SIZE (sizeof(int))


int semid,shmid;
void* buf_id;
int pid[2];

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

int main(int argc, char const *argv[]) {

    semid = semget(1, 3, IPC_CREAT | 0666);

    semctl(semid, 0, SETVAL, 1);//信号灯1,表示缓冲区剩余缓冲块，初始值为BUF_NUM.
    semctl(semid, 1, SETVAL, 0);//信号灯2,表示缓冲区元素数，初始值为0
    semctl(semid, 2, SETVAL, 1);// Mutex, which is avoid the buffer in race condition.

    /*shm initial*/
    shmid = shmget(IPC_PRIVATE, BUF_SIZE, IPC_CREAT | 0666);
    

    /*shmat the shm*/
    buf_id =shmat(shmid, NULL, 0);

    int i;

    for (i = 0; i < 2; i++) {
		if((pid[i] = fork()) == 0) {
			break;
        }
    }// create the children processes
 
	if (i == 0) {//the first process
        int temp=0;
        for(int i=1; i<=100; i++) {
            temp+=i;
            P(semid, 0);
            P(semid, 2);
            memcpy(buf_id, &temp, sizeof(int));
            V(semid, 2);
            V(semid, 1);
        }
         

	} else if (i == 1) {
        int temp = 0;
        for(int i=1; i<=100; i++) {
            P(semid,1);
            P(semid, 2);
            memcpy(&temp, buf_id,sizeof(int));
            printf("%d\n",temp);            
            V(semid, 2);
            V(semid,0);
        }
	} else {
        waitpid(pid[0],NULL,0);
        waitpid(pid[1],NULL,0);

        shmctl(shmid, IPC_RMID,NULL);
                 
	}
 
	return 0;

}


