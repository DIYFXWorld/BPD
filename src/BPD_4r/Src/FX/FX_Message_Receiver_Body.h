#include "FX_Message_Receiver.h"
#include "FX_Message.h"
#include "FX_ID.h"
#include "Myutil.h"
#include <string.h>	// for memcpy
#include "FX_Message_Config.h"

bool										Lock_Message_Process = false;

static uint8_t					Message_Byte;
static uint8_t					Message_Buffer[ sizeof( FX_Message ) ];
static uint8_t					Message_Buffer_Counter;
static uint32_t					Message_Last_Time = 0;
static FX_Message				Message;

////////// Callback function

__weak bool Check_Message_ID( const FX_Message& ){ return false; }

#ifdef	USE_FX_CMD_CHANGE_PROGRAM
__weak void Change_Program	( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_STORE_PROGRAM
__weak void Store_Program		( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_RELEASE_CONTROLS
__weak void Release_Controls( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_CHANGE_BANK
__weak void Change_Bank			( const FX_Message& ){}
#endif

#ifdef	USE_FX_CMD_SET_TIME
__weak void Set_Time				( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_SEL_MIX_LEVEL
__weak void Set_Mix_Level		( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_SET_FEEDBACK
__weak void Set_Feedback		( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_SET_RATE
__weak void Set_Rate				( const FX_Message& ){}
#endif
#ifdef	USE_FX_CMD_SET_DEPTH
__weak void Set_Depth				( const FX_Message& ){}
#endif

//////////

void Start_Receiving_Message()
{
	HAL_UART_Receive_IT( &MESSAGE_RECEIVER_HANDLE, &Message_Byte, 1 );
}

void Dispatch_Message()
{
	if( Check_Message_ID( Message ) )
	{
		switch( Message.Command )
		{
#ifdef	USE_FX_CMD_CHANGE_PROGRAM
			case FX_CMD_Change_Program		: Change_Program( Message );		break;
#endif
#ifdef	USE_FX_CMD_STORE_PROGRAM
			case FX_CMD_Store_Program 		: Store_Program( Message );			break;
#endif
#ifdef	USE_FX_CMD_RELEASE_CONTROLS
			case FX_CMD_Release_Controls	:	Release_Controls( Message );	break;
#endif
#ifdef	USE_FX_CMD_CHANGE_BANK
			case FX_CMD_Change_Bank				: Change_Bank( Message );				break;
#endif
#ifdef	USE_FX_CMD_SET_TIME
			case FX_CMD_Set_Time					:	Set_Time( Message );					break;
#endif
#ifdef	USE_FX_CMD_SET_MIX_LEVEL
			case FX_CMD_Set_Mix_Level			:	Set_Mix_Level( Message );			break;
#endif
#ifdef	USE_FX_CMD_SET_FEEDBACK
			case FX_CMD_Set_Feedback			:	Set_Feedback( Message );			break;
#endif
#ifdef	USE_FX_CMD_SET_RATE
			case FX_CMD_Set_Rate			    :	Set_Rate( Message );					break;
#endif
#ifdef	USE_FX_CMD_SET_DEPTH
			case FX_CMD_Set_Depth		    	:	Set_Depth( Message );					break;
#endif
		}
	}

	Message.Reset();
}

void Post_Message_Process()
{
	if( Message.DID == FX_DID_None )	return;
	Dispatch_Message();
}

void Receiving_Message()
{
	auto	t = HAL_GetTick();

	if( Message_Buffer_Counter == 0 )
	{
		if( t - Message_Last_Time  < 100/*ms*/ )
		{
			Start_Receiving_Message();
			return;
		}
	}
	else if( Message_Buffer_Counter != 0 )
	{
		if( t - Message_Last_Time  > 20/*ms*/ )	Message_Buffer_Counter = 0;
	}

	Message_Last_Time = t;

	// Set FX_Message
	{
		Message_Buffer[ Message_Buffer_Counter++ ] = Message_Byte;

		if( Message_Buffer_Counter == sizeof( FX_Message ) )
		{
			memcpy( &Message, Message_Buffer, sizeof( FX_Message ) );

			if( !Lock_Message_Process )	Dispatch_Message();

			Message_Buffer_Counter = 0;
		}
	}

	Start_Receiving_Message();
}

void UART1_RxCpltCallback( UART_HandleTypeDef* );
void UART2_RxCpltCallback( UART_HandleTypeDef* );
void UART3_RxCpltCallback( UART_HandleTypeDef* );

extern "C" void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
	switch( ( uint32_t )huart->Instance )
	{
		case USART1_BASE: UART1_RxCpltCallback( huart ); break;
		case USART2_BASE: UART2_RxCpltCallback( huart ); break;
		case USART3_BASE: UART3_RxCpltCallback( huart ); break;
	}
}
