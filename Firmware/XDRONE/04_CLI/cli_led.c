
#include "sl_cli_handles.h"
#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/led.h"

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

static void cli_led_state(sl_cli_command_arg_t *arguments)
{
    bool state = sl_cli_get_argument_uint8(arguments, 0) != 0;
    led_setState(state);
    PRINTLN("State              %d", led_getState());
}

static void cli_led_intensity(sl_cli_command_arg_t *arguments)
{
    uint8_t intens = sl_cli_get_argument_uint8(arguments, 0);
    led_setIntesity(intens);
    PRINTLN("Intensity          %d", led_getIntesity());
}

static void cli_led_rgb(sl_cli_command_arg_t *arguments)
{
    uint8_t r = sl_cli_get_argument_uint8(arguments, 0);
    uint8_t g = sl_cli_get_argument_uint8(arguments, 1);
    uint8_t b = sl_cli_get_argument_uint8(arguments, 2);
    
    led_setRGB(r, g, b);

    PRINTLN("R:                 %d", r);
    PRINTLN("G:                 %d", g);
    PRINTLN("B:                 %d", b);
}

static void cli_led_print(sl_cli_command_arg_t *arguments)
{
    (void)arguments;
    uint8_t r, g, b;
    led_getRGB(&r, &g, &b);

    PRINTF("\n");
    PRINTLN("------------------ LED INFO --------------------------------");
    PRINTLN("State              %d", led_getState());
    PRINTLN("Intensity          %d", led_getIntesity());
    PRINTLN("R:                 %d", r);
    PRINTLN("G:                 %d", g);
    PRINTLN("B:                 %d", b);
    PRINTLN("------------------------------------------------------------");

}


 /**********************************************
 * CLI MENU
 *********************************************/

static sl_cli_command_entry_t cli_led_table[];
static const sl_cli_command_info_t cli_led_group = SL_CLI_COMMAND_GROUP(cli_led_table, "Led driver menu");

static sl_cli_command_entry_t cli_led_group_entry[] = {
     {"led", &cli_led_group, false},
     {NULL, NULL, false},
 };

 /**********************************************
 * CLI COMMANDS
 *********************************************/

static const sl_cli_command_info_t led_state =
     SL_CLI_COMMAND(cli_led_state, "Led state command",
                     "Input desired state",
                     {
                         SL_CLI_ARG_UINT8,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t led_intensity =
     SL_CLI_COMMAND(cli_led_intensity, "Led state command",
                     "Input desired Intensity",
                     {
                         SL_CLI_ARG_UINT8,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t led_rgb =
     SL_CLI_COMMAND(cli_led_rgb, "Led state command",
                     "Argument 0:R, 1:G, 2:B",
                     {
                         SL_CLI_ARG_UINT8,
                         SL_CLI_ARG_UINT8,
                         SL_CLI_ARG_UINT8,
                         SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t led_print =
     SL_CLI_COMMAND(cli_led_print, "Led state command",
                     NULL,
                     {
                         SL_CLI_ARG_END,
                     });


static sl_cli_command_entry_t cli_led_table[] = {
     {"state",      &led_state,         false},
     {"intensity",  &led_intensity,     false},
     {"rgb",        &led_rgb,           false},
     {"p_all",      &led_print,         false},
     {NULL, NULL, false},
 };

/**********************************************
 * PUBLIC VARIABLES
 *********************************************/

 sl_cli_command_group_t cli_led_menu = {
     {NULL},
     false,
     cli_led_group_entry,
 };

