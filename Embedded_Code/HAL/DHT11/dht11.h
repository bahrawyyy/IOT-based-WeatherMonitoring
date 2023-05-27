/*
 * dht11.h
 *
 * Created: 4/13/2023 2:45:50 PM
 *  Author: Abdallah
 */


#ifndef DHT11_H_
#define DHT11_H_

#define F_CPU 16000000UL

#include "../../STD_Types.h"
#include "../../Registers.h"
#include <util/delay.h>
#include "../../MCAL/DIO/Dio.h"
#include "stdlib.h"
#include "../Lcd/Lcd.h"
#include <stdio.h>

#define DHT11_PIN 7       // PIND6 --> DHT11_PIN

void DHT11_Init();
void start_signal();
void responce_signal();
void DHT11_FULL_READING();

//
//void DHT11_FULL_READING(uint8_t *humidity, uint8_t *temperature);
//void DHT11_Init();
//uint8_t DHT11_ReadByte();


#endif /* DHT11_H_ */
