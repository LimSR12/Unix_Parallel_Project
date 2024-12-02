#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "config.h"

int main(){

	pid_t pids[NUM_CLIENTS];

	int i;

	for(i=0; i<NUM_CLIENTS; i++){
		pids[i] = fork();
		if(pids[i] < 0){
			perror("fork failed");
			exit(1);
		}else if(pids[i] == 0){
			//client i
			printf("client %d forked (pid:%d)\n",i, getpid());
			sleep(2);
			exit(0);
		}
	}

	for(i=0; i<NUM_CLIENTS; i++){
		wait(NULL);
	}

	printf("all clients process have finished\n");
}
