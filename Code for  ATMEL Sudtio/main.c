#define F_CPU	8000000
#include <util/delay.h>
#include "MemMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "Segment.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Interface.h"
#include "ADC_Interface.h"
#include "Sensors.h"
#include "Sensors_Cfg.h"
#include "EX_Interrupt.h"
#include "Timers.h"
#include "RGB.h"
#include "Timers_Services.h"
#include "Ultrasonic_Cfg.h"
#include "Ultrasonic.h"
#include "Servo.h"
#include "UART.h"
#include "UART_Service.h"
#include "SPI.h"
#include "I2C.h"
#include "EEPROM.h"
#include "WDT.h"


#define YELLOW_LED_ON		SET_BIT(PORTC,1)
#define RED_LED_ON			SET_BIT(PORTC,0)
#define MOTOR_ON			SET_BIT(PORTC,2)
#define BUZZER_ON			SET_BIT(PORTC,5)

#define YELLOW_LED_OFF		CLR_BIT(PORTC,1)
#define RED_LED_OFF			CLR_BIT(PORTC,0)
#define MOTOR_OFF			CLR_BIT(PORTC,2)
#define BUZZER_OFF			CLR_BIT(PORTC,5)




int main(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_VCC,ADC_SCALER_64);
	KEYPAD_Init();

	u8 yello_flag=0, red_flag=0, reset_flag=0, k,key2, pass_flag=0;
	u16 smoke, temp;
	u8 pass=123,num=0;
	u8 j=0;

	pass=EEPROM_Read(1);
	while(1)
	{
		temp=TEMP_Read()/10;
		smoke=POT_Read();


		key2=KEYPAD_GetKey();
		if (key2!=NO_KEY)
		{
			if(key2=='c')
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString(" ENTER THE NEW");
				LCD_SetCursor(1,4);
				LCD_WriteString("PASSWORD: ");
				while(pass_flag==0)
				{
					key2=KEYPAD_GetKey();
					if (key2!=NO_KEY)
					{
						if(key2>='0' && key2<='9')
						{
							LCD_SetCursor(1,0);
							LCD_SetCursor(0,j);
							LCD_WriteChar(key2);
							num=num*10+key2-'0';
							j++;
							LCD_SetCursor(0,j);
							LCD_WriteString("               ");

							LCD_SetCursor(1,0);
							LCD_WriteString("               ");
						}
						else if(key2=='=')
						{
							EEPROM_Write(1,num);
							pass=EEPROM_Read(1);
							pass_flag=1;
							LCD_Clear();
							LCD_SetCursor(0,2);
							LCD_WriteString("PASSWORD SET");
							_delay_ms(2000);
							LCD_Clear();
						}
					}
				}
			}
		}

		//FIRST STARE
		if((temp<=50) && (smoke<50)  && (yello_flag==0) && (red_flag==0) && (reset_flag==0))
		{
			pass=EEPROM_Read(1);
			LCD_SetCursor(0,0);
			LCD_WriteNumber(temp);
			LCD_WriteString("C    ");
			LCD_SetCursor(0,8);
			LCD_WriteString("FINE");
			LCD_SetCursor(1,0);
			LCD_WriteString("       ");
		}

		//SECOND STATE
		if(((temp>=50) || (yello_flag==1)) && ((smoke)<=50) && (red_flag==0) && (reset_flag==0))
		{
			yello_flag=1;

			YELLOW_LED_ON;
			LCD_SetCursor(0,0);
			LCD_WriteNumber(temp);
			LCD_WriteString("C    ");


			LCD_SetCursor(0,8);
			LCD_WriteString("HEAT");
			LCD_WriteString("    ");

			LCD_SetCursor(1,0);
			LCD_WriteNumber(smoke);

			if((temp<50) && (temp>45))
			{
				YELLOW_LED_ON;
				LCD_SetCursor(1,0);
				LCD_WriteString("          ");
			}
			else if(temp<45)
			{
				YELLOW_LED_OFF;
				yello_flag=0;
			}
		}

		//THIRD STATE
		if((((temp>50) && (smoke>50)) || (red_flag==1)))
		{
			while(reset_flag==0)
			{
				YELLOW_LED_OFF;
				RED_LED_ON;
				MOTOR_ON;
				BUZZER_ON;

				red_flag=1;

				LCD_SetCursor(0,0);
				LCD_WriteNumber(temp);
				LCD_WriteString("C   ");

				LCD_SetCursor(0,8);
				LCD_WriteString("FIRE");


				LCD_SetCursor(0,0);
				LCD_WriteString("                    ");

				LCD_SetCursor(0,0);
				LCD_WriteString("ENTER PASSWORD:");

				LCD_SetCursor(1,0);
				LCD_WriteString("                    ");
				while(red_flag==1)
				{
					k=KEYPAD_GetKey();
					if(k!=NO_KEY)
					{
						LCD_SetCursor(0,j);
						LCD_WriteNumber(k);
						LCD_WriteString("                  ");
						if(k>='0' && k<='9')
						{
							LCD_SetCursor(1,0);
							LCD_WriteString("                    ");
							LCD_SetCursor(0,j);
							LCD_WriteChar('*');
							LCD_WriteString("               ");

							num=num*10+k-'0';
							j++;
						}
						else if(k=='=')
						{
							j=0;
							if((num==pass))
							{
								smoke=POT_Read();
								if((smoke<50))
								{
									LCD_SetCursor(0,0);
									LCD_WriteString("                ");
									LCD_SetCursor(1,0);
									LCD_WriteString("     CORRECT          ");

									BUZZER_OFF;
									RED_LED_OFF;
									MOTOR_OFF;
									red_flag=0;
									reset_flag=1;
								}
								else if((smoke>50))
								{
									LCD_SetCursor(0,0);
									LCD_WriteString("  CORRECT BUT       ");
									LCD_SetCursor(1,0);
									LCD_WriteString("   SMOKE>50!   ");
									num=0;
									red_flag=1;
								}
							}

							else if(num!=pass)
							{
								LCD_SetCursor(0,0);
								LCD_WriteString("                ");
								LCD_SetCursor(1,0);
								LCD_WriteString("     WRONG        ");

								num=0;
							}
						}
					}
				}
			}
			reset_flag=0;
			LCD_SetCursor(1,0);
			LCD_WriteString("                    ");
			YELLOW_LED_OFF;
		}
	}
}

