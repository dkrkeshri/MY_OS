#include "process.h"
#include "utils.h"

#define DEFAULT_TIME_SLICE 5
#define MIN_TIME_SLICE 1
#define MAX_TIME_SLICE 100
#define TICK_INTERVAL 1


typedef struct rr_sch_process_node
{
   ppid_t pid;
   struct rr_sch_process_node *next;
}rr_sch_process_node_t;

typedef struct rr_sch_process_list
{
   int count;
   struct rr_sch_process_node *head;
   struct rr_sch_process_node *last;
   struct rr_sch_process_node *crnt;
}rr_sch_process_list_t;

int rr_sch_schedule_proc(ppid_t *pid);
int rr_sch_set_time_slice(int _time_slice);
int rr_sch_get_time_slice();
int rr_sch_add_process(ppid_t pid);
int rr_sch_delete_process(ppid_t pid);
int rr_sch_print_process();
rr_sch_process_node_t const * const rr_sch_get_crnt_process();
int rr_sch_tick();
int rr_sch_get_crnt_time();
void rr_sch_trigger_scheduler();
