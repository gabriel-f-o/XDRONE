
#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/motor.h"

/**********************************************
 * DEFINES
 *********************************************/

#define MOTOR_PWM_FREQ_HZ     1000000

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/

__STATIC_INLINE uint32_t TIMER_CompareGet(TIMER_TypeDef *timer, unsigned int ch){
#if defined (_TIMER_CC_CFG_MASK)
  EFM_ASSERT(timer->EN & TIMER_EN_EN);
  return timer->CC[ch].OC;
#else
  return timer->CC[ch].CCV = val;
#endif
}

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

/***********************************************************************
 * Motor Set power
 *
 * @brief sets current motor power from 0 to 1000
 * 
 * @param motor_e motor        : [in] Which motor to get
 * @param uint16_t power_per1k : [in] Power from 0 to 1000
 **********************************************************************/
void motor_setPower(motor_e motor, uint16_t power_per1k){
    if(motor == MOTOR_UP_LEFT)      TIMER_CompareSet(TIMER0, 0, power_per1k);
    if(motor == MOTOR_UP_RIGHT)     TIMER_CompareSet(TIMER1, 1, power_per1k);
    
    if(motor == MOTOR_DOWN_LEFT)    TIMER_CompareSet(TIMER0, 1, power_per1k);
    if(motor == MOTOR_DOWN_RIGHT)   TIMER_CompareSet(TIMER1, 0, power_per1k);
}

/***********************************************************************
 * Motor Get power
 *
 * @brief Returns current motor power from 0 to 1000
 * 
 * @param motor_e motor : [in] Which motor to get
 * 
 * @return uint16_t : Current power from 0 to 1000
 **********************************************************************/
uint16_t motor_getPower(motor_e motor){
    if(motor == MOTOR_UP_LEFT)      return TIMER_CompareGet(TIMER0, 0);
    if(motor == MOTOR_UP_RIGHT)     return TIMER_CompareGet(TIMER1, 1);
    
    if(motor == MOTOR_DOWN_LEFT)    return TIMER_CompareGet(TIMER0, 1);
    if(motor == MOTOR_DOWN_RIGHT)   return TIMER_CompareGet(TIMER1, 0);

    return 0;
}

/***********************************************************************
 * Motor init
 *
 * @brief Init Motor driver
 * 
 **********************************************************************/
void motor_init(void)
{
    /* Enable peripheral clocks
    ---------------------------------------------------*/
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_TIMER0, true);
    CMU_ClockEnable(cmuClock_TIMER1, true);

    /* Force all gpio to output 0 (off)
    ---------------------------------------------------*/
    GPIO_PinModeSet(MOTOR_UP_LEFT_PORT,     MOTOR_UP_LEFT_PIN,      gpioModePushPull, 0);
    GPIO_PinModeSet(MOTOR_UP_RIGHT_PORT,    MOTOR_UP_RIGHT_PIN,     gpioModePushPull, 0);
    GPIO_PinModeSet(MOTOR_DOWN_LEFT_PORT,   MOTOR_DOWN_LEFT_PIN,    gpioModePushPull, 0);
    GPIO_PinModeSet(MOTOR_DOWN_RIGHT_PORT,  MOTOR_DOWN_RIGHT_PIN,   gpioModePushPull, 0);

    /* Create pwm init structure
    ---------------------------------------------------*/
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;

    timerInit.enable = false;
    timerInit.prescale = CMU_ClockFreqGet(cmuClock_TIMER1) / MOTOR_PWM_FREQ_HZ - 1;
    timerCCInit.mode = timerCCModePWM;

    /* Init timer
    ---------------------------------------------------*/
    TIMER_Init(TIMER0, &timerInit);
    TIMER_Init(TIMER1, &timerInit);

    /* Enable Timer to control GPIOs
    ---------------------------------------------------*/
    GPIO->TIMERROUTE[0].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN | GPIO_TIMER_ROUTEEN_CC1PEN;
    GPIO->TIMERROUTE[1].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN | GPIO_TIMER_ROUTEEN_CC1PEN;

    /* Set timers channels
    ---------------------------------------------------*/
    GPIO->TIMERROUTE[0].CC0ROUTE = (TIMER0_CC0_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (TIMER0_CC0_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
    GPIO->TIMERROUTE[0].CC1ROUTE = (TIMER0_CC1_PORT << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (TIMER0_CC1_PIN << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);

    GPIO->TIMERROUTE[1].CC0ROUTE = (TIMER1_CC0_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (TIMER1_CC0_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
    GPIO->TIMERROUTE[1].CC1ROUTE = (TIMER1_CC1_PORT << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (TIMER1_CC1_PIN << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
    
    /* Init all channels as pwm
    ---------------------------------------------------*/
    TIMER_InitCC(TIMER0, 0, &timerCCInit);
    TIMER_InitCC(TIMER0, 1, &timerCCInit);
    TIMER_InitCC(TIMER1, 0, &timerCCInit);
    TIMER_InitCC(TIMER1, 1, &timerCCInit);

    /* Set compare as 0 to turn all off
    ---------------------------------------------------*/
    TIMER_TopSet(TIMER0, 1000);
    TIMER_TopSet(TIMER1, 1000);

    motor_setPower(MOTOR_UP_LEFT, 0);
    motor_setPower(MOTOR_UP_RIGHT, 0);

    motor_setPower(MOTOR_DOWN_LEFT, 0);
    motor_setPower(MOTOR_DOWN_RIGHT, 0);

    /* Enable timer
    ---------------------------------------------------*/
    TIMER_Enable(TIMER0, true);
    TIMER_Enable(TIMER1, true);
}