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

#include "stdio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "pin_config.h"


int main(void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  app_init();


    printf("Hello drone!\n");
   // GPIO_PinModeSet(LED_RED_PORT, LED_RED_PIN, gpioModePushPull, 1);
    //GPIO_PinModeSet(LED_GREEN_PORT, LED_GREEN_PIN, gpioModePushPull, 1);
   // GPIO_PinModeSet(LED_BLUE_PORT, LED_BLUE_PIN, gpioModePushPull, 1);
#if 01
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_TIMER2, true);

  GPIO_PinModeSet(LED_RED_PORT, LED_RED_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(LED_GREEN_PORT, LED_GREEN_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(LED_BLUE_PORT, LED_BLUE_PIN, gpioModePushPull, 0);

  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
  TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;

  // Do not start counter upon initialization
  timerInit.enable = false;
  timerInit.prescale = 779;

  // Set drive output pin high upon compare match
  timerCCInit.mode = timerCCModePWM;

  TIMER_Init(TIMER2, &timerInit);

  GPIO->TIMERROUTE[2].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN | GPIO_TIMER_ROUTEEN_CC1PEN | GPIO_TIMER_ROUTEEN_CC2PEN;
  GPIO->TIMERROUTE[2].CC0ROUTE = (TIMER2_CC0_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (TIMER2_CC0_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
  GPIO->TIMERROUTE[2].CC1ROUTE = (TIMER2_CC1_PORT << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (TIMER2_CC1_PIN << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
  GPIO->TIMERROUTE[2].CC2ROUTE = (TIMER2_CC2_PORT << _GPIO_TIMER_CC2ROUTE_PORT_SHIFT) | (TIMER2_CC2_PIN << _GPIO_TIMER_CC2ROUTE_PIN_SHIFT);

  TIMER_InitCC(TIMER2, 0, &timerCCInit);
  TIMER_InitCC(TIMER2, 1, &timerCCInit);
  TIMER_InitCC(TIMER2, 2, &timerCCInit);

  // Set the output compare to match at NUM_SECONDS_DELAY counts
  TIMER_TopSet(TIMER2, 999);
  TIMER_CompareSet(TIMER2, 0, 0);
  TIMER_CompareSet(TIMER2, 1, 0);
  TIMER_CompareSet(TIMER2, 2, 0);

  // Now start the TIMER
  TIMER_Enable(TIMER2, true);
#endif
  printf("Hello dr22one!\n");
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
