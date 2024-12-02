# Unix_Term-Project_CUDA
parallel operation project with CUDA

# EX) 16 * 16 data set 
```
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 
32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 
48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 
64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 
80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 
96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 
112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 
128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 
144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 
160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 
176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 
192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 
208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 
224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 
240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 
```
----
# makeDataSet.c
input, output directory 생성 - sm_0.txt(input directory) => sm_0.out.txt(output directory)
config.h ->   ROWS, COLS 세팅 된 값에 의해 MATRIX 생성

# main.c
input_data.txt 읽어와서 matrix 세로로 8등분 후 sm_0.txt ~ sm_7.txt 분배, 저장

# client.c
Loop -> fork() 8회 호출
각 자식 프로세스는 8개의 client(SM) 역할

fork된 자식 프로세스는 실제로는 CPU스케줄러에 의해 실행되지만 CUDA 병렬 처리 한다고 가정
8개의 SM은 파일 읽어와서 1씩 더하고 다시 output/sm_i.out.txt 에 저장
```
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
                
                // sm_i.txt 파일 읽어옴

                // output_file = "output/sm_i.out.txt" 
                for (row = 0; row < ROWS / NUM_CLIENTS; row++) {
                        for (col = 0; col < COLS; col++) {
                                fprintf(output_file, "%d ", matrix[row][col] + 1);
                        }
                }
                exit(0);
        }
}

for(i=0; i<NUM_CLIENTS; i++){
        wait(NULL);
}

printf("all clients process have finished\n");

```

