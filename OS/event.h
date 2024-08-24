#ifndef EVENT_H
#define EVENT_H
#include "ktypes.h"
typedef struct event_node
{
   int eid;
   int time;
   int rem_time;
   struct event_node *next;
}event_node_t;

typedef struct event_list
{
   int count;
   event_node_t *head;
   event_node_t *last;
}event_list_t;

int dispatch_event(ppid_t pid, int event, int time);
#endif
