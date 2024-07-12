
#include "StdTypes.h"
#include "UART.h"
#include "UART_Service.h"

void UART_SendString(u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
		
}


void UART_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=UART_Receive();
	for(;str[i]!='#';)
	{
		i++;
		str[i]=UART_Receive();
	}
	str[i]=0;
	
}

void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
	/*u8*p=&num;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);*/
	
}

u32 UART_RecieveNumber(void)
{
	u32 num;
	
	u8 b0=UART_Receive();
	u8 b1=UART_Receive();
	u8 b2=UART_Receive();
	u8 b3=UART_Receive();
	
	num=(u32)b0|((u32)b1<<8)|((u32)b2<<16)|((u32)b3<<24);
	
	u8*p=&num;
	p[0]=UART_Receive();
	p[1]=UART_Receive();
	p[2]=UART_Receive();
	p[3]=UART_Receive();
	
	return num;
	
}



u8 endian_check(void)
{
	u32 num=1;
	u8*p=&num;
	if(*p==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u32 endian_convert(u32 num)
{
	u8*p=&num;
	u8 temp;
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	temp=p[1];
	p[1]=p[2];
	p[2]=temp;
	
	num=(num>>24)|(num<<24)|((num>>8)&0x0000ff00)|((num<<8)&0x00ff0000);
	return num;
	
}

u16 endian_convert16(u16 num)
{
	num=num>>8|num<<8;
	return num;
	
}


void UART_SendStringCheckSum(u8*str)
{
	u8 i;
	u16 sum=0;
	u8 len;
	for (i=0;str[i];i++)
	{
		sum=sum+str[i];
	}	
	len=i;
	UART_Send(len);
	for (i=0;str[i];i++)
	{
		UART_Send(str[i]);
	}
	UART_Send((u8)sum);
	UART_Send((u8)(sum>>8));
}


#include "LCD_Interface.h"
u8 UART_ReceiveStringCheckSum(u8*str)
{
	u8 len,i,b1,b0;
	u16 sumCalc=0,sumRec;
	len=UART_Receive();
	for (i=0;i<len;i++)
	{
		str[i]=UART_Receive();
		sumCalc+=str[i];
	}
	b0=UART_Receive();
	b1=UART_Receive();
	/**************************/
	sumRec=(u16)b0|((u16)b1<<8);
// 	LCD_SetCursor(0,3);
// 	LCD_WriteNumber(len);
// 	LCD_WriteChar('-');
// 	LCD_WriteNumber(sumRec);
// 	LCD_WriteChar('-');
// 	LCD_WriteNumber(sumCalc);
// 	sumCalc++;
	/*********************************/
	if (sumRec==sumCalc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void UART_ReceiveString_Docklight(u8*str)
{
	u8 i=0;
	u32 num;
	u16 num2;

	str[i]=UART_Receive();
	for(;str[i]!='#';)
	{
		i++;
		str[i]=UART_Receive();
		num2=UART_RecieveNumber();
		if (num2==0x0D0A)
		{
			str[i]=0;
		}
		else
		{
			LCD_SetCursor(1,0);
			LCD_WriteString("NO");
		}
	}
}

static u8*TXStr;
void UART_SendStringAsynch(u8*str)
{
	UART_SendNoBlock(str[0]);
	UART_TX_InterruptEnable();
	TXStr=str;
}


static void TX_Func(void)
{
	static u8 i=1;
	UART_SendNoBlock(TXStr[1]);
	if (TXStr!=0)
	{
		UART_SendNoBlock(TXStr[i]);
		i++;
	} 
	else
	{
		i=1;
	}
}

u8*RXStr;
static void RX_Func(void);

void UART_ReceiveStringAsynch(u8*str)
{
	UART_RX_InterruptEnable();
	UART_RX_SetCallBack(RX_Func);
	RXStr=str;
}

static void RX_Func(void)
{
	static u8 i=0;
	RXStr[i]=UART_ReceiveNoBlock();
	i++;
}