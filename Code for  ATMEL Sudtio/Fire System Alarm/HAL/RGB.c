#define F_CPU	8000000
#include <util/delay.h>
#include "MemMap.h"
#include "StdTypes.h"
#include "RGB.h"
#include "Timers.h"

u8 colours_arr[][3]={
	{0,0,0},		//OFF
	{255,0,0},		//RED
	{0,255,0},		//GREEN
	{0,0,255},		//BLUE
	{255,255,255},	//WHITE
	{255,255,0},	//YELLOW
	{255,127,0},	//ORANGE
	{75,0,130},		//MOVE
};

void RGB_Init(void)
{
	TIMER0_Init( TIMER0_FASTPWM_MODE, TIMER0_SCALER_8);
	TIMER0_OC0Mode( OC0_INVERTING);
	Timer1_Init( TIMER1_FASTPWM_ICR_TOP_MODE, TIMER1_SCALER_8);
	Timer1_OCRA1Mode(OCRA_INVERTING);
	Timer1_OCRB1Mode(OCRB_INVERTING);
	ICR1=255;
}

void RGB_Set(Colours_type colour)
{
	OCR0=255-(colours_arr[colour][0]);
	OCR1A=255-(colours_arr[colour][1]);
	OCR1B=255-(colours_arr[colour][2]);
};

void RGB_Flow(Colours_type colour1, Colours_type colour2)
{
	u8 c;

	OCR0=255-colours_arr[colour1][0];
	OCR1A=255-colours_arr[colour1][1];
	OCR1B=255-colours_arr[colour1][2];

	for (c=0; c<255;c++)
	{
		if((colours_arr[colour1][0])>(colours_arr[colour2][0]))
		{
			OCR0=OCR0+1;
		}
		else if((colours_arr[colour1][0])<(colours_arr[colour2][0]))
		{
			OCR0=OCR0-1;
		}
		
		if((colours_arr[colour1][1])>(colours_arr[colour2][1]))
		{
			OCR1A=OCR1A+1;
		}
		else if((colours_arr[colour1][1])<(colours_arr[colour2][1]))
		{
			OCR1A=OCR1A-1;
		}
		
		if((colours_arr[colour1][2])>(colours_arr[colour2][2]))
		{
			OCR1B=OCR1B+1;
		}
		else if((colours_arr[colour1][2])<(colours_arr[colour2][2]))
		{
			OCR1B=OCR1B-1;
		}
		_delay_ms(100);
	}
}
