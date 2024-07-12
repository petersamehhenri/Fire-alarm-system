#include "StdTypes.h"
#include "ADC_Interface.h"
#include "Sensors_Cfg.h"
#include "Sensors.h"



u8 POT_Read(void)
{
	u16 adc=ADC_Read(POT_CH);
	u8 pot=(adc*(u32)100)/1023;
	return pot;
}

u16 TEMP_Read(void)
{
	u16 volt=ADC_ReadVolt(LM35_CH);
	u16 temp=volt;
	
	return temp;
	
}


u16 PRESSURE_Read(void)
{
	u16 adc=ADC_Read(MPX_CH);
	u16 pressure=((((adc-55)*(u32)1000)/921)+150);
	return pressure;
}
