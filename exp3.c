#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h> // open()

#define BUF_NUM 3
#define BUF_SIZE 3

int semid,shmid[BUF_NUM];
void* buf_id[BUF_NUM];
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

    semctl(semid, 0, SETVAL, BUF_NUM);//信号灯1,表示缓冲区剩余空间，初始值为1
    semctl(semid,1,SETVAL,0);//信号灯2,表示缓冲区元素数，初始值为0
    semctl(semid, 2, SETVAL, 1);// Mutex, which is avoid the buffer in race condition.

    for (int i=0; i<BUF_NUM; i++) {
        shmid[i] = shmget(IPC_PRIVATE, BUF_SIZE, IPC_CREAT | 0666);
    }

    for (int i=0; i<BUF_NUM; i++) {
        buf_id[i] =shmat(shmid[i], NULL, 0);
    }

    int fd_in = open("./input.txt", O_RDONLY);
    int fd_out = open("./output.txt", O_WRONLY | O_CREAT);

    int i;

    for (i = 0; i < 2; i++) {
		if((pid[i] = fork()) == 0) {
			break;
        }
    }// create the children processes
 
	if (i == 0) {//the first process
        int id = 0;
        int size = 0;
        while(1) {
            P(semid, 0);
            P(semid, 2);

            size = read(fd_in, buf_id[id], BUF_SIZE);

            printf("read: %c\n",&buf_id[id]);

            V(semid, 2);
            V(semid, 1);

            if(size < BUF_SIZE) {
                break;
            }

            id +=1;
            id = id % 3;
        }
        printf("read break!\n");     

	} else if (i == 1) {
        int id = 0;
        int write_size = 0;
        while(1) {
            P(semid, 1);
            P(semid, 2);

            write_size = write(fd_out, buf_id[id], BUF_SIZE);

            printf("wrire: %d\n",write_size);

            V(semid, 2);
            V(semid, 0);

            if(write_size < BUF_SIZE) {
                break;
            }

            id +=1;
            id = id % 3;
        }	
        printf("write break!\n");
	} else {
        waitpid(pid[0],NULL,0);
        waitpid(pid[1],NULL,0);

        close(fd_in);
        close(fd_out);          
	}
 
	return 0;

}

