#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
typedef struct ARG {
    int *rez;
    int id;
} ARG;

int** m;
int rows, cols;

void *th_func(void *a) {
    ARG arg = *((ARG*)a);
    int i;
    for(i = 0; i < cols; i++) {
        arg.rez[arg.id] += m[arg.id][i];
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int i, j;
    if(argc != 2) {
        printf("Please provide exactly one argument\n");
        exit(0);
    }
    FILE* f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fscanf(f, "%d %d", &rows, &cols);

    m = (int**)malloc(rows*sizeof(int*));

    for(i=0; i < rows; i++) {
        m[i] = (int*)malloc(cols*sizeof(int));
        for(j=0; j < cols; j++) {
            fscanf(f, "%d", &m[i][j]);
        }
    }

    fclose(f);
    pthread_t th[rows];
    int *rez = (int*) malloc(rows * sizeof(int));
    memset(rez, 0, rows * sizeof(int));
    ARG args[rows];    

    for(i=0; i < rows; i++) {
        args[i].rez = rez;
        args[i].id = i;
        if(0 != pthread_create(&th[i], NULL, &th_func, (void*) &args[i])) {
            perror("Error on pthread create");
        }
    }

    for(i=0; i < rows; i++) {
        if(0 != pthread_join(th[i], NULL)) {
            perror("Error waiting for thread");
        }
    }

    for(i=0; i < rows; i++) {
        printf("Sum on row %d is %d\n", i, rez[i]);
    }

    for(i=0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
    free(rez);
    return 0;
}