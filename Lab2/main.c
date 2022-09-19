#include "unistd.h"
#include "stdio.h"
#include <stdlib.h>


unsigned int time(void *pVoid);

int main(){
    int fd[2];
    if (pipe(fd) == -1){
        printf("An error ocurred with opening the pipe\n");
    }

    int id = fork();

    if (id < 0){
        perror("An error occurred with fork");
        return -1;
    }
    else if (id > 0){
        close(fd[0]);
        float data[11];
        srand(time(NULL));
        int n = rand() % 10 + 1;
        printf("Enter %d different digits\n", n);
        for(int i = 0; i < n; i++){
            scanf("%f", &data[i]);
        }
        write(fd[1], &n, sizeof(int));
        write(fd[1], data, sizeof(float)*n);
        close(fd[1]);

    }
    else{
        int n;
        close(fd[1]);
        float arr[11];
        read(fd[0], &n, sizeof(int));
        read(fd[0], arr, sizeof(float)*n);
        float sum = 0;
        for(int i = 0; i < n; i++){
            sum += arr[i];
        }
        close(fd[0]);
        FILE *file = fopen("/Users/deniskazhekin/untitled/HomeWork", "w");
        fprintf(file, "The answer is %.2f\n", sum);
        fclose(file);
    }
    return 0;
}
