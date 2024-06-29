#ifndef __COMMON_H__
#define __COMMON_H__

#include "stdio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "pin_config.h"

/**********************************************
 * DEFINES
 *********************************************/

#ifndef PRINT_ENABLE
#define PRINT_ENABLE 1
#endif

#if __INTELLISENSE__
#define __FILE_NAME__  __FILE__
#endif

/* Defines a definition as weak
 ---------------------------------------------------*/
#ifndef __weak
#define __weak __attribute__((weak))
#endif

/* Defines a naked function (pure assembly)
 ---------------------------------------------------*/
#ifndef __naked
#define __naked __attribute__((naked))
#endif

/* Defines an used function to avoid warnings and optimization (functions called by asm are not detected)
 ---------------------------------------------------*/
#ifndef __used
#define __used __attribute__((used))
#endif


/**********************************************
 * MACROS
 *********************************************/

#if defined(PRINT_ENABLE) && PRINT_ENABLE == 1
    //#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #define PRINTF(S, ...) 		printf(S, ## __VA_ARGS__)
    #define PRINT(S, ...) 		PRINTF("[%s:%03d]: " S, __FILE_NAME__, __LINE__, ## __VA_ARGS__)
    #define PRINTLN(S, ...) 	PRINT (S "\n", ## __VA_ARGS__)

    #define PRINT_W(S, ...) 	PRINTF("\033[33m" "[%s:%03d]: " S "\033[37m", __FILE_NAME__, __LINE__, ## __VA_ARGS__)
    #define PRINTLN_W(S, ...) 	PRINT_W (S "\n", ## __VA_ARGS__)

    #define PRINT_E(S, ...) 	PRINTF("\033[31m" "[%s:%03d]: " S "\033[37m", __FILE_NAME__, __LINE__, ## __VA_ARGS__)
    #define PRINTLN_E(S, ...) 	PRINT_E (S "\n", ## __VA_ARGS__)
#else
    #define PRINTF(S, ...)
    #define PRINT(S, ...)
    #define PRINTLN(S, ...)

    #define PRINT_W(S, ...)
    #define PRINTLN_W(S, ...)

    #define PRINT_E(S, ...)
    #define PRINTLN_E(S, ...)
#endif

#ifndef ASSERT
    #define ASSERT(x)                    do { if(!(x)) { PRINTLN_E("Assert failed!"); } } while(0)
    #define ASSERT_EQ(val, expected)     do { if( (val) != (expected) ) { PRINTLN_E("Assert failed! Expected %d, got %d", expected, val); } } while(0)
#endif

/**********************************************
 * PUBLIC FUNCTIONS
 *********************************************/

void cli_init(void);

#endif //__COMMON_H__