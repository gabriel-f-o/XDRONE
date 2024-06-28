/***************************************************************************//**
* @file main.c
* @brief main() function.
*******************************************************************************
* # License
* <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
*******************************************************************************
*
* The licensor of this software is Silicon Laboratories Inc. Your use of this
* software is governed by the terms of Silicon Labs Master Software License
* Agreement (MSLA) available at
* www.silabs.com/about-us/legal/master-software-license-agreement. This
* software is distributed to you in Source Code format and is governed by the
* sections of the MSLA applicable to Source Code.
*
******************************************************************************/
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "app.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_system_kernel.h"
#else // SL_CATALOG_KERNEL_PRESENT
#include "sl_system_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT

#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/led.h"
#include "XDRONE/01_Drivers/inc/motor.h"
#include "XDRONE/01_Drivers/inc/resetReason.h"
#include "XDRONE/02_Middlewares/OS/inc/OS.h"

#include "em_emu.h"


void __naked SysTick_Handler(void){
    __asm volatile("push {r0-r12}");
    __asm volatile("pop {r0-r12}");
    __asm volatile("bx lr");
    //os_tick(1);
    /*__asm volatile("push {r0-r12}");
    __asm volatile("push {r0-r12}");
    __asm volatile("push {r0-r12}");*/
}

int main(void)
{
    for(int volatile i = 0; i < 500000; i++) continue;
    // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
    // Note that if the kernel is present, processing task(s) will be created by
    // this call.
    sl_system_init(); 

    /*__asm volatile("mov r0, #105");
    __asm volatile("mov r1, #100");
    __asm volatile("push {r0-r1}");*/


    // Initialize the application. For example, create periodic timer(s) or
    // task(s) if the kernel is present.
    app_init();

    resetReason();

    led_init();
    led_setColor(LED_COLOR_RED);
    led_setIntesity(10);
    led_setState(1);

    //motor_init();


    cli_init();

    PRINTF("\n");
    PRINTLN_W("WARNING");
    PRINTLN_E("ERROR");
    __NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(HardFault_IRQn, 1);
    NVIC_SetPriority(MemoryManagement_IRQn, 1);
    NVIC_SetPriority(SysTick_IRQn, 2);
    NVIC_SetPriority(BusFault_IRQn, 1);
    NVIC_SetPriority(UsageFault_IRQn, 1);





    ASSERT(os_init("main", 20, OS_DEFAULT_STACK_SIZE, "idle", OS_DEFAULT_STACK_SIZE) == OS_ERR_OK);
    //os_scheduler_start();
    //os_task_sleep(1000);

    uint32_t volatile psp = 0, msp = 0;
    __asm volatile ("mrs %[out], psp" : [out] "=r" (psp));
    __asm volatile ("mrs %[out], msp" : [out] "=r" (msp));

    uint32_t volatile psplim = psp - 20;
    uint32_t volatile msplim = msp - 20;
    //__asm volatile ("msr psplim, %[in]" : : [in] "r" (psplim));
    __asm volatile ("msr msplim, %[in]" : : [in] "r" (msplim));

    os_task_wait(1000);


    #if defined(SL_CATALOG_KERNEL_PRESENT)
    // Start the kernel. Task(s) created in app_init() will start running.
    sl_system_kernel_start();
    #else // SL_CATALOG_KERNEL_PRESENT
    while (1) {
        // Do not remove this call: Silicon Labs components process action routine
        // must be called from the super loop.
        sl_system_process_action();

        // Application process.
        app_process_action();

        #if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
        // Let the CPU go to sleep if the system allows it.
        sl_power_manager_sleep();
        #endif
    }
    #endif // SL_CATALOG_KERNEL_PRESENT
}
