#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#define N 5
#define M 13
#define SLEEP 4
pthread_mutex_t mutcond;
pthread_cond_t cond;
int linie[N], tren[M], inA[M+1], dinB[M+1];
pthread_t tid[M];
int liniilibere;
time_t start;


void t2s(int *t, int l, char *r) {
    int i;
    char n[10];
    sprintf(r, "[");
    for ( i = 0; i < l; i++) {
        sprintf(n,"%d, ",t[i]);
        strcat(r, n);
    }
    i = strlen(r) - 1;
    if ( r[i] == ' ') r[i - 1] = 0;
    strcat(r, "]");
}
void prinT(char *s, int t) {
    int i;
    char a[200],l[200],b[200];
    for (i = 0; inA[i] != -1; i++);
    t2s(inA, i, a);
    t2s(linie, N, l);
    for (i = 0; dinB[i] != -1; i++);
    t2s(dinB, i, b);
    printf("%s %d\tA:%s\tLines:%s\tB:%s\ttime: %ld\n",s,t,a,l,b,time(NULL)-start);
}

//rutina unui thread
void* trece(void* tren) {
    int i, t, l;
    t = *(int*)tren;
    sleep(1 + rand() % SLEEP); // Modificati timpii de stationare

    pthread_mutex_lock(&mutcond);
    for ( i = 0; inA[i] != -1; i++);
    inA[i] = t;
    prinT("EnterA", t);
    for ( ; liniilibere == 0; ) pthread_cond_wait(&cond, &mutcond);
    for (l = 0; linie[l] != -1; l++);
    linie[l] = t;
    liniilibere--;
    for ( i = 0; inA[i] != t; i++);
    for ( ; i < M; inA[i] = inA[i + 1], i++);
    prinT(" A => B", t);
    pthread_mutex_unlock(&mutcond);

    sleep(1 + rand() % SLEEP);

    pthread_mutex_lock(&mutcond);
    linie[l] = -1;
    liniilibere++;
    for ( i = 0; dinB[i] != -1; i++);
    dinB[i] = t;
    prinT("  OutB", t);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutcond);
}
//main
int main(int argc, char* argv[]) {
    int i;
    start = time(NULL);
    pthread_mutex_init(&mutcond, NULL);
    pthread_cond_init(&cond, NULL);
    liniilibere = N;
    for (i = 0; i < N; linie[i] = -1, i++);
    for (i = 0; i < M; tren[i] = i, i++);
    for (i = 0; i < M + 1; inA[i] = -1, dinB[i] = -1, i++);

    // ce credeti despre ultimul parametru &i?
    for (i=0; i < M; i++) pthread_create(&tid[i], NULL, trece, &tren[i]);
    for (i=0; i < M; i++) pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&mutcond);
    pthread_cond_destroy(&cond);
    return 0;
}



