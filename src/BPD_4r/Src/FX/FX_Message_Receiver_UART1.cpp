#include	"hal.h"
#include	"hal_uart.h"

#define	MESSAGE_RECEIVER_HANDLE		huart1
extern	UART_HandleTypeDef 				MESSAGE_RECEIVER_HANDLE;

#include	"FX_Message_Receiver_Body.h"

__weak void UART1_RxCpltCallback( UART_HandleTypeDef *huart )
{
	Receiving_Message();
}

__weak void UART2_RxCpltCallback( UART_HandleTypeDef *huart )
{
}

__weak void UART3_RxCpltCallback( UART_HandleTypeDef *huart )
{
}
