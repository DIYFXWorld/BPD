#ifndef	Board_h
#define	Board_h

#include	"hal.h"
#include	"hal_gpio.h"

#if	defined(NUCLEO) && defined(STM32F103xB)
	#define	USER_LED_ON()				HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET )		// positive
	#define	USER_LED_OFF()			HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_RESET )	// positive
	#define	USER_LED_TOGGLE()		HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 )
#endif

#if	defined(STM32F103xB)
	#define	USER_LED_ON()				HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_RESET )	// negative
	#define	USER_LED_OFF()			HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_SET )		// negative
	#define	USER_LED_TOGGLE()		HAL_GPIO_TogglePin( GPIOC, GPIO_PIN_13 )
	#define	OB_ADDRESS					0x1FFFF800
	#define	Get_UID()						( *( uint8_t* )( OB_ADDRESS+4 ) )
	inline unsigned char Get_User_Byte_0() { return *( ( unsigned char* )( OB_ADDRESS+4 ) ); }
	inline unsigned char Get_User_Byte_1() { return *( ( unsigned char* )( OB_ADDRESS+6 ) ); }
#endif

#if	defined(STM32F407xx)
	#define	USER_LED_ON()				HAL_GPIO_WritePin( GPIOA, GPIO_PIN_1, GPIO_PIN_SET )		// positive
	#define	USER_LED_OFF()			HAL_GPIO_WritePin( GPIOA, GPIO_PIN_1, GPIO_PIN_RESET )	// positive
	#define	USER_LED_TOGGLE()		HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_1 )
//#define	OB_ADDRESS					0x1FFFF800
//#define	Get_UID()						( *( uint8_t* )( OB_ADDRESS+4 ) )
//inline unsigned char Get_User_Byte_0() { return *( ( unsigned char* )( OB_ADDRESS+4 ) ); }
//inline unsigned char Get_User_Byte_1() { return *( ( unsigned char* )( OB_ADDRESS+6 ) ); }
#endif

#if	defined(STM32F411xE)
	#define	USER_LED_ON()			HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_RESET )	// negative
	#define	USER_LED_OFF()			HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_SET )	// negative
	#define	USER_LED_TOGGLE()		HAL_GPIO_TogglePin( GPIOC, GPIO_PIN_13 )
//#define	OB_ADDRESS					0x1FFFF800
//#define	Get_UID()						( *( uint8_t* )( OB_ADDRESS+4 ) )
//inline unsigned char Get_User_Byte_0() { return *( ( unsigned char* )( OB_ADDRESS+4 ) ); }
//inline unsigned char Get_User_Byte_1() { return *( ( unsigned char* )( OB_ADDRESS+6 ) ); }
#endif

#if	defined(STM32F401xC)
	#define	USER_LED_ON()				HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_RESET )	// negative
	#define	USER_LED_OFF()			HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_SET )	// negative
	#define	USER_LED_TOGGLE()		HAL_GPIO_TogglePin( GPIOC, GPIO_PIN_13 )
//#define	OB_ADDRESS					0x1FFFC000
//#define	Get_UID()						( *( uint8_t* )( OB_ADDRESS+4 ) )
//inline unsigned char Get_User_Byte_0() { return *( ( unsigned char* )( OB_ADDRESS+4 ) ); }
//inline unsigned char Get_User_Byte_1() { return *( ( unsigned char* )( OB_ADDRESS+6 ) ); }
#endif

#if	defined(STM32F303xC)
	#define	USER_LED_ON()				HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_RESET )	// negative
	#define	USER_LED_OFF()			HAL_GPIO_WritePin( GPIOC, GPIO_PIN_13, GPIO_PIN_SET )	// negative
	#define	USER_LED_TOGGLE()		HAL_GPIO_TogglePin( GPIOC, GPIO_PIN_13 )
//#define	OB_ADDRESS					0x1FFFC000
//#define	Get_UID()						( *( uint8_t* )( OB_ADDRESS+4 ) )
//inline unsigned char Get_User_Byte_0() { return *( ( unsigned char* )( OB_ADDRESS+4 ) ); }
//inline unsigned char Get_User_Byte_1() { return *( ( unsigned char* )( OB_ADDRESS+6 ) ); }
#endif

#endif
