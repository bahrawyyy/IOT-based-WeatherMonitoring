
#include "dht11.h"

extern uint8_t I_RH,I_Temp;
uint8_t D_RH,D_Temp,CheckSum,dataByte=0;



void start_signal()
{

	// Resetting port
	DDRC |= (1<<DHT11_PIN);   // Output
	PORTC |= (1<<DHT11_PIN);  // High
	_delay_ms(100);


	DDRC |= (1<<DHT11_PIN);    // Set dht11 pin as an output
	PORTC &= ~(1<<DHT11_PIN);   // First Send low pulse
	_delay_ms(20);              // Delay for 20 ms
	PORTC |= (1<<DHT11_PIN);    // Send high pulse
}


void responce_signal()
{
	DDRC &= ~(1<<DHT11_PIN);
	while(PINC & (1<<DHT11_PIN));  	// Wait for low pulse
	while((PINC & (1<<DHT11_PIN))==0);	// Wait for high pulse
	while(PINC & (1<<DHT11_PIN));	// Wait for low pulse

//	Lcd_sendChar('S');


}

uint8_t read_DHT11()
{
	int i;
	for(i=0;i<8;i++){
		while((PINC & (1<<DHT11_PIN)) == 0);  // Check high pulse
		_delay_us(30);   // Wait for 50us then check bit value
		if(PINC & (1<<DHT11_PIN))   // If it is 1, store 1 in dataByte
			dataByte = (dataByte<<1) | (0x01);
		else  // Otherwise store 0
			dataByte = (dataByte<<1);
		while((PINC & (1<<DHT11_PIN)));     // Wait for low pulse
 	}
	 return dataByte;
}

char data[5];

void DHT11_Init()
{
	start_signal();
	responce_signal();
}

void DHT11_FULL_READING()
{
	I_RH = read_DHT11();       // read integer part of humidity
	D_RH = read_DHT11();       // read fraction part of humidity
	I_Temp = read_DHT11();     // read integer part of temperature
	D_Temp = read_DHT11();     // read fraction part of temperature
	CheckSum = read_DHT11();   // read check sum



	if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
	{
		lcd_gotoxy(0,0);
		Lcd_sendString("Error");
	}else{
		itoa(I_RH,data,10);
		lcd_gotoxy(11,0);
		Lcd_sendString(data);
		Lcd_sendString(".");

		itoa(D_RH,data,10);
		Lcd_sendString(data);
		Lcd_sendString("%");


		itoa(I_Temp,data,10);
		lcd_gotoxy(6,1);
		Lcd_sendString(data);
		Lcd_sendString(".");

		itoa(D_Temp,data,10);
		Lcd_sendString(data);
		Lcd_sendChar(0xDF);
		Lcd_sendString("C");

		itoa(CheckSum,data,10);
		Lcd_sendString(data);
		Lcd_sendString(" ");
	}
//	_delay_ms(500);


//	// Resetting port
//	DDRC |= (1<<DHT11_PIN);   // Output
//	PORTC |= (1<<DHT11_PIN);  // High
//	_delay_ms(100);
}


