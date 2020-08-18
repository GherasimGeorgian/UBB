#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct _CharFile{
   char*output;
   int CharInFile;
   FILE * Read;
   char aparitii[256];
} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;


void *CountFile(void *thread);

int main(int argc, const char * argv[])
{
  CharFile cf;
  cf.output= NULL;
  cf.CharInFile=0;
  cf.Read = fopen("fisier3.txt", "r");
   int i;
   for(i=0;i<256;i++)
      cf.aparitii[i]=0;


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

   for(t=0;t<cf.CharInFile;t++)
   {
        pthread_join(threads[t], NULL);
   }
    for(i=0;i<256;i++)
      if(cf.aparitii[i]!=0)
          printf("Caracterul %c  apare de %d in fisierul \n",i,cf.aparitii[i]);
    free(cf.output);
  return 0;
}


int n=0;
void *CountFile(void *thread){

    CharFile *cf;
   cf=(CharFile *) thread;
    pthread_mutex_lock(&count);
         cf->aparitii[cf->output[n]]+=1;
         n++;
    pthread_mutex_unlock(&count);
}


