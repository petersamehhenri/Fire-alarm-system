#define F_CPU	8000000
#include <util/delay.h>
#include "Timers.h"
#include "Timers_Services.h"
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "Ultrasonic.h"
#include "Ultrasonic_Cfg.h"


static volatile u16 t1, t2;
static volatile u8 flag;


u16 arr_old[4], arr_new[4];

void ULTRASONIC_Init(void)
{
	Timer1_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_8);
	Timer1_ICU_InterruptEnable();
	sei();
}


static void icu_f1(void)
{
	if (flag==0)
	{
		t1=ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag=1;
	}
	else if(flag==1)
	{
		t2=ICR1;
		flag=2;
	}
}


u16 Get_Distance(ULTRASONIC_num num)
{
	Timer1_ICU_SetCallBack(icu_f1);
	
	u16 time, distance;
	
	flag=0;
	TCNT1=0;
	Timer1_InputCaptureEdge(RISING);
	switch(num)
	{
		case ULTRASONIC_1:
		DIO_WritePin(ULTRASONIC_1_TR,HIGH);
		_delay_us(10);
		DIO_WritePin(ULTRASONIC_1_TR,LOW);
		break;
		
		case ULTRASONIC_2:
		DIO_WritePin(ULTRASONIC_2_TR,HIGH);
		_delay_us(10);
		DIO_WritePin(ULTRASONIC_2_TR,LOW);
		break;
		
		case ULTRASONIC_3:
		DIO_WritePin(ULTRASONIC_3_TR,HIGH);
		_delay_us(10);
		DIO_WritePin(ULTRASONIC_3_TR,LOW);
		break;
		
		case ULTRASONIC_4:
		DIO_WritePin(ULTRASONIC_4_TR,HIGH);
		_delay_us(10);
		DIO_WritePin(ULTRASONIC_4_TR,LOW);
		break;
	}
	while(flag<2);
	time=t2-t1;
	distance=time/58;
	return distance;
}

u8 i=0;
u16 distance;
void ULTRASONIC_Runnable(void)
{
	distance=Get_Distance(ULTRASONIC_1+i);
	arr_old[i]=distance;
	i++;
	if (i==4)
	{
		for(u8 i=0, j=0; j<4; j++, i++)
		{
			arr_new[j]=arr_old[i];
		}
		i=0;
	}
}


u16 DISTANCE_READ(ULTRASONIC_num num)
{
	u16 distancee=arr_new[(num-1)];
	return distancee;
}