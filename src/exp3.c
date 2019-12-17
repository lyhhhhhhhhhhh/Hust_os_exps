#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#include<sys/types.h>
#include<fcntl.h> // open()

#define BUF_NUM 3
#define BUF_SIZE 3

#include <sys/stat.h>


int get_file_size(const char *path)//use the struct in linux to get the file of input.txt.
{
	int filesize = -1;	
	struct stat statbuff;
	if(stat(path, &statbuff) < 0){
		return filesize;//filesize = -1, the file do not exit
	}else{
		filesize = statbuff.st_size;
	}
	return filesize;
}

/* global varies*/
int semid,shmid[BUF_NUM];
void* buf_id[BUF_NUM];//the pointer array with buf address.
int pid[2];//pid array.



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

    semctl(semid, 0, SETVAL, BUF_NUM);//信号灯1,表示缓冲区剩余缓冲块，初始值为BUF_NUM.
    semctl(semid,1,SETVAL,0);//信号灯2,表示缓冲区元素数，初始值为0
    semctl(semid, 2, SETVAL, 1);// Mutex, which is avoid the buffer in race condition.

    /*shm initial*/
    for (int i=0; i<BUF_NUM; i++) {
        shmid[i] = shmget(IPC_PRIVATE, BUF_SIZE, IPC_CREAT | 0666);
    }

    /*shmat the shm*/
    for (int i=0; i<BUF_NUM; i++) {
        buf_id[i] =shmat(shmid[i], NULL, 0);
    }

    int fd_in = open("/home/lyhhhhh/study/Operating_System/exp/doc/input.txt", O_RDONLY);
    int fd_out = open("/home/lyhhhhh/study/Operating_System/exp/doc/output.txt", O_WRONLY | O_CREAT);

    int i;

    int file_size = get_file_size("/home/lyhhhhh/study/Operating_System/exp/doc/input.txt");// get the size of the file.

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


            // memset(buf_id[id],0,sizeof(char)*BUF_SIZE);
            size = read(fd_in, buf_id[id], BUF_SIZE);

            V(semid, 2);
            V(semid, 1);

            if(size < BUF_SIZE) {
                break;//break out of the while, when the file is finished reading.
            }

            id +=1;
            id = id % BUF_NUM;//形成环形缓冲
        }
        for (int i=0; i<BUF_NUM; i++) {
            shmdt(buf_id[i]);
        }
        printf("read break!\n");     

	} else if (i == 1) {
        int id = 0;
        int write_size = BUF_SIZE;
        while(1) {
            P(semid, 1);
            P(semid, 2);

            file_size -= write_size;//calculate the left file to write.

            if(file_size <= 0 ) {
                write_size = write(fd_out, buf_id[id], file_size+BUF_SIZE);
            } else
            {
                write_size = write(fd_out, buf_id[id], BUF_SIZE);
            }      

            V(semid, 2);
            V(semid, 0);

            if(file_size <= 0) {
                break;
            }

            id +=1;
            id = id % BUF_NUM;
        }	
        for (int i=0; i<BUF_NUM; i++) {
            shmdt(buf_id[i]);
        }
        printf("write break!\n");

	} else {
        waitpid(pid[0],NULL,0);
        waitpid(pid[1],NULL,0);

        for (int i=0; i<BUF_NUM; i++) {
            shmctl(shmid[i], IPC_RMID,NULL);
        }

        close(fd_in);
        close(fd_out);          
	}

	return 0;
}


