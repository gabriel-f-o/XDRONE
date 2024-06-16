
#include "sl_cli_handles.h"
#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/motor.h"

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

static void cli_motorUL_pwm(sl_cli_command_arg_t *arguments)
{
    motor_setPower(MOTOR_UP_LEFT, sl_cli_get_argument_uint16(arguments, 0));
    PRINTLN("UP LEFT:                   %d", motor_getPower(MOTOR_UP_LEFT));
}

static void cli_motorUR_pwm(sl_cli_command_arg_t *arguments)
{
    motor_setPower(MOTOR_UP_RIGHT, sl_cli_get_argument_uint16(arguments, 0));
    PRINTLN("UP RIGHT:                  %d", motor_getPower(MOTOR_UP_RIGHT));
}

static void cli_motorDL_pwm(sl_cli_command_arg_t *arguments)
{
    motor_setPower(MOTOR_DOWN_LEFT, sl_cli_get_argument_uint16(arguments, 0));
    PRINTLN("DOWN LEFT:                 %d", motor_getPower(MOTOR_DOWN_LEFT));
}

static void cli_motorDR_pwm(sl_cli_command_arg_t *arguments)
{
    motor_setPower(MOTOR_DOWN_RIGHT, sl_cli_get_argument_uint16(arguments, 0));
    PRINTLN("DOWN RIGHT:                %d", motor_getPower(MOTOR_DOWN_RIGHT));
}

static void cli_motorAll_pwm(sl_cli_command_arg_t *arguments)
{
    motor_setPower(MOTOR_UP_LEFT,     sl_cli_get_argument_uint16(arguments, 0));
    motor_setPower(MOTOR_UP_RIGHT,    sl_cli_get_argument_uint16(arguments, 1));
    motor_setPower(MOTOR_DOWN_LEFT,   sl_cli_get_argument_uint16(arguments, 2));
    motor_setPower(MOTOR_DOWN_RIGHT,  sl_cli_get_argument_uint16(arguments, 3));

    PRINTLN("UP LEFT:                   %d", motor_getPower(MOTOR_UP_LEFT));
    PRINTLN("UP RIGHT:                  %d", motor_getPower(MOTOR_UP_RIGHT));
    PRINTLN("DOWN LEFT:                 %d", motor_getPower(MOTOR_DOWN_LEFT));
    PRINTLN("DOWN RIGHT:                %d", motor_getPower(MOTOR_DOWN_RIGHT));
}

static void cli_motor_print(sl_cli_command_arg_t *arguments)
{
    (void)arguments;

    PRINTF("\n");
    PRINTLN("------------------ MOTOR INFO ---------------------------");
    PRINTLN("UP LEFT:                   %d", motor_getPower(MOTOR_UP_LEFT));
    PRINTLN("UP RIGHT:                  %d", motor_getPower(MOTOR_UP_RIGHT));
    PRINTLN("DOWN LEFT:                 %d", motor_getPower(MOTOR_DOWN_LEFT));
    PRINTLN("DOWN RIGHT:                %d", motor_getPower(MOTOR_DOWN_RIGHT));
    PRINTLN("---------------------------------------------------------");
}


 /**********************************************
 * CLI MENU
 *********************************************/

static sl_cli_command_entry_t cli_motor_table[];
static const sl_cli_command_info_t cli_motor_group = SL_CLI_COMMAND_GROUP(cli_motor_table, "Motor driver menu");

static sl_cli_command_entry_t cli_motor_group_entry[] = {
     {"motor", &cli_motor_group, false},
     {NULL, NULL, false},
 };

 /**********************************************
 * CLI COMMANDS
 *********************************************/

static const sl_cli_command_info_t motorUL_pwm =
     SL_CLI_COMMAND(cli_motorUL_pwm, "Motor Up Left PWM",
                     "PWM from 0 to 1000",
                     {
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t motorUR_pwm =
     SL_CLI_COMMAND(cli_motorUR_pwm, "Motor Up Right PWM",
                     "PWM from 0 to 1000",
                     {
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t motorDL_pwm =
     SL_CLI_COMMAND(cli_motorDL_pwm, "Motor Down Left PWM",
                     "PWM from 0 to 1000",
                     {
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t motorDR_pwm =
     SL_CLI_COMMAND(cli_motorDR_pwm, "Motor Down Right PWM",
                     "PWM from 0 to 1000",
                     {
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t motorAll_pwm =
     SL_CLI_COMMAND(cli_motorAll_pwm, "All Motor PWM",
                     "PWM from 0 to 1000",
                     {
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_UINT16,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t motor_print =
     SL_CLI_COMMAND(cli_motor_print, "Motor current command",
                     NULL,
                     {
                         SL_CLI_ARG_END,
                     });

static sl_cli_command_entry_t cli_motor_table[] = {
     {"ul",     &motorUL_pwm,   false},
     {"ur",     &motorUR_pwm,   false},
     {"dl",     &motorDL_pwm,   false},
     {"dr",     &motorDR_pwm,   false},
     {"all",    &motorAll_pwm,  false},
     {"p_all",  &motor_print,   false},
     {NULL, NULL, false},
 };

/**********************************************
 * PUBLIC VARIABLES
 *********************************************/

 sl_cli_command_group_t cli_motor_menu = {
     {NULL},
     false,
     cli_motor_group_entry,
 };

