/*
 * WDT.h
 *
 * Created: 2/3/2024 11:10:58 PM
 *  Author: peter
 */ 


#ifndef WDT_H_
#define WDT_H_

typedef enum{
	timeout_16ms=0,
	timeout_32ms,
	timeout_65ms,
	timeout_130ms,
	timeout_260ms,
	timeout_520ms,
	timeout_1000ms,
	timeout_2100ms,
	}TimeOut_type;

void WDT_Set(TimeOut_type time);

void WDT_Stop(void);



#endif /* WDT_H_ */