#ifndef __MOTOR_H__
#define __MOTOR_H__

/**********************************************
 * PUBLIC TYPES
 *********************************************/

/* Motor enums
--------------------------------------------*/
typedef enum motor_ {
    MOTOR_UP_LEFT,
    MOTOR_UP_RIGHT,
    MOTOR_DOWN_LEFT,
    MOTOR_DOWN_RIGHT,

    __MOTOR_INVALID,
} motor_e;

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

/***********************************************************************
 * Motor Set power
 *
 * @brief sets current motor power from 0 to 100
 * 
 * @param motor_e motor      : [in] Which motor to get
 * @param uint8_t power_perc : [in] Power from 0 to 100
 **********************************************************************/
void motor_setPower(motor_e motor, uint8_t power_perc);

/***********************************************************************
 * Motor Get power
 *
 * @brief Returns current motor power from 0 to 100
 * 
 * @param motor_e motor : [in] Which motor to get
 * 
 * @return uint8_t : Current power from 0 to 100
 **********************************************************************/
uint8_t motor_getPower(motor_e motor);

/***********************************************************************
 * Motor init
 *
 * @brief Init Motor driver
 * 
 **********************************************************************/
void motor_init(void);

#endif //__MOTOR_H__