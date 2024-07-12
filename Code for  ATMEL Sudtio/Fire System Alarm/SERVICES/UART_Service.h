

#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

#define LITTLE   1
#define BIG     0
void UART_SendString(u8*str);
void UART_ReceiveString(u8*str);

void UART_SendNumber(u32 num);
u32 UART_RecieveNumber(void);
u8 endian_check(void);

void UART_SendStringCheckSum(u8*str);

u8 UART_ReceiveStringCheckSum(u8*str);

void UART_ReceiveString_Docklight(u8*str);

void UART_SendStringAsynch(u8*str);
void UART_ReceiveStringAsynch(u8*str);

#endif /* UART_SERVICE_H_ */