/*
 * UART.h
 *
 * Created: 3/3/2023 12:17:41 AM
 *  Author: Abdallah
 */


#ifndef UART_H_
#define UART_H_

#include "../../Bit_Math.h"
#include "../../Registers.h"
#include "../../STD_Types.h"


void UART_Init(void);
void UART_SendByte(uint8_t data);
uint8_t UART_ReceiveByte(void);
uint8_t UART_ReceiveNoBlock(uint8_t *Pdata);

#endif /* UART_H_ */
