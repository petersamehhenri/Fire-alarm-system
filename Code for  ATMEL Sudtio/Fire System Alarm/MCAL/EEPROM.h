#ifndef EEPROM_H_
#define EEPROM_H_
#include "StdTypes.h"

u8 EEPROM_Read(u16 uiAddress);

void EEPROM_Write(u16 address , u8 data);


#endif /* EEPROM_H_ */