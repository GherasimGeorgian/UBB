#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
int data =0;

typedef struct _Numere{

   int ceva;

} Numere;

pthread_mutex_t lock;
pthread_cond_t cond;

void * al_doilea(void *a)
{  int r=0;
   Numere* nrs;
   nrs = (Numere *) a;
   while(r<2){
        r++;
        pthread_mutex_lock(&lock);
        if(!(data%2))
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("even %d\n",data);
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);    // should come outside else as mutex is locked above if
    }
}

void * primul(void *a)
{
        Numere* nrs;
        nrs = (Numere *) a;
        pthread_mutex_lock(&lock);
        if(data%2)
            pthread_cond_wait(&cond,&lock);
        else
        {
            printf("odd %d\n",data++);
            pthread_cond_signal(&cond);
        }
            pthread_mutex_unlock(&lock);

}
int main()
{
    Numere nrs;
    nrs.ceva=0;
    int check;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t tid[6];


  pthread_create(&tid[0],NULL,primul, (void*)&nrs);


      if(check){
           printf("Error to create thread!\n");
           exit(EXIT_FAILURE);
      }
     int i;

    for(i=1;i<6;i++)
       pthread_create(&tid[i],NULL,al_doilea, (void*)&nrs);


     for(i=0;i<6;i++)
        pthread_join(tid[i], NULL);


    return 0;
}


