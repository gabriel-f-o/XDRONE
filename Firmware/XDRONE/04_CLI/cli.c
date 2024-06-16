#include "sl_cli_handles.h"
#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/motor.h"

/**********************************************
 * EXTERNAL VARIABLES
 *********************************************/

extern sl_cli_command_group_t cli_led_menu;
extern sl_cli_command_group_t cli_motor_menu;

/**********************************************
 * PRIVATE FUNCTIONS
 *********************************************/

static void cli_panic(sl_cli_command_arg_t *arguments){
    (void)arguments;
    
    PRINTLN_E("PANIC!!!");
    motor_setPower(MOTOR_UP_LEFT, 0);
    motor_setPower(MOTOR_UP_RIGHT, 0);
    motor_setPower(MOTOR_DOWN_LEFT, 0);
    motor_setPower(MOTOR_DOWN_RIGHT, 0);
}

/**********************************************
 * PRIVATE VARIABLES
 *********************************************/

static const sl_cli_command_info_t panic =
     SL_CLI_COMMAND(cli_panic, "Stops all motors",
                     NULL,
                     {
                         SL_CLI_ARG_END,
                     });

static sl_cli_command_entry_t cli_main_entry[] = {
     {"p", &panic, false},
     {NULL, NULL, false},
 };

static sl_cli_command_group_t cli_main_group = {
     {NULL},
     false,
     cli_main_entry,
 };

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/


void cli_init(void){
    sl_cli_command_add_command_group(sl_cli_xdrone_handle, &cli_main_group);
    sl_cli_command_add_command_group(sl_cli_xdrone_handle, &cli_led_menu);
    sl_cli_command_add_command_group(sl_cli_xdrone_handle, &cli_motor_menu);
}