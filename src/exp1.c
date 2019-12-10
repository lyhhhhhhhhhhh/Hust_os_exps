#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid[2]; /*global variable, which is used to store pid*/

/*the sigkill handle function in parent*/
void handle(int arg) {
    for(int i = 0; i<2;i++) {
        kill(pid[i],SIGUSR1);
    }
}

void print_killed(int arg) {
    printf("kid process %d has killed.\n",getpid());
    exit(0);
}


int main(void)
{
	int fd[2], i;
	
	pipe(fd);/*create the pipe*/

	for (i = 0; i < 2; i++) {
		if((pid[i] = fork()) == 0) {
			break;
        }
    }// create the children processes
 
	if (i == 0) {//the first process
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR1,print_killed);

        printf("kids1: %d\n", getpid());		
		close(fd[0]);/* close fd[0],the kid1 only use to write*/

        int time = 1;
        while(1) {
            write(fd[1], &time, sizeof(int));
            sleep(1);
            time++;
        }	
	} else if (i == 1) {
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR1,print_killed);	

		close(fd[1]);/*the kid2 only use to read*/
        printf("kids2: %d\n", getpid());				

		while(1) {
            int time = 0;
            if(read(fd[0],&time,sizeof(int))!=0) {
                printf("the time is %d\n", time);
            }
        }		
	} else {
        signal(SIGINT, handle);

        close(fd[0]);
        close(fd[1]);

        printf("parent: %d\n", getpid());
        for(int t = 2; t < 2; t++) {
            printf("%d", pid[i]);
        }

		for(i = 0; i < 2; i++)	
			wait(NULL);

        printf("the parent killed\n");
            
	}
 
	return 0;
}
