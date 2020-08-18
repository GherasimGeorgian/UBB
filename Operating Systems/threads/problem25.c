#include <limits.h>
#include <fcntl.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

typedef struct ARG {
    int id;
} ARG;

 int** m;
int min_dif = INT_MAX;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;

void *th_func(void *a) {
    ARG arg = *((ARG*)a);
    int i;
   pthread_mutex_lock(&count);
    for(i = 0; i < 99; i++) {
         if(abs(m[arg.id][i]-m[arg.id][i+1]) < min_dif)
          {
          min_dif = abs(m[arg.id][i]-m[arg.id][i+1]);
          printf("%d\n", min_dif);
          }
    }
   pthread_mutex_unlock(&count);
    return NULL;
}

int main(int argc, char** argv) {
    int fd, i, j;

    if(argc <= 1) {
        fprintf(stderr, "No input file specified");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("Failed to open input file");
        exit(1);
    }

    m = malloc(2000*sizeof(int));
    for(i=0; i<20; i++) {
        m[i] = malloc(100* sizeof(int));
        read(fd, m[i],100*sizeof(int));
        for(j=0; j<100; j++) {
            printf("%d " , m[i][j]);
        }
        printf("\n \n\n\n");
    }

     pthread_t th[20];
     ARG args[20];


    printf("Threads : \n\n\n\n");

   for(i=0; i < 20; i++) {
        args[i].id = i;
        if(0 != pthread_create(&th[i], NULL, &th_func, (void*) &args[i])) {
            perror("Error on pthread create");
        }
    }

    for(i=0; i < 20; i++) {
        if(0 != pthread_join(th[i], NULL)) {
            perror("Error waiting for thread");
        }
    }

    for(i=0;i<20;i++)
        free(m[i]);
    free(m);

    close(fd);
    return 0;
}