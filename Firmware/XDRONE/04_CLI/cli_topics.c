
#include "sl_cli_handles.h"
#include "XDRONE/00_Common/inc/common.h"
#include "XDRONE/01_Drivers/inc/motor.h"
#include "XDRONE/02_Middlewares/OS/inc/OS.h"

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

static void* printVbattTask(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    PRINTLN("Task '%s' run", os_task_getCurrentTask()->obj.name);
    os_handle_t vbatt;
    ASSERT_FALSE(os_topic_create(&vbatt, "vbatt"));
    ASSERT_FALSE(os_topic_subscribe(vbatt));

    os_err_e err;
    while(1){
        /*if(os_obj_single_wait(vbatt, OS_WAIT_FOREVER, &err) == vbatt && err == OS_ERR_OK){
            int msg = (int) os_topic_receive(vbatt, &err);
            PRINTLN("Msg received 0x%04X", msg);
        }*/
    }

    os_task_return(NULL);
    return NULL;
}

static void cli_vbattTask_create(sl_cli_command_arg_t *arguments)
{
    (void)arguments;

    os_handle_t tk;
    ASSERT_FALSE(os_task_create(&tk, "vbatt_printTask", printVbattTask, OS_TASK_MODE_DELETE, 5, OS_MINIMUM_STACK_SIZE * 2, 0, NULL));
}

static void cli_topicTask_destroy(sl_cli_command_arg_t *arguments)
{
    (void)arguments;

    os_handle_t tk, topic;
    ASSERT_FALSE(os_task_create(&tk, "vbatt_printTask", printVbattTask, OS_TASK_MODE_DELETE, 5, OS_MINIMUM_STACK_SIZE * 2, 0, NULL));
    ASSERT_FALSE(os_topic_create(&topic, "vbatt"));

    ASSERT_FALSE(os_topic_unsubscribeTask(topic, tk));
    ASSERT_FALSE(os_task_delete(tk));
}

 /**********************************************
 * CLI MENU
 *********************************************/

static sl_cli_command_entry_t cli_topicTask_table[];
static const sl_cli_command_info_t cli_topicTask_group = SL_CLI_COMMAND_GROUP(cli_topicTask_table, "Topic print menu");

static sl_cli_command_entry_t cli_topicTask_group_entry[] = {
     {"topicPrint", &cli_topicTask_group, false},
     {NULL, NULL, false},
 };

 /**********************************************
 * CLI COMMANDS
 *********************************************/

static const sl_cli_command_info_t vbattPrint_create =
     SL_CLI_COMMAND(cli_vbattTask_create, "Create a task to print vbatt topic",
                    NULL,
                     {
                        SL_CLI_ARG_END,
                     });

static const sl_cli_command_info_t vbattPrint_destroy =
     SL_CLI_COMMAND(cli_topicTask_destroy, "Destroy task to print vbatt topic",
                    NULL,
                     {
                        SL_CLI_ARG_END,
                     });

static sl_cli_command_entry_t cli_topicTask_table[] = {
     {"c_vbatt",     &vbattPrint_create,  false},
     {"d_vbatt",     &vbattPrint_destroy,   false},
     {NULL, NULL, false},
 };

/**********************************************
 * PUBLIC VARIABLES
 *********************************************/

 sl_cli_command_group_t cli_topicPrint_menu = {
     {NULL},
     false,
     cli_topicTask_group_entry,
 };

