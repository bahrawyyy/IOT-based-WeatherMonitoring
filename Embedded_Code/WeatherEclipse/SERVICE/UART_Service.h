/*
 * UART_Service.h
 *
 * Created: 3/3/2023 10:08:08 AM
 *  Author: Abdallah
 */


#ifndef UART_SERVICE_H_
#define UART_SERVICE_H_

#include "../MCAL/UART/UART.h"

// It takes a pointer to the first element
void UART_SendString(char *str);

void UART_SendNum(uint16_t num);

void UART_ReceiveString(uint8_t *str);

void UART_SendString_MyProtocol(uint8_t *str);
uint8_t UART_ReceiveString_MyProtocol(uint8_t *str);


#endif /* UART_SERVICE_H_ */
