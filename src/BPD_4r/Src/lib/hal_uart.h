#ifndef	hal_uart_h
#define	hal_uart_h

#include "hal.h"

#ifdef	STM32F030x6
	#include "stm32f0xx_hal_uart.h"
#endif

#if	defined(STM32F103xB) || defined(STM32F103xE)
	#include "stm32f1xx_hal_uart.h"
#endif

#ifdef	STM32F303xC
	#include "stm32f3xx_hal_uart.h"
#endif

#ifdef	STM32L152xE
	#include "stm32l1xx_hal_uart.h"
#endif

#ifdef	STM32f407xx
	#include "stm32f4xx_hal_uart.h"
#endif

#endif
