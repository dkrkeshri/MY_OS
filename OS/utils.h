#include <stdlib.h>
#include <assert.h>

#define TRUE  1
#define FALSE 0
#define FOR_ITEMS_IN(x) sizeof(x)/sizeof(x[0])

#define DBG  printf("%s:%u\n",__func__,__LINE__);

#define RR_SCH_ALLOC_HEAP_MEM(ptr, size)   \
{\
   ptr = malloc(size);\
   assert(ptr!=NULL);\
}

#define RR_SCH_FREE_HEAP_MEM(ptr)  free(ptr) 

#define PROC_MGR_ALLOC_HEAP_MEM(ptr, size)   \
{\
   ptr = malloc(size);\
   assert(ptr!=NULL);\
}

#define PROC_MGR_FREE_HEAP_MEM(ptr)  free(ptr) 

#define EVENT_MGR_ALLOC_HEAP_MEM(ptr, size)   \
{\
   ptr = malloc(size);\
   assert(ptr!=NULL);\
}

#define EVENT_MGR_FREE_HEAP_MEM(ptr)  free(ptr) 
