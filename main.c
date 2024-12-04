#include <stdio.h>
#include <stdlib.h>
#include "config.h"

//#define ROWS 16
//#define COLS 16
//#define NUM_CLIENTS 8

int main() {

    FILE* input_file = fopen("bin/data.bin", "rb");
    if (input_file == NULL) {
        printf("bin/data.bin 파일을 열 수 없습니다.\n");
        return 1;
    }

    int matrix[ROWS][COLS];

    int i, j;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            fread(&matrix[i][j], sizeof(int), 1, input_file);
        }
    }

    fclose(input_file);

    /* 8개의 클라이언트 파일 생성, 분배 후 저장 */
    int client;
    for (client = 0; client < NUM_CLIENTS; client++) {
        char filename[20];
        sprintf(filename, "input/sm_%d.bin", client);

        FILE* output_file = fopen(filename, "wb");
        if (output_file == NULL) {
            printf("%s 파일을 열 수 없습니다.\n", filename);
            return 1;
        }

	 
        for (i = 0; i < ROWS; i++) {
            for (j = client * 2; j < client * 2 + 2; j++) {
                //fprintf(output_file, "%d ", matrix[i][j]);
            	fwrite(&matrix[i][j], sizeof(int), 1, output_file);
		//printf("%d", matrix[i][j]);
	    }
            //fprintf(output_file, "\n");
        }

        fclose(output_file);
        printf("%s 파일이 생성되었습니다.\n", filename);
    }

    /* fork */

    

    return 0;
}


