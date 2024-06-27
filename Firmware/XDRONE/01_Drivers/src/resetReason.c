#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/resetReason.h"

/**********************************************
 * PRIVATE VARIABLES
 *********************************************/

static __attribute__((section(".retained.source"))) fault_type_e source;
static __attribute__((section(".retained.retAddr"))) uint32_t addr;

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/

static void __used fault_handler(fault_type_e type, uint32_t returnAddress){
    source = type;
    addr = returnAddress;
    NVIC_SystemReset();
}

/**********************************************
 * FAULT HANDLERS
 *********************************************/

void __naked NMI_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_NMI) : "r0");    //R0 = faultType
    __asm volatile("add r1, sp, #24"); //R1 = SP + 24 To get the reference of the address of return
    __asm volatile("ldr r1, [r1]"); //R1 = *R1
    __asm volatile("bl fault_handler");
}

void __naked HardFault_Handler(void){
    
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_HARDFAULT) : "r0");
    __asm volatile("mrs r1, psp"); 	//R1 = PSP
    //__asm volatile("add r1, sp, #24");  //R1 = SP + 24 To get the reference of the address of return
    __asm volatile("ldr r1, [r1]");     //R1 = *R1
    __asm volatile("bl fault_handler");
}

void __naked MemManage_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_MEMMANAGE) : "r0");
    __asm volatile("add r1, sp, #24"); //R1 = SP + 24 To get the reference of the address of return
    __asm volatile("ldr r1, [r1]"); //R1 = *R1
    __asm volatile("bl fault_handler");
}

void __naked BusFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_BUSFAULT) : "r0");
    __asm volatile("add r1, sp, #24"); //R1 = SP + 24 To get the reference of the address of return
    __asm volatile("ldr r1, [r1]"); //R1 = *R1
    __asm volatile("bl fault_handler");
}

void __naked UsageFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_USAGEFAULT) : "r0");
    __asm volatile("add r1, sp, #24"); //R1 = SP + 24 To get the reference of the address of return
    __asm volatile("ldr r1, [r1]"); //R1 = *R1
    __asm volatile("bl fault_handler");
}

void __naked SecureFault_Handler(void){
    __asm volatile("mov r0, %[in]" : : [in] "i" (FAULT_TYPE_SECUREFAULT) : "r0");
    __asm volatile("add r1, sp, #24"); //R1 = SP + 24 To get the reference of the address of return
    __asm volatile("ldr r1, [r1]"); //R1 = *R1
    __asm volatile("bl fault_handler");
}

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

void resetReason(void){
    PRINTLN("Source = %d, ret = 0x%X", source, addr);
}