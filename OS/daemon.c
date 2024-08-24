#include <stdio.h>
#include <unistd.h>
#include "rr.h"
#include "process.h"
#include "event.h"
#include "appinf.h"

int app_thread_create(ppid_t *id, char *name, int priority, proc_entry_t proc_entry, void *arg, sch_algo_t sch_algo, app_thread_state_t start_state)
{
   if(sch_algo != ROUND_ROBIN)
   {
       printf("Scheduler nahi hai\n");
       return -1;
   }
   if(start_state != READY)
   {
       printf("Abhi READY ke alawa dusra start state supported nahi\n");
       return -1;
   }
   if(id == NULL)
   {
      printf("pid null kaise bhej diya\n");
      return -1;
   }
   if(proc_entry == NULL)
   {
      printf("proc_entry null kaise bhej diya\n");
      return -1;
   }
   //TODO: Add more vaildations on range of I/P
   //TODO: Add log kid of like syslog
   int check_success = create_process(id, name, priority, proc_entry, arg);
   if(check_success != 0)
   {
      printf("Thread create failed\n");
      return -1;
   }

   if(start_state == ready)
   {
      rr_sch_add_process(*id);
   }
    
   return 0;
}

int main()
{
   user();
    
   while(1)
   {
     rr_sch_schedule_proc(&pid);
     printf("\nCurrent time=%d/%d\n", rr_sch_get_crnt_time(), rr_sch_get_time_slice());
     rr_sch_print_process();
     rr_sch_tick();
     run_process(pid);
     sleep(TICK_INTERVAL);
   } 
}    
     
