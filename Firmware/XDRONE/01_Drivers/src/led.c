
#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/led.h"

/**********************************************
 * DEFINES
 *********************************************/

#define LED_RED_CH          0
#define LED_GREEN_CH        1
#define LED_BLUE_CH         2

#define LED_PWM_FREQ_HZ     100000

/**********************************************
 * PRIVATE VARIABLES
 *********************************************/

static bool cur_state = 0;                  //Current state (on/off)
static uint8_t cur_intensity_perc = 100;    //Current intensity in porcentage

static uint8_t cur_r;                       //Curent red value
static uint8_t cur_g;                       //Curent green value
static uint8_t cur_b;                       //Curent blue value

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

/***********************************************************************
 * Set RGB insensity
 *
 * @brief Sets RGB intensity from 0 to 100%
 * 
 * @param uint8_t intensity_perc : [in] Percentage of power
 * 
 **********************************************************************/
void led_setIntesity(uint8_t intensity_perc){
    cur_intensity_perc = intensity_perc;
    led_setRGB(cur_r, cur_g, cur_b); 
}

/***********************************************************************
 * Get RGB insensity
 *
 * @brief Gets RGB intensity from 0 to 100%
 * 
 * @return uint8_t : [in] Percentage of power
 * 
 **********************************************************************/
uint8_t led_getIntesity(void){
    return cur_intensity_perc;
}

/***********************************************************************
 * Set RGB state
 *
 * @brief Sets RGB state 0 = off 1 = on
 * 
 * @param bool state : [in] 0 = off; 1 = on
 * 
 **********************************************************************/
void led_setState(bool state){
    cur_state = state;
    led_setRGB(cur_r, cur_g, cur_b);
}

/***********************************************************************
 * Get RGB state
 *
 * @brief Gets RGB state 0 = off 1 = on
 * 
 * @return bool : [in] 0 = off; 1 = on
 * 
 **********************************************************************/
bool led_getState(void){
    return cur_state;
}

/***********************************************************************
 * Toggles RGB state
 *
 * @brief Toggles RGB state
 * 
 **********************************************************************/
void led_toggleState(void){
    led_setState(!cur_state);
}

/***********************************************************************
 * Get RGB color
 *
 * @brief Gets color currently aplied to leds
 * 
 * @param uint8_t* r : [out] Red value or NULL to ignore
 * @param uint8_t* g : [out] Green value or NULL to ignore
 * @param uint8_t* b : [out] Green value or NULL to ignore
 * 
 **********************************************************************/
void led_getRGB(uint8_t* r, uint8_t* g, uint8_t* b)
{
    /* output values
    ---------------------------------------------------*/
    if(r != NULL) *r = cur_r;
    if(g != NULL) *g = cur_g;
    if(b != NULL) *b = cur_b;
}

/***********************************************************************
 * Set RGB color to leds
 *
 * @brief Controls pwm compare registers to change led color
 *
 * @param uint8_t r : [in] Red value
 * @param uint8_t g : [in] Green value
 * @param uint8_t b : [in] Green value
 * 
 **********************************************************************/
void led_setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    /* Store new values
    ---------------------------------------------------*/
    cur_r = r;
    cur_g = g;
    cur_b = b;

    /* Update pwm if state is enabled. Scale the colors to match the desired intensity
    ---------------------------------------------------*/
    uint8_t new_r = (cur_state == true) ? r * cur_intensity_perc / 100 : 0;
    uint8_t new_g = (cur_state == true) ? g * cur_intensity_perc / 100 : 0;
    uint8_t new_b = (cur_state == true) ? b * cur_intensity_perc / 100 : 0;

    TIMER_CompareSet(TIMER2, LED_RED_CH,    new_r);
    TIMER_CompareSet(TIMER2, LED_GREEN_CH,  new_g);
    TIMER_CompareSet(TIMER2, LED_BLUE_CH,   new_b);
}

/***********************************************************************
 * LED init
 *
 * @brief Init led driver
 * 
 **********************************************************************/
