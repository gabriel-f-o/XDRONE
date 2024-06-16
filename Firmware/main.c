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
#include "XDRONE/02_Middlewares/OS/inc/OS.h"

static volatile int a;

static volatile int b;

void SysTick_Handler(void){
  os_tick(1);
}

int main(void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  app_init();

  led_init();
  led_setColor(LED_COLOR_RED);
  led_setIntesity(10);
  led_setState(1);

  motor_init();

  cli_init();

  PRINTF("\n");
  PRINTLN("Clk: %lu", CMU_ClockFreqGet(cmuClock_SYSCLK));
  PRINTLN_W("WARNING");
  PRINTLN_E("ERROR");

  ASSERT(os_init("main", 20, OS_DEFAULT_STACK_SIZE, "idle", OS_DEFAULT_STACK_SIZE) == OS_ERR_OK);
  os_scheduler_start();
  os_task_sleep(1000);
  
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
