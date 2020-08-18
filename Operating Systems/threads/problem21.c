#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct _CharFile{
   char*output;
   int CharInFile;
   int counter;
   char litera;
   FILE * Read;
} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;


void *CountFile(void *thread);

int main(int argc, const char * argv[])
{
  CharFile cf;
  cf.litera=argv[1][0];
  cf.output= NULL;
  cf.CharInFile=0;
  cf.Read = fopen("fisier2.txt", "r");


   int c = 0;
   int x;
    do {
        c = 0;
        c = fgetc(cf.Read);
        if (c != EOF) {
            cf.output = (char *) realloc (cf.output, (cf.CharInFile + 1) * sizeof(char));
            cf.output[cf.CharInFile] = c;// printf("%c", cf.output[cf.CharInFile]);
            cf.CharInFile++;
        }
    } while (c != EOF);
    fclose(cf.Read);
   // printf("%s\n", cf.output);
   // printf("%d",cf.CharInFile);

   pthread_t threads[cf.CharInFile];

    int t;
    int chck;
   for(t=0;t<cf.CharInFile;t++){
            chck = pthread_create(&threads[t], NULL, CountFile, (void *)&cf);

         if (chck){
              printf("ERROR; return code from pthread_create() is %d\n", chck);
              exit(EXIT_FAILURE);
         }
     }
   free(cf.output);
   for(t=0;t<cf.CharInFile;t++)
   {
        pthread_join(threads[t], NULL);
   }

    printf("Caracterul %c  apare de %d in fisierul \n",cf.litera,cf.counter);

  return 0;
}


int n;
void *CountFile(void *thread){

    CharFile *cf;
   cf=(CharFile *) thread;
    pthread_mutex_lock(&count);
          if(cf->output[n] == cf->litera)
               cf->counter++;
          n++;
    pthread_mutex_unlock(&count);
}


