/*
 * I2C.c
 *
 * Created: 1/25/2024 1:18:00 AM
 *  Author: peter
 */ 

#include "I2C.h"
#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"

void I2C_Init_Master(void)
{
	// bit rate=400000 kbps , F_CPU=8000000 ---> SCL(bit rate)= F_CPU / (16 + 2(TWBR) * 4^TWPS)
	// 400000=8000000/(16+2(TWBR))
	
	TWBR=0x07;		// bit rate
	TWSR=0x00; // prescaler to 1
}
void I2C_Init_Slave(void)
{
	TWAR = 0b000010 ;	// my address = 0x01 --> TWAR=(0000001)0
	SET_BIT(TWCR,TWEN); //  Enable TWI
}
void I2C_Start(void)
{
	SET_BIT(TWCR,TWINT); // Setting this bit initiates the start condition and clears any previous interrupt status.
	SET_BIT(TWCR,TWEN); // This enables the I2C hardware to send and receive data.
	SET_BIT(TWCR,TWSTA); // This sends the start condition on the I2C bus

	while (!READ_BIT(TWCR,TWINT)); // Wait For TWINT Flag Set ... operation Done
	while((TWSR&0xf8) != START_ACK); // wait for the ACK
}

void I2C_Repeated_Start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	while (!READ_BIT(TWCR,TWINT)); // Wait For TWINT Flag Set ... operation Done
	while((TWSR&0xF8) != REP_START_ACK); // wait for the ACK
}



void I2C_Write_Byte(u8 data)
{
	TWDR=data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!READ_BIT(TWCR,TWINT)); // Wait For TWINT Flag Set ... operation Done
	//while((TWSR&0xF8) != I2C_MT_DATA_ACK); // wait for Data ACk
}

u8 I2C_Read_Byte_ACK(void)
{
	//  clears any previous interrupt status.
	// This enables the I2C hardware to send and receive data.
	TWCR = (1<<TWINT) | (1<<TWEN)| (1<<TWEA);
	
	while (!READ_BIT(TWCR,TWINT)); // Wait For TWINT Flag Set ... operation Done
	while((TWSR&0xF8) != I2C_MR_DATA_ACK   ); // wait for Data received with ACk
	
	return TWDR; // Return the Value from data register
}

u8 I2C_Read_Byte_NACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while (!READ_BIT(TWCR,TWINT)); // Wait For TWINT Flag Set ... operation Done
	while((TWSR&0xF8) != I2C_MR_DATA_NACK); // wait for Data received with NACk
	
	return TWDR; // Return the Value from data register
}

void I2C_STOP(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	SET_BIT(TWCR,TWSTO);
}
