#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
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
			// client i (sm i)
			// 각 자식 프로세스들은 스케쥴러에 의해 실행되지만
			// 동시에 병렬 처리된다고 가정
			FILE* file;
			char path[20];
			snprintf(path, sizeof(path), "sm_%d.txt", i);
			
			file = fopen(path, "r");
		        if (file == NULL) {
                		perror("파일을 열 수 없습니다");
                		exit(1);
            		}
			// 클라이언트 파일 읽어옴
			int matrix[ROWS / NUM_CLIENTS][COLS];
			int row, col;
			for (row = 0; row < ROWS / NUM_CLIENTS; row++) {
    				for (col = 0; col < COLS; col++) {
        				fscanf(file, "%d", &matrix[row][col]);
    				}
			}
			fclose(file);	
			
			snprintf(path, sizeof(path), "output/sm_%d.out.txt", i);
			
			FILE* output_file = fopen(path, "w");
			if(output_file == NULL){
				perror("파일을 열 수 없습니다.");
				exit(1);
			}
			for (row = 0; row < ROWS / NUM_CLIENTS; row++) {
    				for (col = 0; col < COLS; col++) {
        				fprintf(output_file, "%d ", matrix[row][col] + 1);
    				}
    				//fprintf(file, "\n");
			}

			printf("%s\n", path);
			printf("client %d forked (pid:%d)\n",i, getpid());
			
			//sleep(2);
			fclose(file);
			exit(0);
		}
	}

	for(i=0; i<NUM_CLIENTS; i++){
		wait(NULL);
	}

	printf("all clients process have finished\n");
}
