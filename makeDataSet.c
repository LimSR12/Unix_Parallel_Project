#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "config.h"
//#include <cuda_runtime_api.h>

//#define ROWS 128
//#define COLS 128

int main() {
    FILE *file;
    file = fopen("input_data.txt", "w");

    if(access("input", F_OK) == -1){
	if(mkdir("input", 0777) == -1){
	    perror("input mkdir failed");
	    exit(1);
	}
	printf("input 디렉토리가 생성되었습니다.\n");
    }    

    if (access("output", F_OK) == -1) {
        if (mkdir("output", 0777) == -1) {
             perror("output mkdir failed");
             exit(1);
        }
        printf("output 디렉토리가 생성되었습니다.\n");
    }


    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

	int i, j;
	for (i = 0; i < ROWS; i++) {
        	for (j = 0; j < COLS; j++) {
			fprintf(file, "%d ", i * ROWS + j);
        	}
        	fprintf(file, "\n"); // 행마다 줄바꿈
    	}

	fclose(file);
    	printf("데이터 파일이 생성되었습니다: input_data.txt\n");
    	return 0;
}
