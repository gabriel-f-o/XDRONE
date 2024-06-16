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
} motor_e;

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
void motor_setPower(motor_e motor, uint16_t power_per1k);

/***********************************************************************
 * Motor Get power
 *
 * @brief Returns current motor power from 0 to 1000
 * 
 * @param motor_e motor : [in] Which motor to get
 * 
 * @return uint16_t : Current power from 0 to 1000
 **********************************************************************/
uint16_t motor_getPower(motor_e motor);

/***********************************************************************
 * Motor init
 *
 * @brief Init Motor driver
 * 
 **********************************************************************/
void motor_init(void);

#endif //__MOTOR_H__