void led_init(void)
{
    /* Enable peripheral clocks
    ---------------------------------------------------*/
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_TIMER2, true);

    /* Force all gpio to output 0 (off)
    ---------------------------------------------------*/
    GPIO_PinModeSet(LED_RED_PORT,   LED_RED_PIN,    gpioModePushPull, 0);
    GPIO_PinModeSet(LED_GREEN_PORT, LED_GREEN_PIN,  gpioModePushPull, 0);
    GPIO_PinModeSet(LED_BLUE_PORT,  LED_BLUE_PIN,   gpioModePushPull, 0);

    /* Create pwm init structure
    ---------------------------------------------------*/
    TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
    TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;

    timerInit.enable = false;
    timerInit.prescale = CMU_ClockFreqGet(cmuClock_TIMER2) / LED_PWM_FREQ_HZ - 1;
    timerCCInit.mode = timerCCModePWM;

    /* Init timer
    ---------------------------------------------------*/
    TIMER_Init(TIMER2, &timerInit);

    /* Enable Timer to control GPIOs
    ---------------------------------------------------*/
    GPIO->TIMERROUTE[2].ROUTEEN  = GPIO_TIMER_ROUTEEN_CC0PEN | GPIO_TIMER_ROUTEEN_CC1PEN | GPIO_TIMER_ROUTEEN_CC2PEN;

    /* Set gpio red channel
    ---------------------------------------------------*/
#if LED_RED_CH == 0
    GPIO->TIMERROUTE[2].CC0ROUTE = (LED_RED_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (LED_RED_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
#elif LED_RED_CH == 1
    GPIO->TIMERROUTE[2].CC1ROUTE = (LED_RED_PORT << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (LED_RED_PIN << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
#elif LED_RED_CH == 2
    GPIO->TIMERROUTE[2].CC2ROUTE = (LED_RED_PORT << _GPIO_TIMER_CC2ROUTE_PORT_SHIFT) | (LED_RED_PIN << _GPIO_TIMER_CC2ROUTE_PIN_SHIFT);
#endif

    /* Set gpio green channel
    ---------------------------------------------------*/
#if LED_GREEN_CH == 0
    GPIO->TIMERROUTE[2].CC0ROUTE = (LED_GREEN_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (LED_GREEN_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
#elif LED_GREEN_CH == 1
    GPIO->TIMERROUTE[2].CC1ROUTE = (LED_GREEN_PORT << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (LED_GREEN_PIN << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
#elif LED_GREEN_CH == 2
    GPIO->TIMERROUTE[2].CC2ROUTE = (LED_GREEN_PORT << _GPIO_TIMER_CC2ROUTE_PORT_SHIFT) | (LED_GREEN_PIN << _GPIO_TIMER_CC2ROUTE_PIN_SHIFT);
#endif

    /* Set gpio blue channel
    ---------------------------------------------------*/
#if LED_BLUE_CH == 0
    GPIO->TIMERROUTE[2].CC0ROUTE = (LED_BLUE_PORT << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (LED_BLUE_PIN << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
#elif LED_BLUE_CH == 1
    GPIO->TIMERROUTE[2].CC1ROUTE = (LED_BLUE_PORT << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (LED_BLUE_PIN << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
#elif LED_BLUE_CH == 2
    GPIO->TIMERROUTE[2].CC2ROUTE = (LED_BLUE_PORT << _GPIO_TIMER_CC2ROUTE_PORT_SHIFT) | (LED_BLUE_PIN << _GPIO_TIMER_CC2ROUTE_PIN_SHIFT);
#endif
    
    /* Init all channels as pwm
    ---------------------------------------------------*/
    TIMER_InitCC(TIMER2, LED_RED_CH, &timerCCInit);
    TIMER_InitCC(TIMER2, LED_GREEN_CH, &timerCCInit);
    TIMER_InitCC(TIMER2, LED_BLUE_CH, &timerCCInit);

    /* Set compare as 0 to turn all off and maximum to 256
    ---------------------------------------------------*/
    TIMER_TopSet(TIMER2, 256);
    TIMER_CompareSet(TIMER2, LED_RED_CH, 0);
    TIMER_CompareSet(TIMER2, LED_GREEN_CH, 0);
    TIMER_CompareSet(TIMER2, LED_BLUE_CH, 0);

    /* Enable timer
    ---------------------------------------------------*/
    cur_state = false;
    cur_r = cur_g = cur_b = 0;
    cur_intensity_perc = 100;
    TIMER_Enable(TIMER2, true);
}