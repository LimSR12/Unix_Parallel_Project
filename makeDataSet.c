#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime_api.h>

#define ROWS 128
#define COLS 128

int main() {
    FILE *file;
    file = fopen("input_data.txt", "w");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

	int i, j;
	for (i = 0; i < ROWS; i++) {
        	for (j = 0; j < COLS; j++) {
            		int value = rand() % 100; // 임의의 0-99 값 생성
			fprintf(file, "%d ", i * ROWS + j);
        	}
        	fprintf(file, "\n"); // 행마다 줄바꿈
    	}

	fclose(file);
    	printf("데이터 파일이 생성되었습니다: input_data.txt\n");
    	return 0;
}
