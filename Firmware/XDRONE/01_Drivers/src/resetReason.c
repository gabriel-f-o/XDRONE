#include "em_emu.h"
#include "em_cmu.h"

#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/resetReason.h"
#include "XDRONE/02_Middlewares/OS/inc/OS.h"

/**********************************************
 * PRIVATE TYPES
 *********************************************/

typedef enum {
    SOURCE_NONE,
    SOURCE_TASK,
    SOURCE_INTERRUPT,
}reset_oferflowSource_e;

/**********************************************
 * PRIVATE VARIABLES
 *********************************************/

static __attribute__((section(".retained.source"))) fault_type_e source;
static __attribute__((section(".retained.addr"))) uint32_t addr;
static __attribute__((section(".retained.CFSR"))) uint32_t CFSR;
static __attribute__((section(".retained.MMFAR"))) uint32_t MMFAR;
static __attribute__((section(".retained.BFAR"))) uint32_t BFAR;
static __attribute__((section(".retained.overflowSource"))) reset_oferflowSource_e overflowSource;
static __attribute__((section(".retained.taskName"))) char taskName[50];


static char* fault_names[__FAULT_TYPE_INVALD] = {
    [FAULT_TYPE_NONE]        = "None",
    [FAULT_TYPE_HARDFAULT]   = "HardFault_irq",
    [FAULT_TYPE_MEMMANAGE]   = "MemMenage_irq",
    [FAULT_TYPE_BUSFAULT]    = "BusFault_irq",
    [FAULT_TYPE_USAGEFAULT]  = "UsageFault_irq",
    [FAULT_TYPE_SECUREFAULT] = "Securefault_irq",
};

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/

/***********************************************************************
 * Save information to debug later
 *
 * @brief Save information to debug later
 * 
 * @param fault_type_e type         : [in] Fault type
 * @param uint32_t returnAddress    : [in] Return address
 * @param uint32_t psplim           : [in] psp limit
 * @param uint32_t msplim           : [in] msp limit
 * 
 **********************************************************************/
static void __used saveAndReset(fault_type_e type, uint32_t returnAddress, uint32_t psplim, uint32_t msplim){
    /* Saves source of fault and return address
    ------------------------------------------------------*/
    source = type;
    addr = returnAddress;

    /* Get current PSP and MSP
    ------------------------------------------------------*/
	uint32_t volatile psp = 0, msp = 0;
	__asm volatile ("mrs %[out], psp" : [out] "=r" (psp));
	__asm volatile ("mrs %[out], msp" : [out] "=r" (msp));

    /* Checks if a stack overflow happened and saves source (task or interrupt) 
    ------------------------------------------------------*/
    if(psp <= psplim && psp != 0)
        overflowSource = SOURCE_TASK;
    else if(msp <= msplim && msp != 0)
        overflowSource = SOURCE_INTERRUPT;

    /* Saves register infos
    ------------------------------------------------------*/
    CFSR = OS_SYSTEM_CTRL->CFSR;
    MMFAR = OS_SYSTEM_CTRL->MMFAR;
    BFAR = OS_SYSTEM_CTRL->BFAR;

    /* Saves task name
    ------------------------------------------------------*/
    taskName[0] = '\0';
    if(os_init_get() == 1 && os_task_getCurrentTask() != NULL)
        strncpy(taskName, os_task_getCurrentTask()->obj.name, sizeof(taskName));

    NVIC_SystemReset();
}

/***********************************************************************
 * Handles faults
 *
 * @brief Handles faults
 * 
 **********************************************************************/
static void __naked __used fault_handler(void){
    /* Get stack limit
    ------------------------------------------------------*/
    __asm volatile ("mrs r2, psplim");
    __asm volatile ("mrs r3, msplim");

    /* set stack limit to 0 to avoid stack problems
    ------------------------------------------------------*/
    __asm volatile ("mov r1, #0");
    __asm volatile ("msr psplim, r1");
	__asm volatile ("msr msplim, r1");

    /* Get return address
	------------------------------------------------------*/
    __asm volatile ("add r1, sp, #24");
    __asm volatile ("ldr r1, [r1]");
    __asm volatile ("b saveAndReset");
} 

