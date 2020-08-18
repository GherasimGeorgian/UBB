#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mymutex;
typedef struct ARG {
    int *row;
    int id, cols;
    int *rez;
} ARG;

void *th_func(void *a) {
    ARG arg = *((ARG *) a);
    int i;
    for (i = 0; i < arg.cols; i++) {
        pthread_mutex_lock(&mymutex);
        *(arg.rez) += arg.row[i];
        pthread_mutex_unlock(&mymutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int i, j, rows, cols;
    int **m;
    if(argc != 2) {
        printf("Please provide exactly one argument\n");
        exit(0);
    }
    if(0 != pthread_mutex_init(&mymutex, NULL)) {
        perror("Error initializing mutex");
        exit(1);
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
    int rez = 0;
    ARG args[rows];

    for(i=0; i < rows; i++) {
        args[i].row = m[i];
        args[i].cols = cols;
        args[i].id = i;
        args[i].rez = &rez;
        if(0 != pthread_create(&th[i], NULL, &th_func, &args[i])) {
            perror("Error on create thread");
        }
    }

    for(i=0; i < rows; i++) {
        if(0 != pthread_join(th[i], NULL)) {
            perror("Error waiting for thread");
        }
    }

    printf("Sum is %d\n", rez);

    pthread_mutex_destroy(&mymutex);

    for(i=0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
    return 0;
}