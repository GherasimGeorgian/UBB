Write a program that receives strings of alphanumeric characters as command line arguments (validation is not required). For each string the program creates a thread which calculates the number of digits, the number of consonants and the number of vowels. The thread adds the results to three global variables, one for digits, one for vowels and one for consonants. The main program prints the end results (total number of digits, vowels and consonants across all the received command line arguments) and terminates. Use efficient synchronization.

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <string.h>

typedef struct _CharFile{

   int numar_argumente;
   char** argumente;

} CharFile;

pthread_mutex_t count = PTHREAD_MUTEX_INITIALIZER;

void *CountFile(void *thread);

int numar_cifre=0,numar_vocale=0,numar_consoane=0;

int main(int argc, const char * argv[])
{
  CharFile cf;
  cf.argumente = malloc((argc-1) * sizeof(char*));
  cf.numar_argumente = argc-1;

  printf("Ai introdus %d argumente\n",cf.numar_argumente);

   int i;
   for(i=0;i<cf.numar_argumente;i++)
    {
     cf.argumente[i] = (char *)malloc(strlen(argv[i+1]) + 1);
     //printf("Argument: %s\n",argv[i+1]);
     strcpy(cf.argumente[i],argv[i+1]);
    }
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

    printf("Total cifre:%d --- total vocale: %d ---- total consoane: %d\n" ,numar_cifre,numar_vocale,numar_consoane);

 return 0;
}
int n=0;
bool isVowel(char ch)
{
    ch = toupper(ch);
    return (ch=='A' || ch=='E' || ch=='I' ||
                       ch=='O' || ch=='U');
}

void *CountFile(void *thread){

    CharFile *cf;
    cf=(CharFile *) thread;
    int i;

    pthread_mutex_lock(&count);
         printf("Argument%d: %s \n",n,cf->argumente[n]);
         for(i=0;i<strlen(cf->argumente[n]);i++)
         {
          // printf("%c\n",cf->argumente[n][i]);
          if(cf->argumente[n][i] >= '0' && cf->argumente[n][i]<= '9')
            {
            numar_cifre++;
            }
          else if(isVowel(cf->argumente[n][i]))
             {
              numar_vocale++;
             }
         else
             {
             numar_consoane++;
             }
         }
         n++;
    pthread_mutex_unlock(&count);
}
             
