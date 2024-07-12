
#ifndef SENSORS_H_
#define SENSORS_H_

u8 POT_Read(void);

/* return temp C*10; */
u16 TEMP_Read(void);

u16 PRESSURE_Read(void);

#endif /* SENSORS_H_ */