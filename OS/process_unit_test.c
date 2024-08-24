#include <stdio.h>
#include "process.h"
#include "utils.h"

void *proc_entry(void *arg)
{
   char *print_string = (char *) arg;
   printf("%s\n",print_string);
}

typedef struct proc_table
{
   ppid_t pid;
   char *name;
   int priority;
   proc_entry_t proc_entry;
   void *arg;
}proc_table_t;

proc_table_t test_procs[] ={
   {0, "P1", 1, proc_entry, (void *)"Running process 1"},
   {0, "P2", 1, proc_entry, (void *)"Running process 2"},
   {0, "P3", 1, proc_entry, (void *)"Running process 3"},
   {0, "P4", 1, proc_entry, (void *)"Running process 4"}
};

int test_proc_mgr_create_process()
{
  print_proc(READY);
  for(int i=0; i<FOR_ITEMS_IN(test_procs); i++)
  { 
     create_process(&test_procs[i].pid, test_procs[i].name, test_procs[i].priority,
          test_procs[i].proc_entry, test_procs[i].arg);
  }
  print_proc(READY);
  return 0;
}

int test_proc_mgr_send_event()
{
   print_event_pid(0);
   dispatch_event(0, 5, 10);
   dispatch_event(0, 6, 3);
   print_event_pid(0);

   print_event_pid(3);
   dispatch_event(3, 5, 10);
   dispatch_event(3, 6, 3);
   print_event_pid(3);
}

int test_proc_mgr_run_process()
{
  for(int i=0; i<FOR_ITEMS_IN(test_procs); i++)
  { 
     run_process(test_procs[i].pid);
  }
}

int main()
{
   test_proc_mgr_create_process();
   test_proc_mgr_send_event();
   test_proc_mgr_run_process();
   return 0;
}
