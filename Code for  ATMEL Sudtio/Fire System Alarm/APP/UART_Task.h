
#ifndef UART_TASK_H_
#define UART_TASK_H_
#include "Servo.h"
#include "RGB.h"

#define	arr_size	10
	
	
typedef struct{
	u8 *str;
	void (*pf)(u8);
}UartTask_type;


u8 StringCompare(u8*str1, u8*str2);

u8 Rec_StrAndNum(u8*str, u8*str_new);
	
u8 SearchInStruct(UartTask_type *arr_struct, u8*str2);	

void LED_ON(u8 led);

void LED_OFF(u8 led);

 void Set_Function(u8 index, u8 num);

#endif /* UART_TASK_H_ */