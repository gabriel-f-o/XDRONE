#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_cli_instances.h"
#include "sl_cli.h"
#include "sl_string.h"
#include <string.h>
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#endif // defined(SL_CATALOG_KERNEL_PRESENT)

#include "sl_cli_config_xdrone.h"


#include "sl_iostream_handles.h"

//****************************************************************************
// Macros

#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGUMENTS(...) ELEVENTH_ARGUMENT(dummy, ## __VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define ISEMPTY(...) (COUNT_ARGUMENTS(__VA_ARGS__) == 0)

//****************************************************************************
// Variables

extern const sl_cli_command_entry_t sl_cli_default_command_table[];

#if !ISEMPTY(SL_CLI_XDRONE_COMMAND_GROUP)
extern sl_cli_command_group_t *SL_CLI_XDRONE_COMMAND_GROUP;
#endif


// Instance variables for xdrone
#if defined(SL_CATALOG_KERNEL_PRESENT)
__ALIGNED(8) static uint8_t xdrone_task_stack[(SL_CLI_XDRONE_TASK_STACK_SIZE * sizeof(void *)) & 0xFFFFFFF8u];
__ALIGNED(4) static uint8_t xdrone_thread_cb[osThreadCbSize];
static osThreadId_t xdrone_thread_id;
#endif
static sl_cli_t sl_cli_xdrone;
sl_cli_handle_t sl_cli_xdrone_handle = &sl_cli_xdrone;
sl_cli_command_group_t sl_cli_xdrone_command_group =
{
  { NULL },
  false,
  sl_cli_default_command_table
};



const sl_cli_handle_t sl_cli_handles[] = {

  &sl_cli_xdrone,

};

const uint32_t sl_cli_handles_count = sizeof(sl_cli_handles) / sizeof(sl_cli_handle_t);

//****************************************************************************
// Global functions

void sl_cli_instances_init(void)
{
  sl_cli_instance_parameters_t instance_parameters;

  // ==== Initialize xdrone ====
  sl_cli_default_handle = sl_cli_xdrone_handle;
  sl_cli_default_command_group  = &sl_cli_xdrone_command_group;
  instance_parameters.task_name = "CLI instance xdrone";
  instance_parameters.iostream_handle = SL_CLI_XDRONE_IOSTREAM_HANDLE;
#if ISEMPTY(SL_CLI_XDRONE_COMMAND_GROUP)
  sl_cli_default_command_group  = NULL;
#else
  sl_cli_default_command_group  = SL_CLI_XDRONE_COMMAND_GROUP;
#endif
  instance_parameters.default_command_group = sl_cli_default_command_group;
#if defined(SL_CATALOG_KERNEL_PRESENT)
  instance_parameters.thread_id = &xdrone_thread_id;
  instance_parameters.thread_cb = xdrone_thread_cb;
  instance_parameters.stack = xdrone_task_stack;
  instance_parameters.stack_size = (SL_CLI_XDRONE_TASK_STACK_SIZE * sizeof(void *)) & 0xFFFFFFF8u;
  EFM_ASSERT(SL_CLI_XDRONE_TASK_PRIORITY < osPriorityISR);
  instance_parameters.prio = (osPriority_t)SL_CLI_XDRONE_TASK_PRIORITY;
  instance_parameters.start_delay_ms = SL_CLI_XDRONE_TASK_START_DELAY_MS;
  instance_parameters.loop_delay_ms = SL_CLI_XDRONE_TASK_LOOP_DELAY_MS;
#endif
  sl_cli_instance_init(sl_cli_xdrone_handle, &instance_parameters);
  
}

#if !defined(SL_CATALOG_KERNEL_PRESENT)
bool sl_cli_instances_is_ok_to_sleep(void)
{
  
  if (sl_cli_is_ok_to_sleep(sl_cli_xdrone_handle) == false) {
    return false;
  }
  

  return true;
}

void sl_cli_instances_tick(void)
{
sl_iostream_t *previous = sl_iostream_get_default();

  // Handle xdrone
  sl_iostream_set_default(sl_cli_xdrone_handle->iostream_handle);
  sl_cli_tick_instance(sl_cli_xdrone_handle);
  
  sl_iostream_set_default(previous);
}
#endif
