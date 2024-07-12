
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "ADC_Interface.h"


static u8 ADC_ReadFlag=0;

void ADC_Init(ADC_VoltRef_type vref,ADC_Prescaler_type scaler)
{
	/* vref*/
	switch(vref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS1);
		CLR_BIT(ADMUX,REFS0);
		break;
		case VREF_VCC:
		CLR_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS1);
		SET_BIT(ADMUX,REFS0);
		break;
	}
	
	/*clock*/
	ADCSRA=ADCSRA&0xf8;//0b11111000
	// 	if (scaler>7)
	// 	{
	// 		scaler=7;
	// 	}
	scaler=scaler&0x07;
	ADCSRA=ADCSRA|scaler;
	
	/*ADC enable*/
	SET_BIT(ADCSRA,ADEN);
}


u16 ADC_Read(ADC_Channel_type channel)
{
	/* select ch using mux*/
	
	ADMUX=ADMUX&0xe0;
	ADMUX|=channel;
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait until end     busy wait or blocking*/
	while(READ_BIT(ADCSRA,ADSC));

	/* get reading from 2 registers*/
	return ADC;
	
}

void ADC_StartConversion(ADC_Channel_type channel)
{
	if(ADC_ReadFlag==0)
	{
		/* select ch using mux*/
		
		ADMUX=ADMUX&0xe0;
		ADMUX|=channel;
		/* start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_ReadFlag=1;
	}
	
}

u16 ADC_GetRead(void)
{
	/*wait until end     busy wait or blocking*/
	while(READ_BIT(ADCSRA,ADSC));
	ADC_ReadFlag=0;
	/* get reading from 2 registers*/
	return ADC;
}

u8 ADC_GetReadPeriodicCheck(u16*pdata)
{
	/*check if reading end*/
	if (!READ_BIT(ADCSRA,ADSC))
	{
		*pdata=ADC;
		ADC_ReadFlag=0;
		return 1;
	}
	return 0;
	
}

u16 ADC_ReadVolt(ADC_Channel_type channel)
{
	u16 adc=ADC_Read(channel);
	u16 volt =((u32)5000*adc)/1024;
	
	return volt;
	
	
}

u16 ADC_GetReadNoBlock(void)
{
	/* get reading from 2 registers*/
	return ADC;
}

