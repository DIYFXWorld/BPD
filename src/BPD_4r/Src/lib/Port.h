#ifndef	Port_h
#define	Port_h

#include	"hal.h"
#include	"hal_gpio.h"

struct Port
{
	GPIO_TypeDef*		GPIO;
	uint16_t				Pin;
	bool						Logic;

	Port():
		GPIO( 0 ), Pin( 0 ), Logic( 0 )
	{
	}

	Port( GPIO_TypeDef* gpio, uint16_t pin, bool logic = true ):
		GPIO( gpio ), Pin( pin ), Logic( logic )
	{
	}

	bool Read()
	{
		GPIO_PinState	v = HAL_GPIO_ReadPin( GPIO, Pin );

		if( Logic )	return ( v == GPIO_PIN_SET ) ? true  : false;
		else				return ( v == GPIO_PIN_SET ) ? false : true;
	}

	void Write( bool v ) { v ? ON() : OFF(); }

	void Toggle() { HAL_GPIO_TogglePin( GPIO, Pin ); }

	void ON() 	{ HAL_GPIO_WritePin( GPIO, Pin, ( Logic ) ? GPIO_PIN_SET   : GPIO_PIN_RESET ); }
	void OFF()	{ HAL_GPIO_WritePin( GPIO, Pin, ( Logic ) ? GPIO_PIN_RESET : GPIO_PIN_SET   ); }
	
	void High() { HAL_GPIO_WritePin( GPIO, Pin, GPIO_PIN_SET ); }
	void Low()	{ HAL_GPIO_WritePin( GPIO, Pin, GPIO_PIN_RESET ); }
};

#define	_PA0_			GPIOA,GPIO_PIN_0
#define	_PA1_			GPIOA,GPIO_PIN_1
#define	_PA2_			GPIOA,GPIO_PIN_2
#define	_PA3_			GPIOA,GPIO_PIN_3
#define	_PA4_			GPIOA,GPIO_PIN_4
#define	_PA5_			GPIOA,GPIO_PIN_5
#define	_PA6_			GPIOA,GPIO_PIN_6
#define	_PA7_			GPIOA,GPIO_PIN_7
#define	_PA8_			GPIOA,GPIO_PIN_8
#define	_PA9_			GPIOA,GPIO_PIN_9
#define	_PA10_		GPIOA,GPIO_PIN_10
#define	_PA11_		GPIOA,GPIO_PIN_11
#define	_PA12_		GPIOA,GPIO_PIN_12
#define	_PA13_		GPIOA,GPIO_PIN_13
#define	_PA14_		GPIOA,GPIO_PIN_14
#define	_PA15_		GPIOA,GPIO_PIN_15

#define	_PB0_			GPIOB,GPIO_PIN_0
#define	_PB1_			GPIOB,GPIO_PIN_1
#define	_PB2_			GPIOB,GPIO_PIN_2
#define	_PB3_			GPIOB,GPIO_PIN_3
#define	_PB4_			GPIOB,GPIO_PIN_4
#define	_PB5_			GPIOB,GPIO_PIN_5
#define	_PB6_			GPIOB,GPIO_PIN_6
#define	_PB7_			GPIOB,GPIO_PIN_7
#define	_PB8_			GPIOB,GPIO_PIN_8
#define	_PB9_			GPIOB,GPIO_PIN_9
#define	_PB10_		GPIOB,GPIO_PIN_10
#define	_PB11_		GPIOB,GPIO_PIN_11
#define	_PB12_		GPIOB,GPIO_PIN_12
#define	_PB13_		GPIOB,GPIO_PIN_13
#define	_PB14_		GPIOB,GPIO_PIN_14
#define	_PB15_		GPIOB,GPIO_PIN_15

#define	_PC0_			GPIOC,GPIO_PIN_0
#define	_PC1_			GPIOC,GPIO_PIN_1
#define	_PC2_			GPIOC,GPIO_PIN_2
#define	_PC3_			GPIOC,GPIO_PIN_3
#define	_PC4_			GPIOC,GPIO_PIN_4
#define	_PC5_			GPIOC,GPIO_PIN_5
#define	_PC6_			GPIOC,GPIO_PIN_6
#define	_PC7_			GPIOC,GPIO_PIN_7
#define	_PC8_			GPIOC,GPIO_PIN_8
#define	_PC9_			GPIOC,GPIO_PIN_9
#define	_PC10_		GPIOC,GPIO_PIN_10
#define	_PC11_		GPIOC,GPIO_PIN_11
#define	_PC12_		GPIOC,GPIO_PIN_12
#define	_PC13_		GPIOC,GPIO_PIN_13
#define	_PC14_		GPIOC,GPIO_PIN_14
#define	_PC15_		GPIOC,GPIO_PIN_15

