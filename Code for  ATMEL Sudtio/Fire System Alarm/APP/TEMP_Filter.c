#include "StdTypes.h"
#include "Sensors.h"

u16 tempFiltered;
u16 tempUnFiltered;
u16 arr[10];

void TEMPFilter_Init(void)
{
	tempUnFiltered=TEMP_Read();
	tempFiltered=tempUnFiltered;
}


void TEMPFilter_Runnable(void)
{
	static u8 i;
	u32 tempSum=0;
	arr[i]=TEMP_Read();
	tempUnFiltered=arr[i];
	i++;
	if(i==10)
	{
		i=0;
	}
	for(u8 j=0; j<10; j++)
	{
		tempSum=arr[j];
	}
	tempFiltered=tempSum/10;
}

u16 TEMPFilter_getFilterValue(void)
{
	return tempFiltered;
}


u16 TEMPFilter_getUnFilterValue(void)
{
	return tempUnFiltered;
}