/**********************************************
 * FAULT HANDLERS
 *********************************************/

/***********************************************************************
 * Handles hardfault
 *
 * @brief Handles hardfault
 * 
 **********************************************************************/
void __naked HardFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_HARDFAULT) : "r0");
    __asm volatile("b fault_handler");
}

/***********************************************************************
 * Handles memmanage
 *
 * @brief Handles memmanage
 * 
 **********************************************************************/
void __naked MemManage_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_MEMMANAGE) : "r0");
    __asm volatile("b fault_handler");
}

/***********************************************************************
 * Handles busfault
 *
 * @brief Handles busfault
 * 
 **********************************************************************/
void __naked BusFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_BUSFAULT) : "r0");
    __asm volatile("b fault_handler");
}

/***********************************************************************
 * Handles usagefault
 *
 * @brief Handles usagefault
 * 
 **********************************************************************/
void __naked UsageFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_USAGEFAULT) : "r0");
    __asm volatile("b fault_handler");
}

/***********************************************************************
 * Handles securefault
 *
 * @brief Handles securefault
 * 
 **********************************************************************/
void __naked SecureFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_SECUREFAULT) : "r0");
    __asm volatile("b fault_handler");
}

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

/***********************************************************************
 * Print reset reason
 *
 * @brief Print reset reason
 * 
 **********************************************************************/
