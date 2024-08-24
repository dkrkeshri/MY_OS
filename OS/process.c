#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "process.h"
#include "utils.h"

typedef struct process_node
{
   process_t process;
   struct process_node *next;
}process_node_t;

typedef struct ready_list
{
   int count;
   process_node_t *head;
   process_node_t *last;
}ready_list_t;

typedef struct pid_allocator
{
   uint8_t is_allocated;
}pid_allocator_t;

typedef struct process_manager
{
   ready_list_t ready;
   pid_allocator_t pids[MAX_PID];
}process_manager_t;

process_node_t *map_ppid_to_proc_node[MAX_PID] = {0};
process_manager_t process_mgr = {0};

ppid_t generate_pid()
{
   ppid_t running_pid = 0;
   for(;process_mgr.pids[running_pid].is_allocated != 0 && running_pid < MAX_PID; running_pid++);
   assert(running_pid != MAX_PID);
   process_mgr.pids[running_pid].is_allocated = TRUE;
   return running_pid; 
}

int create_process(ppid_t *pid, char *name, int priority, void * (*proc_entry)(void *), void *arg)
{
   process_node_t *proc_node = NULL;
   //create process node
   PROC_MGR_ALLOC_HEAP_MEM(proc_node, sizeof(process_node_t)); 
   proc_node->process.pid = generate_pid();
   PROC_MGR_ALLOC_HEAP_MEM(proc_node->process.name, strlen(name));
   strcpy(proc_node->process.name, name);
   proc_node->process.priority = priority;
   proc_node->process.state = READY;
   proc_node->process.proc_entry = proc_entry;
   proc_node->process.proc_args = arg;
   proc_node->process.event_list.count = 0;
   proc_node->process.event_list.head = NULL;
   proc_node->process.event_list.last = NULL;
   proc_node->next=NULL;

   if(process_mgr.ready.head == NULL)
   {
      process_mgr.ready.head = proc_node;
   }
   else
   {
      process_mgr.ready.last->next = proc_node;
   }

   // The currently created node will be the last node
   process_mgr.ready.last = proc_node;
   process_mgr.ready.count++;
   map_ppid_to_proc_node[proc_node->process.pid] = proc_node;
   *pid = proc_node->process.pid; 
   return 0;
}

int print_proc(state_t state_queue)
{
  process_node_t *queue_node = NULL;
  int count = 0;
  switch(state_queue)
  {
    case READY: queue_node = process_mgr.ready.head;
                count = process_mgr.ready.count;
                break;
    default: printf("Error printing process, state not found:%d",state_queue);
  }
  printf("Printing process list count=%d\n", count); 
  printf("SL_NO\tPID\tNAME\tPRIO\tSTATE\tPROC_ENTRY\tEVENT_COUNT\n");
  int sl_no = 0;
  while(queue_node != NULL)
  {
     printf("%d\t%d\t%s\t%d\t%d\t%p\t%d\n", ++sl_no, queue_node->process.pid,
        queue_node->process.name, queue_node->process.priority, queue_node->process.state,
        queue_node->process.proc_entry, queue_node->process.event_list.count);
     queue_node = queue_node->next;
  }
}

event_list_t *const get_event_list_for_pid(ppid_t pid)
{
   assert(process_mgr.pids[pid].is_allocated == TRUE);
   return &map_ppid_to_proc_node[pid]->process.event_list;
}

int print_event_pid(ppid_t pid)
{
  event_list_t * const el = get_event_list_for_pid(pid);
  int count = el->count;
  printf("\nPrinting event list for pid=%d count=%d\n", pid, count); 
  printf("SL_NO\tEID\tT\tREM_T\n");
  int sl_no = 0;
  event_node_t *event_node = el->head;
  while(event_node != NULL)
  {
     printf("%d\t%d\t%d\t%d\n", ++sl_no, event_node->eid, event_node->time,
         event_node->rem_time);
     event_node = event_node->next;
  }
}

int run_process(ppid_t pid)
{
   void *(*entry)(void *) = map_ppid_to_proc_node[pid]->process.proc_entry;
   void *arg =  map_ppid_to_proc_node[pid]->process.proc_args;
   entry(arg);
   return 0;
}

state_t get_proc_state(ppid_t pid)
{
   return map_ppid_to_proc_node[pid]->process.state;
}
int set_proc_state(ppid_t pid, state_t state)
{
   map_ppid_to_proc_node[pid]->process.state = state;
   return 0;
}