#define	_PD0_			GPIOD,GPIO_PIN_0
#define	_PD1_			GPIOD,GPIO_PIN_1
#define	_PD2_			GPIOD,GPIO_PIN_2
#define	_PD3_			GPIOD,GPIO_PIN_3
#define	_PD4_			GPIOD,GPIO_PIN_4
#define	_PD5_			GPIOD,GPIO_PIN_5
#define	_PD6_			GPIOD,GPIO_PIN_6
#define	_PD7_			GPIOD,GPIO_PIN_7
#define	_PD8_			GPIOD,GPIO_PIN_8
#define	_PD9_			GPIOD,GPIO_PIN_9
#define	_PD10_		GPIOD,GPIO_PIN_10
#define	_PD11_		GPIOD,GPIO_PIN_11
#define	_PD12_		GPIOD,GPIO_PIN_12
#define	_PD13_		GPIOD,GPIO_PIN_13
#define	_PD14_		GPIOD,GPIO_PIN_14
#define	_PD15_		GPIOD,GPIO_PIN_15

#define	_PE0_			GPIOE,GPIO_PIN_0
#define	_PE1_			GPIOE,GPIO_PIN_1
#define	_PE2_			GPIOE,GPIO_PIN_2
#define	_PE3_			GPIOE,GPIO_PIN_3
#define	_PE4_			GPIOE,GPIO_PIN_4
#define	_PE5_			GPIOE,GPIO_PIN_5
#define	_PE6_			GPIOE,GPIO_PIN_6
#define	_PE7_			GPIOE,GPIO_PIN_7
#define	_PE8_			GPIOE,GPIO_PIN_8
#define	_PE9_			GPIOE,GPIO_PIN_9
#define	_PE10_		GPIOE,GPIO_PIN_10
#define	_PE11_		GPIOE,GPIO_PIN_11
#define	_PE12_		GPIOE,GPIO_PIN_12
#define	_PE13_		GPIOE,GPIO_PIN_13
#define	_PE14_		GPIOE,GPIO_PIN_14
#define	_PE15_		GPIOE,GPIO_PIN_15

#define	_PF0_			GPIOF,GPIO_PIN_0
#define	_PF1_			GPIOF,GPIO_PIN_1
#define	_PF2_			GPIOF,GPIO_PIN_2
#define	_PF3_			GPIOF,GPIO_PIN_3
#define	_PF4_			GPIOF,GPIO_PIN_4
#define	_PF5_			GPIOF,GPIO_PIN_5
#define	_PF6_			GPIOF,GPIO_PIN_6
#define	_PF7_			GPIOF,GPIO_PIN_7
#define	_PF8_			GPIOF,GPIO_PIN_8
#define	_PF9_			GPIOF,GPIO_PIN_9
#define	_PF10_		GPIOF,GPIO_PIN_10
#define	_PF11_		GPIOF,GPIO_PIN_11
#define	_PF12_		GPIOF,GPIO_PIN_12
#define	_PF13_		GPIOF,GPIO_PIN_13
#define	_PF14_		GPIOF,GPIO_PIN_14
#define	_PF15_		GPIOF,GPIO_PIN_15

#define	_PG0_			GPIOG,GPIO_PIN_0
#define	_PG1_			GPIOG,GPIO_PIN_1
#define	_PG2_			GPIOG,GPIO_PIN_2
#define	_PG3_			GPIOG,GPIO_PIN_3
#define	_PG4_			GPIOG,GPIO_PIN_4
#define	_PG5_			GPIOG,GPIO_PIN_5
#define	_PG6_			GPIOG,GPIO_PIN_6
#define	_PG7_			GPIOG,GPIO_PIN_7
#define	_PG8_			GPIOG,GPIO_PIN_8
#define	_PG9_			GPIOG,GPIO_PIN_9
#define	_PG10_		GPIOG,GPIO_PIN_10
#define	_PG11_		GPIOG,GPIO_PIN_11
#define	_PG12_		GPIOG,GPIO_PIN_12
#define	_PG13_		GPIOG,GPIO_PIN_13
#define	_PG14_		GPIOG,GPIO_PIN_14
#define	_PG15_		GPIOG,GPIO_PIN_15

#endif
