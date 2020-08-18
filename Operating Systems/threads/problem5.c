//Sa se scrie un program care creeaza doua threaduri si are doua variabile globale numite numere_pare si numere_impare. Fiecare thread va genera numere aleatoare  si in functie de paritatea lor va incrementa valoarea  globala respectiva. Threadurile se opresc cand  ambele variabile depasesc 100. Programul  principal afiseaza cele doua variabile globale si apoi se termina
#include<stdio.h>
#include<pthread.h>
#include <time.h>
int data =0;

pthread_mutex_t lock;
pthread_cond_t cond;

typedef struct _Numere{

    int numere_pare;
    int numere_impare;
    int numere_adaugate;
} Numere;


void * even(void *a)
{  int nr_random;
    srand(time(NULL));
    Numere *nrs;
    nrs = (Numere *) a;
    while(data < 200 && nrs->numere_pare < 100)
    {
        do{
          nr_random = rand() % 10;

        }while(nr_random%2 != 0);

        pthread_mutex_lock(&lock);

        if(data%2)
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("Par: %d   %d\n",nr_random,data);
            //printf("even %d\n",data++);
            data++;
            nrs->numere_pare++;
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);    // should come outside else as mutex is locked above if
    }
    pthread_exit(&data);
}

void * odd(void *a)
{
    int nr_random;
    srand(time(NULL));
    Numere *nrs;
    nrs = (Numere *) a;
     while(data < 200 && nrs->numere_impare < 100)
    {
        do{

         nr_random = rand() % 10;
        }while(nr_random %2 == 0);
        pthread_mutex_lock(&lock);

        if(!(data%2))
            pthread_cond_wait(&cond,&lock);
        else
        {
           printf("Impar: %d %d\n",nr_random,data);
           //printf("odd %d\n",data++);
           data++;
            nrs->numere_impare++;
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);
    }
    pthread_exit(&data);
}


int main()
{
    Numere nrs;
    nrs.numere_pare = 0;
    nrs.numere_impare = 0;
    nrs.numere_adaugate =0;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,even, (void*)&nrs);
    pthread_create(&tid[1],NULL,odd, (void*)&nrs);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    printf("Numere pare: %d numere impare: %d", nrs.numere_pare, nrs.numere_impare);
    return 0;
}

           