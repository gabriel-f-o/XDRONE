#include "sl_cli_handles.h"
#include "XDRONE/00_Common/inc/common.h"

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

extern sl_cli_command_group_t cli_led_menu;

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

void cli_init(void){
    sl_cli_command_add_command_group(sl_cli_xdrone_handle, &cli_led_menu);
}