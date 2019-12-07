#ifndef	FX_ID_h
#define	FX_ID_h

#include	<stdint.h>

enum FX_ID
{
	FX_ID_None = 0,
	FX_ID_Delay,
	FX_ID_Reverse_Delay,
	FX_ID_Chorus,
	FX_ID_Flanger,
	FX_ID_Phaser,
	FX_ID_Analog_Delay,
	FX_ID_Modulation_Delay,
	FX_ID_Dual_Chorus, FX_ID_Tremolo,
	FX_ID_Ring_Modulation,
	FX_ID_Reverb,
	FX_ID_Two_Tap_Delay,
	FX_ID_Delay_ADPCM,
	FX_ID_Delay_PCMU,
	FX_ID_Reverse_Delay_PCMU,
	FX_ID_Delay_0,
	FX_ID_Pitch_Shift,
};

#endif
