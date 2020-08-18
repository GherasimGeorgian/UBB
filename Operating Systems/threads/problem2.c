//Afiseaza numere pare/imp short cu var cond
#include<stdio.h>
#include<pthread.h>
int data =0;

pthread_mutex_t lock;
pthread_cond_t cond;

void * even(void *tid)
{
    while(data < 30)
    {
        pthread_mutex_lock(&lock);
        if(data%2)
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("Tid %ld even %d\n",pthread_self(),data++);
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);    // should come outside else as mutex is locked above if
    }
    pthread_exit(&data);
}
void * odd()
{
    while(data < 30)
    {
        pthread_mutex_lock(&lock);
        if(!(data%2))
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("Tid %ld odd %d\n",pthread_self(),data++);
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);
    }
    pthread_exit(&data);
}

int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,even, (void*)&tid[0]);
    pthread_create(&tid[1],NULL,odd, (void*)&tid[1]);
    void *ret[2];
    pthread_join(tid[0], &ret[0]);
    pthread_join(tid[1], &ret[1]);
    printf("return value %d \n",*(int*)ret[0]);
    printf("return value %d \n",*(int*)ret[1]);

    return 0;
}


