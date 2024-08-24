#include <stddef.h>
#include "event.h"
#include "process.h"
#include "utils.h"

int dispatch_event(ppid_t pid, int event, int time)
{
   event_node_t *node = NULL;
   EVENT_MGR_ALLOC_HEAP_MEM(node, sizeof(event_node_t));
   node->eid = event;
   node->time = time;
   node->rem_time = time;
   node->next = NULL;

   event_list_t * const el = get_event_list_for_pid(pid);
   if(el->head == NULL)
   {
      el->head = node;
   }
   else
   {
      el->last->next = node;
   }
   el->last = node;
   el->count++;
}

