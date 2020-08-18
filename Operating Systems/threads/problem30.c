#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _CharFile{

    char litera;
    char *fileName;
    int counter;
    FILE *in;
    char car_citit;
    char litere[100];
} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;
int sum = 0;

void *CountFile(void *threadarg);

int main(int argc, const char * argv[]) {

    pthread_t threads[100];
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
    int j=0;
    while (fscanf(cf.in, "%c", &cf.car_citit) != EOF){
            cf.litere[j]=cf.car_citit;
           j++;
    }

     for(t=0;t<13;t++){
            chck = pthread_create(&threads[t], NULL, CountFile, (void *)&cf);

     }
      if (chck){
            printf("ERROR; return code from pthread_create() is %d\n", chck);
            exit(EXIT_FAILURE);
        }

   fclose(cf.in);

 for(t=0;t<13;t++)
   {
        pthread_join(threads[t], NULL);
   }
    printf("%lld occurrences of the letter %c in %lld threads\n", (long long)sum, argv[1][0], (long long)argc-2);

    return 0;
}

void *CountFile(void *threadarg){

   CharFile *cf;
   cf=(CharFile *) threadarg;

//          printf("Fissiisfs %s",cf->fileName);


        //if(cf->car_citit == cf->litera){
           printf("Caracter%c   \n",cf->litere[0]);
        //   cf->counter++;
      //  }
//
    //}

   // pthread_mutex_lock(&count);
    //sum += cf->counter;
    //printf("%d sum value, %d counter value \n", sum, cf->counter);
    //pthread_mutex_unlock(&count);

}

