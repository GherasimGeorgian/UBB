// Intr-o frizerie există un frizer, un scaun pentru frizer și n scaune pentru clienți care așteaptă.
// Când nu sunt clienți care așteaptă frizerul stă pe scaunul lui și doarme.
// Când doarme şi apare primul client, frizerul este trezit.
// Dacă apare un client si are loc pe scaun atunci așteaptă, altfel pleacă de la frizerie netuns.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
pthread_mutex_t mutex;
pthread_cond_t somn;
int scauneLibere = N, locTuns = 0, locNou = 0, clientNou = 0, clientTuns = 0;
int scaun[N];

void p(char* s) {
    printf("clientNou: %d, clientTuns: %d, locNou: %d, locTuns: %d, scauneLibere: %d, scaune: [ ", clientNou, clientTuns, locNou, locTuns, scauneLibere);
    for (int i = 0; i < N; i++) printf("%d ", scaun[i]);
    printf(" ]. %s\n", s);
}
void* client(void* a) {
    pthread_mutex_lock(&mutex);
    if (scauneLibere == 0) {
        p("Clientul pleaca netuns!");
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    scaun[locNou] = clientNou;
    locNou = (locNou + 1) % N;
    scauneLibere--;
    p("Clientul a ocupat loc");
    if (scauneLibere == N - 1) pthread_cond_signal(&somn);
    pthread_mutex_unlock(&mutex);
}

void* frizer(void *a) {
    for ( ; ; ) {
        pthread_mutex_lock(&mutex);
        while(scauneLibere == N){
            p("Frizerul doarme");
            pthread_cond_wait(&somn, &mutex);
        }
        clientTuns = scaun[locTuns];
        scaun[locTuns] = 0;
        locTuns = (locTuns + 1) % N;
        scauneLibere++;
        p("Frizerul tunde");
        pthread_mutex_unlock(&mutex);
        sleep(2); // Atat dureaza "tunsul"
    }
}


int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&somn, NULL);
    for (int i = 0; i < N; scaun[i] = 0, i++);
    pthread_t barber;
    pthread_create(&barber, NULL, frizer, NULL);
    for ( ; ; ){
        pthread_t customer;
        sleep(rand() % 3);
        clientNou++;
        pthread_create(&customer, NULL, client, NULL);
    }
    return 0;
}

