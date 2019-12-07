#ifndef	FX_Message_Receiver_h
#define	FX_Message_Receiver_h

#include	"FX_Message.h"

extern bool	Lock_Message_Process;

bool Check_Message_ID	( const FX_Message& );
void Change_Program		( const FX_Message& );
void Store_Program		( const FX_Message& );
void Release_Controls	( const FX_Message& );
void Change_Bank			( const FX_Message& );

void Set_Time					( const FX_Message& );
void Set_Mix_Level		( const FX_Message& );
void Set_Feedback			( const FX_Message& );
void Set_Rate					( const FX_Message& );
void Set_Depth				( const FX_Message& );

void Start_Receiving_Message();

void Post_Message_Process();

void Receiving_Message();


#endif
