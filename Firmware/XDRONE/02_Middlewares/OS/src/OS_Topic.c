/*
 * OS_Topic.c
 *
 *  Created on: Jun 30, 2024
 *      Author: Gabriel
 */

#include "../inc/OS.h"
#include "../inc/OS_Internal.h"

/**********************************************
 * PRIVATE TYPES
 *********************************************/

/* Message Queue list structure
------------------------------------------------------*/
typedef struct{
    os_handle_t associated_task;
    os_handle_t msgQ;
} os_topic_msgQList_el_t;

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/

/***********************************************************************
 * OS Search task in list
 *
 * @brief Searches for a given task inside the os_topic_msgQList_el_t list 
 *
 * @param os_list_head_t* head : [in] List head
 * @param os_handle_t task     : [in] Task to search
 *
 * @return os_topic_msgQList_el_t* : Reference to the element containing the task or NULL if not found
 **********************************************************************/
static os_topic_msgQList_el_t* os_topic_searchTaskInList(os_list_head_t* head, os_handle_t task){
    /* Iterate message queue list
	------------------------------------------------------*/
    os_list_cell_t* it = head->head.next;
	while(it != NULL && it->element != NULL){
        os_topic_msgQList_el_t* el = (os_topic_msgQList_el_t*)it->element;

        /* Task was found, return it
	    ------------------------------------------------------*/
        if(el->associated_task == task)
            return it->element;

		it = it->next;
	}

	/* Task not found
    ------------------------------------------------------*/
    return NULL;
}


/***********************************************************************
 * OS topic get free count
 *
 * @brief Gets the amount of times the topic can pop before blocking
 *
 * @param os_handle_t h : [in] object to verify the availability
 *
 * @return uint32_t : the amount of times the object can be taken
 *
 **********************************************************************/
static uint32_t os_topic_getFreeCount(os_handle_t h, os_handle_t takingTask){
	
    UNUSED_ARG(h);

    os_topic_t* t = (os_topic_t*) h;
    os_topic_msgQList_el_t* el = os_topic_searchTaskInList(t->msgQlist, takingTask);
    if(el == NULL)
        return 0xFFFFFFFF;

    return el->msgQ->getFreeCount(el->msgQ, takingTask);
}


/***********************************************************************
 * OS topic take
 *
 * @brief Unused. Just to prevent crashes
 *
 * @param os_handle_t h 			: [in] object to take
 * @param os_handle_t takingTask	: [in] handle to the task that is taking the object
 *
 * @return os_err_e : 0 if OK
 **********************************************************************/
static os_err_e os_topic_objTake(os_handle_t h, os_handle_t takingTask){
	UNUSED_ARG(h);
	UNUSED_ARG(takingTask);
    return OS_ERR_OK;
}



/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

/***********************************************************************
 * OS Topic create
 *
 * @brief Creates a new topic
 *
 * @param os_handle_t* h : [out] Topic handle
 * @param char* name     : [ in] Topic name or NULL to create an nameless topic
 *
 * @return os_err_e error code (0 = OK)
 **********************************************************************/
os_err_e os_topic_create(os_handle_t* h, char const * name)
{
    /* Arg check
	------------------------------------------------------*/
    if(h == NULL) 			        return OS_ERR_BAD_ARG;
    if(name == NULL) 		        return OS_ERR_BAD_ARG;
	if(os_init_get() == false)		return OS_ERR_NOT_READY;

	/* If topic exists, return it
	 ------------------------------------------------------*/
	if(name != NULL){
		os_list_cell_t* obj = os_handle_list_searchByName(&os_obj_head, OS_OBJ_TOPIC, name);
		if(obj != NULL){
			*h = obj->element;
			return OS_ERR_OK;
		}
	}
    /* Alocate topic and return if fail
	------------------------------------------------------*/
    os_topic_t* topic = (os_topic_t*)os_heap_alloc(sizeof(os_topic_t));
    if(topic == NULL)
        return OS_ERR_INSUFFICIENT_HEAP;

    /* Init topic structure
	------------------------------------------------------*/
    topic->obj.type			= OS_OBJ_TOPIC;
    topic->obj.objUpdate	= 0;
    topic->obj.getFreeCount	= &os_topic_getFreeCount;
    topic->obj.blockList	= os_list_init();
    topic->obj.obj_take		= &os_topic_objTake;
    topic->obj.name			= name == NULL ? NULL : (char*)os_heap_alloc(strlen(name));

    topic->msgQlist 		= os_list_init();

    /* Handles allocation errors
	------------------------------------------------------*/
    if(topic->msgQlist == NULL || topic->obj.blockList == NULL || (topic->obj.name == NULL && name != NULL)){
        os_list_clear(topic->obj.blockList);
        os_list_clear(topic->msgQlist);
        os_heap_clear(topic->obj.name);
        os_heap_free(topic);

        return OS_ERR_INSUFFICIENT_HEAP;
    }
    
    /* Copy name
    ------------------------------------------------------*/
    strcpy(topic->obj.name, name);

    /* Add object to object list
    ------------------------------------------------------*/
    os_err_e ret = os_list_add(&os_obj_head, (os_handle_t) topic, OS_LIST_FIRST);
    if(ret != OS_ERR_OK) {
        os_list_clear(topic->obj.blockList);
        os_list_clear(topic->msgQlist);
        os_heap_free(topic->obj.name);
        os_heap_free(topic);

        return ret;
    }

    /* Return topic
    ------------------------------------------------------*/
    *h = (os_handle_t)topic;
    return OS_ERR_OK;
}

