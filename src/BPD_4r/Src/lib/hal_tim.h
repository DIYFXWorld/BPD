#ifndef	hal_tim_h
#define	hal_tim_h

#include "hal.h"

#if	defined(STM32F103xB) || defined(STM32F103xE)
	#include "stm32f1xx_hal_tim.h"
#endif

#ifdef	STM32F303xC
	#include "stm32f3xx_hal_tim.h"
#endif

#ifdef	STM32L152xE
	#include "stm32l1xx_hal_tim.h"
#endif

#ifdef	STM32F401xC
	#include "stm32F4xx_hal_tim.h"
#endif

#ifdef	STM32F407xx
	#include "stm32F4xx_hal_tim.h"
#endif

#ifdef	STM32F411xE
	#include "stm32F4xx_hal_tim.h"
#endif

#ifdef	STM32F303xC
	#include "stm32F3xx_hal_tim.h"
#endif

#endif
