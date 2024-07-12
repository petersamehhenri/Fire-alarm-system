/*
 * I2C.h
 *
 * Created: 1/25/2024 1:18:14 AM
 *  Author: peter
 */ 

#ifndef I2C_H_
#define I2C_H_
#include "StdTypes.h"

// status Regsiter TWSR :
#define START_ACK 0x08 // A START condition has been transmitted
#define REP_START_ACK 0x10
#define I2C_MT_SLA_W_ACK  0x18 // SLA+W has been transmitted; ACK has been received
#define I2C_MT_SLA_R_ACK  0x40 // SLA+R has been transmitted; ACK has been received

#define I2C_MT_DATA_ACK   0x28 // Data byte has been transmitted; ACK has been received

#define I2C_MR_DATA_ACK   0x50
#define I2C_MR_DATA_NACK  0x58


void I2C_Init_Master(void);
void I2C_Init_Slave(void);
void I2C_Start(void);
void I2C_Repeated_Start(void);
void I2C_MasterSend_SlaveAddress_Write(u8 slave_address);
void I2C_MasterSend_SlaveAddress_Read(u8 slave_address);
void I2C_Write_Byte(u8 data);
u8 I2C_Read_Byte_ACK(void);
u8 I2C_Read_Byte_NACK(void);
void I2C_STOP(void);

#endif /* I2C_H_ */