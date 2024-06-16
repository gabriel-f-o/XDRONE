#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <stdbool.h>

/**********************************************
 * DEFINES
 *********************************************/

#define LED_COLOR_RED           ( (led_color_t) { .r = 255, .g =   0, .b =   0} )
#define LED_COLOR_GREEN         ( (led_color_t) { .r =   0, .g = 255, .b =   0} )
#define LED_COLOR_BLUE          ( (led_color_t) { .r =   0, .g =   0, .b = 255} )
#define LED_COLOR_WHITE         ( (led_color_t) { .r = 255, .g = 255, .b = 255} )
#define LED_COLOR_BLACK         ( (led_color_t) { .r =   0, .g =   0, .b =   0} )
#define LED_COLOR_ORANGE        ( (led_color_t) { .r = 255, .g = 100, .b =   0} )

/**********************************************
 * PUBLIC TYPES
 *********************************************/

/* Color struct
--------------------------------------------*/
typedef struct led_color_s{
    uint8_t r;  //Red color
    uint8_t g;  //Green color
    uint8_t b;  //Blue color
}led_color_t;

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
void led_setIntesity(uint8_t intensity_perc);

/***********************************************************************
 * Get RGB insensity
 *
 * @brief Gets RGB intensity from 0 to 100%
 * 
 * @return uint8_t : [in] Percentage of power
 * 
 **********************************************************************/
uint8_t led_getIntesity(void);

/***********************************************************************
 * Set RGB state
 *
 * @brief Sets RGB state 0 = off 1 = on
 * 
 * @param bool state : [in] 0 = off; 1 = on
 * 
 **********************************************************************/
void led_setState(bool state);

/***********************************************************************
 * Get RGB state
 *
 * @brief Gets RGB state 0 = off 1 = on
 * 
 * @return bool : [in] 0 = off; 1 = on
 * 
 **********************************************************************/
bool led_getState(void);

/***********************************************************************
 * Toggles RGB state
 *
 * @brief Toggles RGB state
 * 
 **********************************************************************/
void led_toggleState(void);

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
void led_getRGB(uint8_t* r, uint8_t* g, uint8_t* b);

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
void led_setRGB(uint8_t r, uint8_t g, uint8_t b);

/***********************************************************************
 * LED init
 *
 * @brief Init led driver
 * 
 **********************************************************************/
void led_init(void);

/**********************************************
 * PUBLIC INLINE FUNCTIONS
 *********************************************/

/***********************************************************************
 * Set color to leds
 *
 * @brief Controls pwm compare registers to change led color
 *
 * @param led_color_t c : [in] Color structure
 * 
 **********************************************************************/
static inline void led_setColor(led_color_t c){
    led_setRGB(c.r, c.g, c.b);
}

/***********************************************************************
 * Get current color
 *
 * @brief Get current color applied to leds
 *
 * @return led_color_t : Color structure
 **********************************************************************/
static inline led_color_t led_getColor(void){
    led_color_t ret;
    led_getRGB(&ret.r, &ret.g, &ret.b);
    return ret;
}

#endif