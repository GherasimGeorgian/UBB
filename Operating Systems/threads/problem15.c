#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

typedef struct _Numbers{

   int numbers[100];
   int numere_adaugate;
   int max_numbers;
   int index;
} Numbers;

pthread_mutex_t m;
pthread_cond_t c;


void* bear(void* a) {
    Numbers *nrs;
    nrs=(Numbers *) a;

    while(nrs->numere_adaugate != nrs->max_numbers) {
        pthread_mutex_lock(&m);
        if(nrs->numere_adaugate != nrs->max_numbers) {
             nrs->numbers[nrs->index]=1;
             nrs->index++;
             nrs->numere_adaugate++;

        }
        else {
            pthread_cond_signal(&c);
        }
        pthread_mutex_unlock(&m);
    }
    pthread_mutex_lock(&m);
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
    return NULL;
}
void* farmer(void* a) {
    Numbers *nrs;
    nrs=(Numbers *) a;
    while(nrs->numere_adaugate != nrs->max_numbers) {
        pthread_mutex_lock(&m);
        while(nrs->numere_adaugate != nrs->max_numbers) {
            pthread_cond_wait(&c, &m);
        }
        nrs->numbers[nrs->index]=1;
        nrs->index++;
        nrs->numere_adaugate++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char** argv) {

   Numbers nrs;

  nrs.max_numbers = 4;

   nrs.index=0;


    pthread_t t[1];
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);

    pthread_create(&t[0], NULL, farmer, (void *)&nrs);
    pthread_create(&t[1], NULL, bear, (void *)&nrs);


     pthread_join(t[0], NULL);
     pthread_join(t[1],NULL);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    printf("fsges");
    return 0;
}