/***********************************************************************
 * OS Topic Subscribe
 *
 * @brief Subscribe a task to a topic
 *
 * @param os_handle_t topic : [in] topic to subscribe to
 * 
 * @return os_err_e error code (0 = OK)
 **********************************************************************/
os_err_e os_topic_subscribe(os_handle_t topic){

    /* Convert address
    ------------------------------------------------------*/
    os_topic_t* t = (os_topic_t*)topic; 

	/* Check arguments
    ------------------------------------------------------*/
	if(topic == NULL)                   return OS_ERR_BAD_ARG;
	if(topic->type != OS_OBJ_TOPIC)     return OS_ERR_BAD_ARG;

	/* Searches to see if task is already subscribed. If it is, return
    ------------------------------------------------------*/
    os_handle_t cur_task = (os_handle_t) os_task_getCurrentTask();
    if(os_topic_searchTaskInList(t->msgQlist, cur_task) != NULL)
        return OS_ERR_INVALID;

    /* Create messageQ list element
    ------------------------------------------------------*/
    os_topic_msgQList_el_t* el = (os_topic_msgQList_el_t*) os_heap_alloc(sizeof(os_topic_msgQList_el_t));
    if(el == NULL)
        return OS_ERR_INSUFFICIENT_HEAP;

    /* Create messageQ to associate with the task
    ------------------------------------------------------*/
    os_handle_t msgQ;
    os_err_e err = os_msgQ_create(&msgQ, OS_MSGQ_MODE_FIFO, NULL);
    if(err != OS_ERR_OK){
        os_heap_free(el);
        return err;
    }

    /* Associate messageQ with task and add to the msgQ list
    ------------------------------------------------------*/
    el->associated_task = cur_task;
    el->msgQ = msgQ;

    return os_list_add(t->msgQlist, el, OS_LIST_FIRST);
}


void* os_topic_receive(os_handle_t topic, os_err_e* err){
    os_topic_t* t = (os_topic_t*)topic;
    os_handle_t cur_task = (os_handle_t) os_task_getCurrentTask();

    os_topic_msgQList_el_t* el = os_topic_searchTaskInList(t->msgQlist, cur_task);
    if(el != NULL){
        return os_msgQ_pop(el->msgQ, err);
    }

    return NULL;
}

void os_topic_publish(os_handle_t topic, void* msg){
    os_topic_t* t = (os_topic_t*)topic;

    os_list_cell_t* it = ((os_list_head_t*) t->msgQlist)->head.next;
	while(it != NULL && it->element != NULL){
        os_topic_msgQList_el_t* el = (os_topic_msgQList_el_t*)it->element;

        os_msgQ_push(el->msgQ, msg);
        it = it->next;
	}

    if(os_handle_list_updateAndCheck((os_handle_t)t) && os_scheduler_state_get() == OS_SCHEDULER_START) 
        os_task_yeild();

}

os_err_e os_topic_delete(os_handle_t topic){

    /* Check arguments
    ------------------------------------------------------*/
	if(topic == NULL)                   return OS_ERR_BAD_ARG;
	if(topic->type != OS_OBJ_TOPIC)     return OS_ERR_BAD_ARG;

    /* delete every message Q in the list
    ------------------------------------------------------*/
    os_topic_t* t = (os_topic_t*)topic;
    os_list_cell_t* it = ((os_list_head_t*) t->msgQlist)->head.next;

	while(it != NULL){
        os_err_e ret = os_msgQ_delete(((os_topic_msgQList_el_t*)it->element)->msgQ);
        if(ret != OS_ERR_OK)
            return ret;

        it = it->next;
	}

	/* Deletes from obj list
	------------------------------------------------------*/
	os_list_remove(&os_obj_head, topic);

    /* delete topic contents
    ------------------------------------------------------*/
    os_list_clear(t->msgQlist);
    os_list_clear(topic->blockList);

    os_err_e ret = os_heap_free(topic->name);
    if(ret != OS_ERR_OK)
        return ret;

    /* delete topic
    ------------------------------------------------------*/
    return os_heap_free(topic);
}