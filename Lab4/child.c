#include "unistd.h"
#include "stdio.h"
#include <stdlib.h>

#include "string.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "errno.h"
#include "fcntl.h"


int main(int argc, char* argv[]){

    char *file_in_memory = argv[1];
    int n_of_chars = file_in_memory[0] - '0';
    int n_of_digits = file_in_memory[n_of_chars+3] - '0';

    printf("%d\n", n_of_chars);
    printf("%d\n", n_of_digits);

    char str[n_of_chars];

    for (int i = 2; i < 2 + n_of_chars; i++){
        str[i-2] = file_in_memory[i];
    }
    float sum = 0;
    int start = 5 + n_of_chars;
    for(int j = 0; j < n_of_digits; j++) {
        int i = 0;
        char a[4];
        while (i < 4) {
            a[i] = file_in_memory[start];
            i += 1;
            start += 1;
        }
        sum += atof(a);
        printf("%s\n", a);
        start += 1;

    }
    printf("%.2f\n", sum);
    printf("%s", str);


    FILE *fptr2;
    fptr2 = fopen(str,"w");
    fprintf(fptr2,"The answer is: %.2f\n", sum);
    fclose(fptr2);


    return 0;
}