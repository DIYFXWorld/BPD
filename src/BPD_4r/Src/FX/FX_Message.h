#ifndef	FX_Message_h
#define	FX_Message_h

#include	"FX_ID.h"
#include	<stdint.h>

enum FX_Device_ID
{
	FX_DID_None		=  0,
	FX_DID_0 			=  5,
	FX_DID_1			= 10,
	FX_DID_2			= 15,
	FX_DID_3			= 20,
	FX_DID_4			= 25,
	FX_DID_5			= 30,
	FX_DID_6			= 35,
	FX_DID_7			= 40,
	FX_DID_8			= 45,

	FX_DID_BPD		= 50,
	FX_DID_BPCFP	= 51,
	FX_DID_BPPGC5	= 52,

	FX_DID_Common = 255,
};

enum FX_Command
{
	FX_CMD_None 						= 0,
	FX_CMD_Change_Program,
	FX_CMD_Store_Program,
	FX_CMD_Copy_Program,
	FX_CMD_Erase_Program,
	FX_CMD_Release_Controls,
	FX_CMD_Change_Bank,

	FX_CMD_Set_Time					= 30,
	FX_CMD_Set_Mix_Level,
	FX_CMD_Set_Feedback,
	FX_CMD_Set_Volume,
	FX_CMD_Set_Rate,
	FX_CMD_Set_Depth,

	FX_CMD_Set_HPF_Freq			= 60,
	FX_CMD_Set_LPF_Freq,
	FX_CMD_Set_BPF_Freq,
	FX_CMD_Set_HPF_Q,
	FX_CMD_Set_LPF_Q,
	FX_CMD_Set_BPF_Q,
};

struct FX_Message
{
	uint8_t		DID;
	uint8_t		FID;
	uint8_t		Command;
	uint8_t		Param_Byte;
	int16_t		Param_Word;

	FX_Message
	(
		FX_Device_ID	did = FX_DID_None,
		FX_ID					fid	= FX_ID_None,
		FX_Command		cmd	= FX_CMD_None,
		uint8_t				pb 	= 0,
		int16_t 			pw	= 0
	):
		DID( did ), FID( fid ), Command( cmd ),	Param_Byte( pb ), Param_Word( pw )
	{
	}

	void Reset()
	{
		*this = FX_Message();
	}
};

#endif
