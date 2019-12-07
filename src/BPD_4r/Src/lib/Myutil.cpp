#include	"Myutil.h"

////////// 16bit

const	uint16_t	UINT16_HALF		=  UINT16_MAX/2;

////////// 14bit

const	uint16_t	UINT14_MAX	=  16383;
const	uint16_t	UINT14_HALF	=  16383/2;
const	 int16_t	INT14_MAX		=  16383/2;
const	 int16_t  INT14_MIN		= -(16383/2)-1;

////////// 12bit

const	uint16_t	UINT12_MAX	=  4095;
const	uint16_t	UINT12_HALF	=  2047;
const	 int16_t	INT12_MAX		=  2047;
const	 int16_t  INT12_MIN		= -2048;


unsigned long Random()
{
	static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
	unsigned long t=(x^(x<<11));
	x=y;y=z;z=w;
	return( w=(w^(w>>19))^(t^(t>>8)) );
}
