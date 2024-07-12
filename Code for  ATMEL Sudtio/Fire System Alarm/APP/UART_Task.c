#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "UART_Task.h"



static UartTask_type arr_struct[arr_size]={
	{"SERVO=",SERVO_SetAngle},
	{"RGB=",RGB_Set},
	{"LED_ON=",LED_ON},
	{"LED_OFF=",LED_OFF},
};


u8 StringCompare(u8*str1, u8*str2)
{
	u8 flag,i;
	for (i=0; (((str1[i])!='=') || ((str2[i])!='=')); i++)
	{
		if (str1[i]!=str2[i])
		{
			flag=0;
			break;
		}
		else
		{
			flag=1;
		}
	}
	return flag;
}

	
	
u8 Rec_StrAndNum(u8*str, u8*str_new)
{
	u8 num, res=0;
	for(u8 i=0; str[i]; i++)
	{
		str_new[i]=str[i];
		if(str[i]=='=')
		{
			str_new[i]='=';
			str_new[i+1]=0;
			for(i=i+1; str[i]; i++)
			{
				num=str[i]-'0';
				res=res*10+num;
			}
		}
	}
	return res;
}
	
	
u8 SearchInStruct(UartTask_type *arr_struct, u8*str2)
{
	u8 i,flag;
	for(i=0; i<arr_size; i++)
	{

		if(StringCompare(arr_struct[i].str,str2))
		{
			flag=i;
			break;
		}
		else
		{
			flag=255;
		}
	}
	return flag;
}


void LED_ON(u8 led)
{
	SET_BIT(PORTC,led);
}

void LED_OFF(u8 led)
{
	CLR_BIT(PORTC,led);
}


void Set_Function(u8 index, u8 num)
{
	arr_struct[index].pf(num);
}



