//Afiseaza numere pare respectiv impare in ordine var cond
//
#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

void *functionCount1();
void *functionCount2();

int count = 0;

#define COUNT_DONE 200

void main()
{
 pthread_t thread1, thread2;
 pthread_create( &thread1, NULL, &functionCount1, NULL);
 pthread_create( &thread2, NULL, &functionCount2, NULL);
 pthread_join( thread1, NULL);
 pthread_join( thread2, NULL);
 exit(0);
}

// Print odd numbers
void *functionCount1()
{
  for(;;) {
   // Lock mutex and then wait for signal to relase mutex
   pthread_mutex_lock( &count_mutex );
   if ( count % 2 != 0 ) {
     pthread_cond_wait( &condition_var, &count_mutex );
   }
   count++;
   printf("Counter value functionCount1: %d\n",count);
   pthread_cond_signal( &condition_var );
   if ( count >= COUNT_DONE ) {
     pthread_mutex_unlock( &count_mutex );
     return(NULL);
   }
   pthread_mutex_unlock( &count_mutex );
 }
}

// print even numbers
void *functionCount2()
{
  for(;;) {
  // Lock mutex and then wait for signal to relase mutex
  pthread_mutex_lock( &count_mutex );
  if ( count % 2 == 0 ) {
    pthread_cond_wait( &condition_var, &count_mutex );
  }
  count++;
  printf("Counter value functionCount2: %d\n",count);
  pthread_cond_signal( &condition_var );
  if( count >= COUNT_DONE ) {
    pthread_mutex_unlock( &count_mutex );
    return(NULL);
  }
  pthread_mutex_unlock( &count_mutex );
 }
}
