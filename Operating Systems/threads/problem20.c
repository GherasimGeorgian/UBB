#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct _CharFile{

   int numar_argumente;
   int aparitii[256];
   int numbers[100];

} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;


void *CountFile(void *thread);

int main(int argc, const char * argv[])
{
  CharFile cf;
  cf.numar_argumente = argc-1;
  printf("%d",cf.numar_argumente);
  int i;
  for(i=0;i<cf.numar_argumente;i++)
    {
     int x = atoi(argv[i+1]);
     cf.numbers[i]= x;
    }


   for(i=0;i<256;i++)
      cf.aparitii[i]=0;

   pthread_t threads[cf.numar_argumente];

    int t;
    int chck;
   for(t=0;t<cf.numar_argumente;t++){
            chck = pthread_create(&threads[t], NULL, CountFile, (void *)&cf);

         if (chck){
              printf("ERROR; return code from pthread_create() is %d\n", chck);
              exit(EXIT_FAILURE);
         }
     }

for(t=0;t<cf.numar_argumente;t++)
   {
        pthread_join(threads[t], NULL);
   }
    for(i=0;i<100;i++)
      if(cf.aparitii[i]!=0)
         printf("Caracterul %d  apare de %d in fisierul \n",i,cf.aparitii[i]);
  return 0;
}


int n=0;
void *CountFile(void *thread){

    CharFile *cf;
   cf=(CharFile *) thread;
    pthread_mutex_lock(&count);
        cf->aparitii[cf->numbers[n]]+=1;
         n++;

    pthread_mutex_unlock(&count);
}