void resetReason(void){
    uint32_t resetCause = EMU->RSTCAUSE;

    /* Print mcu boot and system clock 
    ------------------------------------------------------*/
    PRINTF("\n\n");
    PRINTLN("------------------------------------------------");
    PRINTLN("MCU Boot! Sysclk: %ld\n", CMU_ClockFreqGet(cmuClock_SYSCLK));
    PRINTLN("Reset cause(s):");

    /* Print reset cause informed by the mcu
    ------------------------------------------------------*/
    if(resetCause & EMU_RSTCAUSE_AVDDBOD)     PRINTLN("   (AVBO): AVDD Brown-out");
    if(resetCause & EMU_RSTCAUSE_DECBOD)      PRINTLN("   (DCBO): Decouple Brown-out");
    if(resetCause & EMU_RSTCAUSE_DVDDBOD)     PRINTLN("   (DVBO_01): EM0/1 DVDD Brown-out");
    if(resetCause & EMU_RSTCAUSE_DVDDLEBOD)   PRINTLN("   (DVBO_23): EM2/3 DVDD Brown-out");
    if(resetCause & EMU_RSTCAUSE_EM4)         PRINTLN("   (EM4): EM4 pin wake-up");
    if(resetCause & EMU_RSTCAUSE_IOVDD0BOD)   PRINTLN("   (IVBO): IOVDD Brown-out");
    if(resetCause & EMU_RSTCAUSE_LOCKUP)      PRINTLN("   (LOCK): Cortex Lockup");
    if(resetCause & EMU_RSTCAUSE_WDOG0)       PRINTLN("   (WDG0): Watchdog 0");
    if(resetCause & EMU_RSTCAUSE_WDOG1)       PRINTLN("   (WDG1): Watchdog 1");
    if(resetCause & EMU_RSTCAUSE_PIN)         PRINTLN("   (PIN): Reset pin");
    if(resetCause & EMU_RSTCAUSE_SETAMPER)    PRINTLN("   (TAMP): SE Tamper");
    if(resetCause & EMU_RSTCAUSE_VREGIN)      PRINTLN("   (VREG): VREGIN");
    if(resetCause & EMU_RSTCAUSE_POR)         PRINTLN("   (POR): Power-on reset");

    if(resetCause & EMU_RSTCAUSE_SYSREQ)      
        PRINTLN("   (SYS): Cortex System Request");
    else{
        source = FAULT_TYPE_NONE;
        CFSR = 0;
    }

    PRINTLN("");

    /* Print exception info if needed
    ------------------------------------------------------*/
    if(source != FAULT_TYPE_NONE){
        PRINTLN("");
        PRINTLN_E("Fault Detected! IRQ source = '%s'", fault_names[source]);    
        
        /* Memmanage fault
        ------------------------------------------------------*/
        if(CFSR & OS_CFSR_IACCVIOL || CFSR & OS_CFSR_DACCVIOL || CFSR & OS_CFSR_MUNSTKERR || CFSR & OS_CFSR_MSTKERR || CFSR & OS_CFSR_MLSPERR || CFSR & OS_CFSR_MMARVALID)
        {
            PRINTLN("MemManage Fault cause(s):");
            if(CFSR & OS_CFSR_IACCVIOL)         PRINTLN("   Instruction access violation");
            if(CFSR & OS_CFSR_DACCVIOL)         PRINTLN("   Data access violation");
            if(CFSR & OS_CFSR_MUNSTKERR)        PRINTLN("   Failed to unstack for a return from exception");
            if(CFSR & OS_CFSR_MSTKERR)          PRINTLN("   Failed to stack to exception entry");
            if(CFSR & OS_CFSR_MLSPERR)          PRINTLN("   Float point lazy state preservation error");

            if(CFSR & OS_CFSR_MMARVALID)        PRINTLN("      Addres that caused the exception: 0x%08X", (unsigned int)MMFAR);
            PRINTLN("");
        }

        /* BusFault error
        ------------------------------------------------------*/
        if(CFSR & OS_CFSR_IBUSERR || CFSR & OS_CFSR_PRECISERR || CFSR & OS_CFSR_UNSTKERR || CFSR & OS_CFSR_STKERR || CFSR & OS_CFSR_LSPERR || CFSR & OS_CFSR_BFARVALID)
        {
            PRINTLN("BusFault cause(s):");
            if(CFSR & OS_CFSR_IBUSERR)          PRINTLN("   Instruction bus error");
            if(CFSR & OS_CFSR_PRECISERR)        PRINTLN("   Precise data bus error");
            if(CFSR & OS_CFSR_UNSTKERR)         PRINTLN("   Failed to unstack for a return from exception");
            if(CFSR & OS_CFSR_STKERR)           PRINTLN("   Failed to stack to exception entry");
            if(CFSR & OS_CFSR_LSPERR)           PRINTLN("   Float point lazy state preservation error");

            if(CFSR & OS_CFSR_BFARVALID)        PRINTLN("      Addres that caused the exception: 0x%08X", (unsigned int)BFAR);
            PRINTLN("");
        }

        /* usage fault
        ------------------------------------------------------*/
        if(CFSR & OS_CFSR_UNDEFINSTR || CFSR & OS_CFSR_INVSTATE || CFSR & OS_CFSR_INVPC || CFSR & OS_CFSR_NOCP || CFSR & OS_CFSR_STKOF || CFSR & OS_CFSR_UNALIGNED || CFSR & OS_CFSR_DIVBYZERO)
        {
            PRINTLN("UsageFault cause(s):");
            if(CFSR & OS_CFSR_UNDEFINSTR)       PRINTLN("   Undefined instruction");
            if(CFSR & OS_CFSR_INVSTATE)         PRINTLN("   Invalid state");
            if(CFSR & OS_CFSR_INVPC)            PRINTLN("   Invalid PC");
            if(CFSR & OS_CFSR_NOCP)             PRINTLN("   No coprocessor");

            if(CFSR & OS_CFSR_UNALIGNED)        PRINTLN("   Unaligned data access");
            if(CFSR & OS_CFSR_DIVBYZERO)        PRINTLN("   Division by zero");


            if(CFSR & OS_CFSR_STKOF)
                PRINTLN("   Stack overflow on '%s' task", overflowSource == SOURCE_TASK ? taskName : "Interrupt handle");

            PRINTLN("");
        }

        /* Stack overflow stops exception frame from being pushed. The return address in this case cannot be fetched
        ------------------------------------------------------*/
        if(!(CFSR & OS_CFSR_STKOF)){
            PRINTLN("Exception occured on address 0x%08X", (unsigned int)addr);
            PRINTLN("");
        }
    }
    
    /* Reset variables
    ------------------------------------------------------*/
    PRINTLN("------------------------------------------------\n\n");
    source = FAULT_TYPE_NONE;
    CFSR = 0;
    EMU->CMD = EMU_CMD_RSTCAUSECLR;
}