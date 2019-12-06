#ifndef	Audio_h
#define	Audio_h

#include	"Board.h"	// for User Bytes

void Audio_Input_Callback( int );
void Audio_Invalid_Callback( int );

void Audio_Input_Callback( int, int );
void Audio_Invalid_Callback( int, int );

struct Audio
{
	static int8_t		Lock_Counter;

	static void Input_Start();
	static void Output_Start();

	static void Start()
	{
		Output_Start();
		Input_Start();
	}

	static void Set_Output( int );
	static void Set_Output( int, int );

	static void Active() 	{ --Lock_Counter; }
	static void Inactive()	{ ++Lock_Counter; }
};

#endif
