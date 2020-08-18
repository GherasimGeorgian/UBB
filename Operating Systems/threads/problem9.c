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