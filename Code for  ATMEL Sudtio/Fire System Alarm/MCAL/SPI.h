

#ifndef SPI_H_
#define SPI_H_

typedef enum{
	SLAVE,
	MASTER
	
	
	}SPI_Mode_type;


void SPI_Init(SPI_Mode_type mode);

u8 SPI_SendReceive(u8 data);

void SPI_SendNoBlock(u8 data);

u8 SPI_ReceivePerodic(u8*pdata);


#endif /* SPI_H_ */