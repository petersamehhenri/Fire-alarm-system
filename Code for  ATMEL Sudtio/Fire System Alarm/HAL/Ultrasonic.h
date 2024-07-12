
#include "StdTypes.h"
#include "Ultrasonic_Cfg.h"
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

typedef enum{
	ULTRASONIC_1=1,
	ULTRASONIC_2,
	ULTRASONIC_3,
	ULTRASONIC_4
	}ULTRASONIC_num;


void ULTRASONIC_Init(void);

u16 DISTANCE_READ(ULTRASONIC_num num);

u16 Get_Distance(ULTRASONIC_num num);

void ULTRASONIC_Runnable(void);


#endif /* ULTRASONIC_H_ */