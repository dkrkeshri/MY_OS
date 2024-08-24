#include <stdio.h>
#include <unistd.h>
#include "rr.h"
#include "utils.h"

int test_rr_sch_check_time_slice()
{
   int test_time_slice[] = {1,2,3,4,5,-4838, 32434, 101, 0};
   for(int i=0; i < FOR_ITEMS_IN(test_time_slice); i++)
   {
      rr_sch_set_time_slice(test_time_slice[i]);
      int out_time_slice = rr_sch_get_time_slice();
      if(out_time_slice < MIN_TIME_SLICE)
      {
         printf("Error setting time slice=%d < MIN_TIME_SLICE=%d\n", test_time_slice[i], MIN_TIME_SLICE);
      }
      if(out_time_slice > MAX_TIME_SLICE)
      {
         printf("Error setting time slice=%d > MAX_TIME_SLICE=%d\n", test_time_slice[i], MAX_TIME_SLICE);
      }
      int is_time_slice_valid = (test_time_slice[i] < MAX_TIME_SLICE) &&
                                (test_time_slice[i] > MIN_TIME_SLICE) ? TRUE: FALSE;
      if(is_time_slice_valid == TRUE)
      {
         if(out_time_slice != test_time_slice[i])
         {
            printf("Error setting time slice=%d\n", test_time_slice[i]);
         }
      }
      
   }
   return 0;
}

int test_rr_sch_process_list_add()
{
    rr_sch_add_process(0);
    rr_sch_add_process(1);
    rr_sch_add_process(2);
    rr_sch_add_process(3);
}

int test_rr_sch_schedule_proc()
{
    rr_sch_set_time_slice(1);
    ppid_t pid = 0;
    while(1)
    {
       printf("\nCurrent time=%d/%d\n", rr_sch_get_crnt_time(), rr_sch_get_time_slice());
       rr_sch_schedule_proc(&pid);
       rr_sch_print_process();
       rr_sch_tick();
       sleep(TICK_INTERVAL);
    }
}

int main()
{
   test_rr_sch_check_time_slice();
   test_rr_sch_process_list_add();
   test_rr_sch_schedule_proc();
}
