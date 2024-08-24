#define MAX_SEM_COUNT 32
int semm_create(int id, int value);
int semm_destroy(int id);
int semm_wait(int id);
int semm_post(int id);
