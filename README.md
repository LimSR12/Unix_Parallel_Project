# Unix_Term-Project_CUDA
### parallel operation project with CUDA

makeDataSet.c -> main.c
----
# makeDataSet.c
>input, output directory 생성 : **sm_0.txt**(input directory) => **sm_0.out.txt**(output directory)
>
>
>
>config.h에 세팅 된 ROWS, COLS 값에 의해 MATRIX 생성

# main.c
>input_data.txt 읽어와서 matrix 세로로 8등분 후 sm_0.txt ~ sm_7.txt 분배, 저장

# client.c
>Loop -> fork() 8회 호출
>
>각 자식 프로세스는 **8개의 client(SM)** 역할
> 
> 
>fork된 자식 프로세스는 실제로는 CPU스케줄러에 의해 순서가 정해진 채 실행되지만
>
>**프로젝트 상에는 CUDA를 이용해 병렬 처리 한다고 가정**
>
>연산 과정은 그냥 입력 data set의 정수에 1씩 더한다고 가정
> 
>각 SM은 자신에게 할당된 파일 하나를 input/에서 읽어와서 1씩 더하고 다시 output/sm_i.out.txt 에 저장
>


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
                // output_file = "output/sm_i.out.txt" 에 1씩 더해서 저장
        }
}

```

# server.c








# Idea
전체 128*128 데이터 존재

이걸 8*8 grid 로 나눠서 각 클라이언트가 사용하도록 할거임 -> file_partition.c

서버는 fork() 후 대기

클라이언트는 fork() 8번, 각 프로세스마다 자신이 읽어와야 할 파일 읽어옴

클라이언트끼리 통신, 순차적으로 데이터 모아줘야 함
ex) 16*16 배열을 8*8 파티셔닝

16 / 8 = 2
각 클라이언트가 가지고 있는 데이터에 대해 
앞에서부터 2개씩 2번 (2*2) -> sm_0
그다음     2개씩 2번 (2*2) -> sm_1
.
.
.
마지막      2개씩 2번 (2*2) -> sm_7









