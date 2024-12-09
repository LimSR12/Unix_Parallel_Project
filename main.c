/*
* server
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "config.h"

int main() {
    int input_fd = open("bin/data.bin", O_RDONLY);
    if (input_fd < 0) {
        perror("bin/data.bin 파일을 열 수 없습니다");
        return 1;
    }

    int matrix[ROWS][COLS];
    int i, j;

    /* 파일에서 데이터 읽기 (저수준 입출력) */
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (read(input_fd, &matrix[i][j], sizeof(int)) != sizeof(int)) {
                perror("파일 읽기 오류");
                close(input_fd);
                return 1;
            }
        }
    }

    close(input_fd);

    int cols_per_client = COLS / OFFSET;

    /* 8개의 클라이언트 파일 생성, 분배 후 저장 */
    int client;
    for (client = 0; client < NUM_CLIENTS; client++) {
        char filename[20];
        sprintf(filename, "bin/client/partition/sm%d.bin", client);

        int output_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd < 0) {
            perror("파일을 열 수 없습니다");
            return 1;
        }

        for (i = 0; i < ROWS; i++) {
            for (j = client * cols_per_client; j < (client + 1) * cols_per_client; j++) {
                if (write(output_fd, &matrix[i][j], sizeof(int)) != sizeof(int)) {
                    perror("파일 쓰기 오류");
                    close(output_fd);
                    return 1;
                }
            }
        }

        close(output_fd);
        printf("%s 파일이 생성되었습니다.\n", filename);
    }

    /* fork */

    return 0;
}
