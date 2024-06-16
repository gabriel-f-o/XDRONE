/*
 * OS_cortexM4.h
 *
 *  Created on: Feb 13, 2022
 *      Author: Gabriel
 */

#ifndef INC_OS_OS_CORTEXM33_H_
#define INC_OS_OS_CORTEXM33_H_

#include "OS_Common.h"

/**********************************************
 * DEFINES
 * ********************************************/

/* System control defines
 ---------------------------------------------------*/
#define OS_SYSTEM_CTRL_BASE					(0xE000E010)
#define OS_SYSTEM_CTRL						((SystemControl_TypeDef*) OS_SYSTEM_CTRL_BASE)

#define OS_SYSTEM_CTRL_ICSR_PENDSVSET_Pos 	(28U)
#define OS_SYSTEM_CTRL_ICSR_PENDSVSET_Msk 	(0x1UL << OS_SYSTEM_CTRL_ICSR_PENDSVSET_Pos)
#define OS_SYSTEM_CTRL_ICSR_PENDSVSET  		(OS_SYSTEM_CTRL_ICSR_PENDSVSET_Msk)

#define OS_SYSTEM_CTRL_CPACR_CP10_Pos		(20U)
#define OS_SYSTEM_CTRL_CPACR_CP10_Msk		(0x3UL << OS_SYSTEM_CTRL_CPACR_CP10_Pos)
#define OS_SYSTEM_CTRL_CPACR_CP10			(OS_SYSTEM_CTRL_CPACR_CP10_Msk)

#define OS_SYSTEM_CTRL_CPACR_CP11_Pos		(22U)
#define OS_SYSTEM_CTRL_CPACR_CP11_Msk		(0x3UL << OS_SYSTEM_CTRL_CPACR_CP11_Pos)
#define OS_SYSTEM_CTRL_CPACR_CP11			(OS_SYSTEM_CTRL_CPACR_CP11_Msk)

#define OS_SYSTEM_CTRL_SYSTCSR_ENABLE_Pos	(0U)
#define OS_SYSTEM_CTRL_SYSTCSR_ENABLE_Msk	(0x1UL << OS_SYSTEM_CTRL_SYSTCSR_ENABLE_Pos)
#define OS_SYSTEM_CTRL_SYSTCSR_ENABLE		(OS_SYSTEM_CTRL_SYSTCSR_ENABLE_Msk)

#define OS_SYSTICK_ENABLE()					OS_SET_BITS(OS_SYSTEM_CTRL->SYSTCSR,   OS_SYSTEM_CTRL_SYSTCSR_ENABLE)
#define OS_SYSTICK_DISABLE()				OS_CLEAR_BITS(OS_SYSTEM_CTRL->SYSTCSR, OS_SYSTEM_CTRL_SYSTCSR_ENABLE)

#define OS_SYSTICK_SET_PRIO(x)				do { OS_SYSTEM_CTRL->SHPR3   |= ( ( (x) & 0x0000FF) << 24); }while(0);
#define OS_SYSTICK_SET_RELOAD(x)			do { OS_SYSTEM_CTRL->SYSTRVR = ( ( (x) & 0xFFFFFF) <<  0); }while(0);

#define OS_SET_PENDSV()						do { OS_SET_BITS(OS_SYSTEM_CTRL->ICSR, OS_SYSTEM_CTRL_ICSR_PENDSVSET); } while(0)
#define OS_PENDSV_SET_PRIO(x)				do { OS_SYSTEM_CTRL->SHPR3   |= ( ( (x) & 0x0000FF) << 16); }while(0);

/* FPU defines
 ---------------------------------------------------*/
#define OS_FPU_BASE							(0xE000EF34)
#define OS_FPU								((FPU_TypeDef*) OS_FPU_BASE)

#define OS_FPU_FPCCR_ASPEN_Pos				(30U)
#define OS_FPU_FPCCR_ASPEN_Msk				(0x1UL << OS_FPU_FPCCR_ASPEN_Pos)
#define OS_FPU_FPCCR_ASPEN					(OS_FPU_FPCCR_ASPEN_Msk)

#define OS_FPU_FPCCR_LSPEN_Pos				(31U)
#define OS_FPU_FPCCR_LSPEN_Msk				(0x1UL << OS_FPU_FPCCR_LSPEN_Pos)
#define OS_FPU_FPCCR_LSPEN					(OS_FPU_FPCCR_LSPEN_Msk)

#define OS_FPU_ENABLE()						OS_SET_BITS(OS_SYSTEM_CTRL->CPACR,   (OS_SYSTEM_CTRL_CPACR_CP10 | OS_SYSTEM_CTRL_CPACR_CP11))
#define OS_FPU_DISABLE()					OS_CLEAR_BITS(OS_SYSTEM_CTRL->CPACR, (OS_SYSTEM_CTRL_CPACR_CP10 | OS_SYSTEM_CTRL_CPACR_CP11))

#define OS_FPU_LAZY_ENABLE()				OS_SET_BITS(OS_FPU->FPCCR,   OS_FPU_FPCCR_LSPEN)
#define OS_FPU_LAZY_DISABLE()				OS_CLEAR_BITS(OS_FPU->FPCCR, OS_FPU_FPCCR_LSPEN)

#define OS_FPU_STATUS_ENABLE()				OS_SET_BITS(OS_FPU->FPCCR,   OS_FPU_FPCCR_ASPEN)
#define OS_FPU_STATUS_DISABLE()				OS_CLEAR_BITS(OS_FPU->FPCCR, OS_FPU_FPCCR_ASPEN)

/**********************************************
 * PUBLIC TYPES
 * ********************************************/

typedef struct{
	__OS_IOM uint32_t SYSTCSR; 	//0xE000E010
	__OS_IOM uint32_t SYSTRVR; 	//0xE000E014
	uint32_t reserved0[827];
	__OS_IOM uint32_t ICSR;	 	//0xE000ED04
	uint32_t reserved1[6];
	__OS_IOM uint32_t SHPR3;	//0xE000ED20
	uint32_t reserved2[25];
	__OS_IOM uint32_t CPACR;	//0xE000ED88
}SystemControl_TypeDef;

typedef struct{
	__OS_IOM uint32_t FPCCR;		//FP Context Control Register
	__OS_IOM uint32_t FPCAR;		//FP Context Address Register
	__OS_IOM uint32_t FPDSCR;		//FP Default Status Control Register
	__OS_IM  uint32_t MVFR0;		//Media and VFP Feature Register 0, MVFR0
	__OS_IM  uint32_t MVFR1;		//Media and VFP Feature Register 1, MVFR1
}FPU_TypeDef;


#endif /* INC_OS_OS_CORTEXM33_H_ */
