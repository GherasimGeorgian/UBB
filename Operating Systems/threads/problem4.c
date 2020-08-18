//Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.
#include<stdio.h>
#include<pthread.h>
#include<time.h>
int data =0;

pthread_mutex_t lock;
pthread_cond_t cond;

typedef struct _Numere{

    int numbers[500];
    int numere_adaugate;
    int dimensiune;

} Numere;

void * even(void *a)
{
   Numere* nrs;
  nrs = (Numere *) a;
   int nr_random;
    srand(time(NULL));


    while(nrs->dimensiune > nrs->numere_adaugate)
    {
      do{
        nr_random = rand()%10;
        }
        while(nr_random % 2 == 0);
        printf("Numar random par: %d\n",nr_random);

        printf("act dim: %d\n", nrs->numere_adaugate);
        pthread_mutex_lock(&lock);
        if(nrs->numere_adaugate%2)
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("even %d\n",data++);
            nrs->numbers[nrs->numere_adaugate]= nr_random;
             nrs->numere_adaugate+=1;
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);    // should come outside else as mutex is locked above if
    }
    pthread_exit(&data);
}



void * odd(void *a)
{
    Numere* nrs;
     nrs = (Numere *) a;
    int nr_random;
    srand(time(NULL));

    while(nrs->dimensiune > nrs->numere_adaugate)
    {
      do{
        nr_random = rand()%10;
       }
       while(nr_random % 2 != 0);
    printf("Numar random impar: %d\n",nr_random);

        pthread_mutex_lock(&lock);
        if(!(nrs->numere_adaugate%2))
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("odd %d\n",data++);
            nrs->numbers[nrs->numere_adaugate] = nr_random;
            nrs->numere_adaugate+=1;
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);
    }
    pthread_exit(&data);
}

int main()
{
    Numere nrs;
    int n;
     scanf("%d", &n);
    nrs.dimensiune = n;
    nrs.numere_adaugate =0;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,even, (void*)&nrs);
    pthread_create(&tid[1],NULL,odd, (void*)&nrs);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);

    printf("\n\n\nResult:\n");
    int i;
    for(i=0;i<n;i++)
    {
      printf("%d ",nrs.numbers[i]);
    }
    return 0;
}


