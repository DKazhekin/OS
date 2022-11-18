#include "unistd.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h"
#include <sys/mman.h>
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include "fcntl.h"


unsigned int time(void *pVoid);

int main(){

    int id = fork();

    if (id < 0){
        perror("An error occurred with fork");
        return -1;
    }

    else if (id > 0){

        FILE *fp;
        fp = fopen ("data.txt", "w");

        char s[30];
        printf("Enter the filename:\n");
        scanf("%s",s);

        int len = strlen(s);         // Длина строки

        srand(time(NULL));
        int n = rand() % 9 + 1;

        fprintf(fp, "%d\n", len);
        fprintf(fp, "%s\n", s);
        fprintf(fp, "%d\n", n);



        printf("Enter %d different digits\n", n);

        float x;
        for(int i = 0; i < n; i++){
            scanf("%f", &x);
            fprintf(fp, "%.2f\n", x);
        }
        fclose(fp);

        int fd = open("./data.txt", O_RDONLY);

        struct stat sb;

        if(fstat(fd, &sb) == -1){
            perror("couldn't get the file size\n");
        }
        printf("file size is %lld\n", sb.st_size);

        char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

        char *args[] = {"./child", file_in_memory, NULL};
        execvp(args[0], args);
    }
    return 0;
}
