/*
 * WDT.c
 *
 * Created: 2/3/2024 11:10:44 PM
 *  Author: peter
 */ 

#include "MemMap.h"
#include "StdTypes.h"
#include "WDT.h"

void WDT_Set(TimeOut_type time)
{
	cli();
	u8 wdt_value=0x08;				//WDE SET & WDTOE CLEARED 0B00001000
	wdt_value|=time;				//0B00001011
	WDTCR |= (1<<WDTOE) | (1<<WDE);
	WDTCR=wdt_value;
	sei();
}


void WDT_Stop(void)
{
	cli();
	WDTCR=(1<<WDTOE)|(1<<WDE);	
	WDTCR=0;
	sei();
}