#ifndef PROCESS_H
#define PROCESS_H
#include "ktypes.h"
#include "event.h"

#define MIN_PID 0
#define MAX_PID 128

typedef enum state
{
   READY,
   SUSPEND
}state_t;

typedef void*(*proc_entry_t)(void *);

typedef struct process
{
  ppid_t pid;
  char *name;
  int priority;
  state_t state;
  proc_entry_t proc_entry;
  void *proc_args;
  event_list_t event_list;
}process_t;
int create_process(ppid_t *pid, char *name, int priority, proc_entry_t proc_entry, void *arg);
int print_proc(state_t state_queue);
int print_event_pid(ppid_t pid);
event_list_t *const get_event_list_for_pid(ppid_t pid);
int run_process(ppid_t pid);
state_t get_proc_state(ppid_t pid);
int set_proc_state(ppid_t pid, state_t state);
#endif
