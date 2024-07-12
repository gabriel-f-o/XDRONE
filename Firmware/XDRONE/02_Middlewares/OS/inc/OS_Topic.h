#ifndef __OS_TOPIC_H__
#define __OS_TOPIC_H__

#include "OS_Obj.h"

typedef struct os_topic_{
	os_obj_t  obj;				//Base object (must be first member)
    void*     msgQlist;
} os_topic_t;


#endif //__OS_TOPIC_H__