#include <stdio.h>
#include "rr.h"

int rr_sch_time_slice = DEFAULT_TIME_SLICE;
int rr_sch_crnt_time;
rr_sch_process_list_t rr_sch_process_list = {.count=0, .head=NULL, .last=NULL, .crnt=NULL};

int rr_sch_get_crnt_time()
{
   return rr_sch_crnt_time;
}

int rr_sch_tick()
{
   rr_sch_crnt_time++;
   if(rr_sch_crnt_time == rr_sch_time_slice)
   {
       rr_sch_crnt_time = 0;
   }
}

int rr_sch_schedule_proc(ppid_t *pid)
{
    if(rr_sch_process_list.head == NULL)
    {
       printf("ka kare head null hai\n");
       return 1;
    }
    if(rr_sch_crnt_time == 0)
    {
        if(rr_sch_process_list.crnt == NULL)
        {
           rr_sch_process_list.crnt = rr_sch_process_list.head;
        }
        else if(rr_sch_process_list.crnt == rr_sch_process_list.last)
        {
           rr_sch_process_list.crnt = rr_sch_process_list.head;
        }
        else
        {
           rr_sch_process_list.crnt = rr_sch_process_list.crnt->next;
        }
    }
    *pid = rr_sch_process_list.crnt->pid;
    return 0;
}

// sets the rr sch time slice between MIN_TIME_SLICE and MAX_TIME_SLICE,
// including MIN_TIME_SLICE and MAX_TIME_SLICE
int rr_sch_set_time_slice(int _time_slice)
{
   if(_time_slice > MAX_TIME_SLICE)
   {
      return 1;
   }
   if(_time_slice < MIN_TIME_SLICE)
   {
      return 1;
   }
   rr_sch_time_slice = _time_slice;
   return 0;
}

int rr_sch_get_time_slice()
{
   return rr_sch_time_slice;
}

int rr_sch_add_process(ppid_t pid)
{
   // Create node
   rr_sch_process_node_t *node=NULL; 
   RR_SCH_ALLOC_HEAP_MEM(node, sizeof(rr_sch_process_node_t));
   node->next = NULL;
   node->pid = pid;

   if(rr_sch_process_list.head == NULL)
   {
      rr_sch_process_list.head = node;
   }
   else
   {
      rr_sch_process_list.last->next = node;
   }
 
   // The currently created node will be the last node
   rr_sch_process_list.last = node;
   rr_sch_process_list.count++;
}

int rr_sch_print_process()
{
   rr_sch_process_node_t *node = rr_sch_process_list.head;
   printf("PID count = %d\n",rr_sch_process_list.count);
   while(node)
   {
      printf("%d",node->pid);
      if(node == rr_sch_process_list.crnt)
      {
          printf(" *");
      }
      printf("\n");
      node = node->next;
   }
}

rr_sch_process_node_t const * const rr_sch_get_crnt_process()
{
    return rr_sch_process_list.crnt;
}

void rr_sch_trigger_scheduler()
{
}
