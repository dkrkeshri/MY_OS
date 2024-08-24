#include "semmaphore.h"
#include "rr.h"
#include "process.h"

typedef struct semm_proc_node
{
  ppid_t pid;
  struct semm_proc_node *next;
}semm_proc_node_t;

typedef struct semm_proc_queue
{
  int count;
  semm_proc_node_t *head;
  semm_proc_node_t *last;
}semm_proc_queue_t;

typedef struct semm
{
   int initialized;
   int id;
   volatile int value;
   semm_proc_queue_t *waitQueue;
}semm_t;

semm_t semmaphores[MAX_SEM_COUNT];

int semm_create(int id, int value)
{
   semmaphores[id].initialized = TRUE;
   id = id;
   value = value;
   waitQueue = NULL;
}

int semm_destroy(int id)
{
  semmaphores[id].initialized = FALSE;
}

int semm_wait(int id)
{
   if(semmaphores[id].initialized == FALSE)
   {
       printf("Pahile create karo\n");
       return -1;
   }
   if(semmaphores[id].value <= 0)
   {
      rr_sch_process_node_t *crnt_proc = rr_sch_get_crnt_process();
      set_proc_state(crnt_proc->pid, SUSPEND);
      return 0;
   }
   semmaphores[id].value--;
   return 1;
}

int semm_post(int )
{
   semmaphores[id].value++;
}
