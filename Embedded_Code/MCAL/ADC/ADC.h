/*
 * ADC.h
 *
 *  Created on: Sep 24, 2022
 *      Author: 10
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../STD_Types.h"
#include "../../Bit_Math.h"
#include "ADCconfig.h"

void ADC_init(void);
uint16_t ADC_read(uint8_t channel);

#endif /* MCAL_ADC_ADC_H_ */
