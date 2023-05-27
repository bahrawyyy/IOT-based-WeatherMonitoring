/*
 * UART_Service.c
 *
 * Created: 3/3/2023 10:07:52 AM
 *  Author: Abdallah
 */



#include "UART_Service.h"
#include "../HAL/Lcd/Lcd.h"   // Just for testing


// Because the following functions are not supported by UART, as the buffer of
// the UART can handle only one byte
// So, we will put somewhere else than UART in MCAL
// Also, if you want to use them by another MCU, you can do it just easily without changing anything




// This is a synchronous function. what does it mean ?
// It means that it won't get out until it sends the whole string completely
// Then you can deal with the string after it normally
// The disadvantage it will delay the processor until it finishes

void UART_SendString(char *str)
{
	uint8_t i = 0;
	while(str[i] != '\0')
	{
		UART_SendByte(str[i]);
		i++;
	}
}


void UART_SendNum(uint16_t num)
{
	uint8_t ch[10],i=0,j=0;
	if(num == 0)
	{
		UART_SendByte('0');
	}
	else
	{
		while(num)
		{
			ch[i] = num % 10 + '0';  //To convert int to char
			num /= 10;
			i++;
		} //Thus number entered is reversed so, we want to display it correctly
		for(j=i;j>0;j--)
		{
			UART_SendByte(ch[j-1]);
		}
	}
}

/* Also a synchronous */

void UART_ReceiveString(uint8_t *str)
{
	// We need a buffer(an array of n elements) to store the string
	// As the UDR will just store a byte
	// We will consider that if he sends a # then the data has finished

	uint8_t i = 0;
	str[i] = UART_ReceiveByte();

	// We must call it once before the while as it is by default empty, so
	// it isn't a #, so it won't go inside the while, you can do it by do while also
	while(str[i] != 0x0d)   // until enter (0x0d in Proteus) it differs in HW
	{                       // It will send 0x0A then 0x0d
		i++;
		str[i] = UART_ReceiveByte();
	}
	str[i] = '\0';



}



/************************************************************************/
/*                                   Protocol                           */
/************************************************************************/



void UART_SendString_MyProtocol(uint8_t *str)
{
	uint8_t i = 0, length = 0;
	uint16_t sum = 0;
	// Calculate the length of the string
	while(str[length] != '\0')
	{
		sum += str[length];   // Calculate the sum of the characters
		length++;
	}
	UART_SendByte(length);  // First send the no. of characters
	while(str[i] != '\0')
	{
		UART_SendByte(str[i]);   // Send each character
		i++;
	}
	// Send the sum divided into two bytes
	UART_SendByte((uint8_t)sum);   // first send the least byte
	UART_SendByte((uint8_t)(sum>>8));   // Then the most
}




uint8_t UART_ReceiveString_MyProtocol(uint8_t *str)
{
	// Check for errors, then put only the useful data in the buffer (str)
	uint8_t i,length = UART_ReceiveByte();  // Receiving the length
	uint16_t sum_receive=0,sum_call=0;
	uint16_t first_byte, second_byte;
	// Receiving the data and put it in the buffer
	// You must receive it
	for(i=0;i<length;i++)
	{
		str[i] = UART_ReceiveByte();
		sum_call += str[i];
	}
	first_byte = UART_ReceiveByte();
	second_byte = UART_ReceiveByte();


	sum_call = first_byte | (second_byte << 8);

	/******************* Test Code *********************/
	LCD_GoTo(0,4);
	Lcd_displayNum(length);
	LCD_GoTo(0,7);
	Lcd_displayNum(sum_call);
	LCD_GoTo(0,12);
	Lcd_displayNum(sum_receive);
	///////////////////////////////////////////////////


	if(sum_call == sum_receive){
		return 1;
	}else{
		return 0;
	}





}
