#include "em_emu.h"
#include "em_cmu.h"

#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/resetReason.h"
#include "XDRONE/02_Middlewares/OS/inc/OS.h"

/**********************************************
 * 
 *********************************************/

typedef enum {
    SOURCE_NONE,
    SOURCE_TASK,
    SOURCE_INTERRUPT,
}reset_oferflowSource_e;

/**********************************************
 * 
 *********************************************/

static __attribute__((section(".retained.source"))) fault_type_e source;
static __attribute__((section(".retained.addr"))) uint32_t addr;
static __attribute__((section(".retained.CFSR"))) uint32_t CFSR;
static __attribute__((section(".retained.MMFAR"))) uint32_t MMFAR;
static __attribute__((section(".retained.BFAR"))) uint32_t BFAR;
static __attribute__((section(".retained.overflowSource"))) reset_oferflowSource_e overflowSource;
static __attribute__((section(".retained.taskName"))) char taskName[50];

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/

static void __used saveAndReset(fault_type_e type, uint32_t returnAddress, uint32_t psplim, uint32_t msplim){
    source = type;
    addr = returnAddress;

	uint32_t volatile psp = 0, msp = 0;
	__asm volatile ("mrs %[out], psp" : [out] "=r" (psp));
	__asm volatile ("mrs %[out], msp" : [out] "=r" (msp));

    if(psp <= psplim && psp != 0)
        overflowSource = SOURCE_TASK;
    else if(msp <= msplim && msp != 0)
        overflowSource = SOURCE_INTERRUPT;

    CFSR = OS_SYSTEM_CTRL->CFSR;
    MMFAR = OS_SYSTEM_CTRL->MMFAR;
    BFAR = OS_SYSTEM_CTRL->BFAR;

    if(os_task_getCurrentTask() != NULL)
        strncpy(taskName, os_task_getCurrentTask()->obj.name, sizeof(taskName));

    NVIC_SystemReset();
}

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

    /* Save FPU context
	------------------------------------------------------*/
    __asm volatile ("add r1, sp, #24");
    __asm volatile ("ldr r1, [r1]");
    __asm volatile ("b saveAndReset");
} 

/**********************************************
 * FAULT HANDLERS
 *********************************************/

void __naked HardFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_HARDFAULT) : "r0");
    __asm volatile("b fault_handler");
}

void __naked MemManage_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_MEMMANAGE) : "r0");
    __asm volatile("b fault_handler");
}

void __naked BusFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_BUSFAULT) : "r0");
    __asm volatile("b fault_handler");
}

void __naked UsageFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_USAGEFAULT) : "r0");
    __asm volatile("b fault_handler");
}

void __naked SecureFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_SECUREFAULT) : "r0");
    __asm volatile("b fault_handler");
}

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

void resetReason(void){
    uint32_t resetCause = EMU->RSTCAUSE;

    PRINTF("\n\n");
    PRINTLN("------------------------------------------------");
    PRINTLN("MCU Boot! Sysclk: %ld\n", CMU_ClockFreqGet(cmuClock_SYSCLK));
    PRINTLN("Reset cause(s):");

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
    if(resetCause & EMU_RSTCAUSE_POR)         PRINTLN("   (POR): Power-on reset");
    if(resetCause & EMU_RSTCAUSE_SETAMPER)    PRINTLN("   (TAMP): SE Tamper");
    if(resetCause & EMU_RSTCAUSE_SYSREQ)      PRINTLN("   (SYS): Cortex System Request");
    if(resetCause & EMU_RSTCAUSE_VREGIN)      PRINTLN("   (VREG): VREGIN");

    PRINTLN("");
    PRINTLN("");
    PRINTLN("Source : %d, CFSR=0x%08X, MMFAR=0x%08X, BFAR=0x%08X, OF = %d, name = %s", source, CFSR, MMFAR, BFAR, overflowSource, taskName);
    PRINTLN("");
    PRINTLN("------------------------------------------------\n\n");
    EMU->CMD = EMU_CMD_RSTCAUSECLR;
}