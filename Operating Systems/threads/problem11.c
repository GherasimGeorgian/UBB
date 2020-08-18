#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


typedef struct _CharFile{

   int numar_argumente;
   int aparitii[256];
   int numbers[100];

} CharFile;

CharFile cf;
  cf.numar_argumente = argc-1;
  printf("%d",cf.numar_argumente);
  int i;
  for(i=0;i<cf.numar_argumente;i++)
    {
     int x = atoi(argv[i+1]);
     cf.numbers[i]= x;
    }
