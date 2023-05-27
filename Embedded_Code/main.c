/*
 * UART_TestApp.c
 *
 * Created: 3/3/2023 12:15:49 AM
 * Author : Abdallah
 */

#define F_CPU 16000000UL

#include "HAL/Lcd/Lcd.h"
#include <util/delay.h>
#include "HAL/DHT11/dht11.h"
#include "string.h"


uint8_t I_RH,I_Temp;
uint8_t sentData[8];


int main(void)
{
	Dio_init();
	Lcd_Init();
	UART_Init();
	ADC_init();




	uint8_t TempReading = 0,GasReading = 0;
	uint8_t rainReading=0;
	uint8_t Humidity=0,Temperature=0;

	lcd_clear();		/* Clear LCD */
	LCD_GoTo(0,0);


	Lcd_sendString("Rain=");
	LCD_GoTo(1,0);
	Lcd_sendString("Gas=");


    while (1)
    {


		// 2.5024 --> *(2.56/1023)*1000  --> Internal of ADC is 2.56
		rainReading = ADC_read(ADC7)*4.88;   // Millivolts    --> PA3
		rainReading = (int)(rainReading / 10.00);   // To Celsius
		GasReading = ADC_read(ADC0)*4.88;     // --> PA6
		GasReading = (int)(GasReading / 10.00);   // To Celsius
		// Dio_read(PORTD_2,&rainReading);




		UART_SendNum(rainReading);
		UART_SendByte('r');
		UART_SendNum(GasReading);
		UART_SendByte('m');


		LCD_GoTo(0,10);
 		Lcd_displayNum((int)rainReading);
 		LCD_GoTo(1,10);
 		Lcd_displayNum((int)GasReading);





 		_delay_ms(1500);
//



 		lcd_clear();
 		Lcd_sendString("Rain=");
 		LCD_GoTo(1,0);
 		Lcd_sendString("Gas=");




// 		UART_SendNum((int)GasReading);
// 		UART_SendString("m");
// 		UART_SendNum(12);
// 		UART_SendString("r");




		//UART_SendNum((int)TempReading);

		_delay_ms(500);


    }
	return 0;
}

