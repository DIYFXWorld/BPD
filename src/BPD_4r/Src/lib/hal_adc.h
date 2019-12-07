#ifndef	hal_adc_h
#define	hal_adc_h

#include "hal.h"

#if	defined(STM32F103xB) || defined(STM32F103xE)
	#include "stm32f1xx_hal_adc.h"
#endif

#ifdef	STM32F303xC
	#include "stm32f3xx_hal_adc.h"
#endif

#ifdef	STM32L152xE
	#include "stm32l1xx_hal_adc.h"
#endif

#if	defined(STM32F407xx) | defined(STM32F411xE)
	#include "stm32f4xx_hal_adc.h"
#endif

#endif
