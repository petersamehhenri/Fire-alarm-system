#include "StdTypes.h"
#include "Servo.h"
#include "Timers.h"
#include "Timers_Services.h"


void SERVO_Init(void)
{
	Timer1_Init(TIMER1_FASTPWM_OCRA_TOP_MODE, TIMER1_SCALER_8);
	Timer1_OCRB1Mode(OCRB_NON_INVERTING);
	OCR1A=19999;
}


void SERVO_SetAngle(u8 angle)
{
	OCR1B=((angle*(u32)1000)/180)+999;
}
