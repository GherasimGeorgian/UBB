//Afiseaza numere pare/imp short cu var cond
#include<stdio.h>
#include<pthread.h>
int data =0;

pthread_mutex_t lock;
pthread_cond_t cond;
typedef struct _Numere{

   int ceva;

} Numere;

void * even(void *a)
{   Numere* nrs;
        nrs = (Numere *) a;
    while(data < 30)
    {
        pthread_mutex_lock(&lock);
        if(data%2)
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("even %d\n",data++);
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);    // should come outside else as mutex is locked above if
    }
    pthread_exit(&data);
}

void * odd(void *a)
{    Numere* nrs;
        nrs = (Numere *) a;
    while(data < 30)
    {
        pthread_mutex_lock(&lock);
        if(!(data%2))
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("odd %d\n",data++);
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);
    }
    pthread_exit(&data);
}

int main()
{   Numere nrs;
    nrs.ceva=0;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t tid[2];

    pthread_create(&tid[0],NULL,even, (void*)&nrs);
    pthread_create(&tid[1],NULL,odd, (void*)&nrs);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return 0;
}
