#include "StdTypes.h"

#ifndef RGB_H_
#define RGB_H_


typedef enum{
	OFF=0,
	RED=1,
	GREEN=2,
	BLUE=3,
	WHITE=4,
	YELLOW=5,
	ORANGE=6,
	MOVE=7
}Colours_type;


void RGB_Init(void);

void RGB_Set(Colours_type colour);

void RGB_Flow(Colours_type colour1, Colours_type colour2);



#endif /* RGB_H_ */