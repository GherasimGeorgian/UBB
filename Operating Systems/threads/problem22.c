#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_SIZE 100

typedef struct _CharFile{

    char litera;
    char *fileName;
    int counter;
    FILE *in;
    char buffer[DEFAULT_SIZE];

} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;
int sum = 0;
size_t l=0;
int n=0;

void *CountFile(void *threadarg);

int main(int argc, const char * argv[]) {

    pthread_t threads[DEFAULT_SIZE];
    int chck, t;
    CharFile cf;

    if (argc <= 2){

        perror("Wrong inputs: need to select a letter and one or more files\n");
        exit(EXIT_FAILURE);

    } else if (argc > 51) {

        perror("Too many files\n");
        exit(EXIT_FAILURE);

    }

cf.counter=0;
     cf.litera = argv[1][0];
     printf("Litera introdusa este :%c \n",cf.litera);
     cf.fileName = (char *)argv[2];
     printf("Fisierul este: %s \n",cf.fileName);

    cf.in = fopen(cf.fileName, "r");

    if (cf.in == NULL){

        perror("Error opening the file!\n");
        pthread_exit(NULL);

    }
    for (l = 0; l < DEFAULT_SIZE; ++l)
    {
       int c = getc(cf.in);

        if (c == EOF)
        {
         cf.buffer[l] = 0x00;
          break;
        }

       cf.buffer[l] = c;
    }


     for(t=0;t<DEFAULT_SIZE;t++){
            chck = pthread_create(&threads[t], NULL, CountFile, (void *)&cf);

     }
      if (chck){
            printf("ERROR; return code from pthread_create() is %d\n", chck);
            exit(EXIT_FAILURE);
        }

   fclose(cf.in);

    for(t=0;t<DEFAULT_SIZE;t++)
   {
        pthread_join(threads[t], NULL);
   }
    printf("%d occurrences of the letter\n", cf.counter);
    return 0;
}

void *CountFile(void *threadarg){

   CharFile *cf;
   cf=(CharFile *) threadarg;

    pthread_mutex_lock(&count);
       //   printf("Car:%c ---> %d\n", cf->buffer[n],n);
          if(cf->buffer[n] == cf->litera)
               cf->counter++;
          n++;
    pthread_mutex_unlock(&count);


}
