typedef struct _CharFile{

    char litera;
    char *fileName;
    int counter;
    FILE *in;
    char car_citit;
    char litere[100];
} CharFile;


cf.litera = argv[1][0];


cf.fileName = (char *)argv[2];

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