#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _CharFile{

    char litera;
    char *fileName;

} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;
int sum = 0;

void *CountFile(void *threadarg);

int main(int argc, const char * argv[]) {

    pthread_t threads[10];
    int chck, t;
    CharFile cf;

    if (argc <= 2){

        perror("Wrong inputs: need to select a letter and one or more files\n");
        exit(EXIT_FAILURE);

    } else if (argc > 51) {

        perror("Too many files\n");
        exit(EXIT_FAILURE);

    }

     cf.litera = argv[1][0];
     printf("Litera introdusa este :%c \n",cf.litera);
     cf.fileName = (char *)argv[2];
     printf("Fisierul este: %s \n",cf.fileName);

     for(t=0;t<10;t++){
         chck = pthread_create(&threads[t], NULL, CountFile, (void *)&cf);
     }
      if (chck){
            printf("ERROR; return code from pthread_create() is %d\n", chck);
            exit(EXIT_FAILURE);
        }


    for(t=0;t<10;t++)
   {
        pthread_join(threads[t], NULL);
   }
    printf("%lld occurrences of the letter %c in %lld threads\n", (long long)sum, argv[1][0], (long long)argc-2);

    return 0;
}

void *CountFile(void *threadarg){

    FILE *in;
    CharFile *cf;
    char c;
    int counter = 0;

    cf = (CharFile *) threadarg;
    in = fopen(cf->fileName, "r");

    if (in == NULL){

        perror("Error opening the file!\n");
        pthread_exit(NULL);

    }

    while (fscanf(in, "%c", &c) != EOF){

        if(c == cf->litera){

            counter ++;

        }

    }

    fclose(in);

    pthread_mutex_lock(&count);
    sum += counter;
    printf("%d sum value, %d counter value \n", sum, counter);
    pthread_mutex_unlock(&count);

//    pthread_exit(NULL);
}


