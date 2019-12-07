#ifndef FX_PROCESS_H_
#define FX_PROCESS_H_

#include "FX_Interface.h"
#include "Fade_In.h"
#include "FX_Params.h"

extern	FX_Interface		*FX;	// current FX
extern	Fade_In					Audio_Fade_In;

void Select_FX( const FX_Params& );

#endif

/* FX_PROCESS_H_ */
