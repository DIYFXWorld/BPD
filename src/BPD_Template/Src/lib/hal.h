#ifndef	hal_h
#define	hal_h

#if	defined(STM32F103xB) || defined(STM32F103xE)
	#include "stm32f1xx_hal.h"
#endif

#if	defined(STM32F303xC)
	#include "stm32f3xx_hal.h"
#endif

#if	defined(STM32L152xE)
	#include "stm32l1xx_hal.h"
#endif

#if	defined(STM32F401xC) || defined(STM32F407xx) || defined(STM32F411xE)
	#include "stm32F4xx_hal.h"
#endif

#endif
