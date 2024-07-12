
#include "StdTypes.h"
#include "MemMap.h"
#include "Utils.h"
#include "SPI.h"


void SPI_Init(SPI_Mode_type mode)
{
	if (mode==MASTER)
	{
		SET_BIT(SPCR,MSTR);
	} 
	else
	{
		CLR_BIT(SPCR,MSTR);
	}
	
	//Clock
	
	
	//Enable
	SET_BIT(SPCR,SPE);
}


u8 SPI_SendReceive(u8 data)
{
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF));
	return SPDR;
}

