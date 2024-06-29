#ifndef __RESETREASON_H__
#define __RESETREASON_H__

/**********************************************
 * PUBLIC TYPES
 *********************************************/

/* Fault types
--------------------------------------------*/
typedef enum fault_type_{
    FAULT_TYPE_NONE,
    FAULT_TYPE_HARDFAULT,
    FAULT_TYPE_MEMMANAGE,
    FAULT_TYPE_BUSFAULT,
    FAULT_TYPE_USAGEFAULT,
    FAULT_TYPE_SECUREFAULT,

    __FAULT_TYPE_INVALD,
} fault_type_e;

/**********************************************
 * PUBLIC TYPES
 *********************************************/

/***********************************************************************
 * Print reset reason
 *
 * @brief Print reset reason
 * 
 **********************************************************************/
void resetReason(void);

#endif //__RESETREASON_H__