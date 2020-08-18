#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

typedef struct _CharFile{
   char*output;
   int CharInFile;
   char litera;
   FILE * Read;
} CharFile;


int readfile (FILE * Read)
{
int c = 0;
int x;
CharFile cf;
    do {
        c = 0;
        c = fgetc(Read);
        if (c != EOF) {
            cf.output = (char *) realloc (cf.output, (cf.CharInFile + 1) * sizeof(char));
            cf.output[cf.CharInFile] = c;// printf("%c", cf.output[cf.CharInFile]);
            cf.CharInFile++;
        }
    } while (c != EOF);
    printf("%s\n", cf.output);
    printf("%d",cf.CharInFile);
    return 0;

}

int main(void)
{
  CharFile cf;
  cf.litera='a';
  cf.output= NULL;
  cf.CharInFile=0;
  cf.Read = fopen("fisier2.txt", "r");

fclose(cf.Read);



  return 0;
}





