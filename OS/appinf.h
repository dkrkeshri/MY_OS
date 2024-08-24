#include<stdint.h>
typedef uint8_t tid_t;

typedef enum sch_algo
{
  ROUND_ROBIN
}sch_algo_t;

typedef enum app_thread_state
{
  ready,
  supend
}app_thread_state_t;

int app_thread_create(tid_t *id, char *name, int priority, void *(*proc_entry)(void *), void *arg, sch_algo_t sch_algo, app_thread_state_t start_state);

void *user(void *arg);
