#include <stdio.h>
#include <stdlib.h>
#include "appinf.h"

void *thread(void *arg)
{
   int thread_idx = *(int *)arg;
   printf("Thread arg=%d\n",thread_idx);
   return NULL;
}

int test_thread_create()
{
   tid_t id;
   char *name = "Thread1";
   int priority = 1;
   static int idx = 0;
   void *arg = malloc(sizeof(int));
   int *thread_idx = (int *) arg;
   *thread_idx = ++idx;
   sch_algo_t sch_algo = ROUND_ROBIN;
   app_thread_state_t start_state = ready;
   app_thread_create(&id, name, priority, thread, arg, sch_algo, start_state); 
}

void * user(void *arg)
{
   printf("user running\n");
   test_thread_create(); 
   test_thread_create(); 
   test_thread_create(); 
   test_thread_create(); 
}
