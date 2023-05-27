/*
 * UART.c
 *
 * Created: 3/3/2023 12:17:24 AM
 *  Author: Abdallah
 */


#include "UART.h"
#include "UART_Cfg.h"

const uint16_t BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE]=
{{{103, 51, 25, 16, 12,  8},{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34}},
{{207,103, 51, 34, 25, 16},{416,207,103, 68 ,51, 34},{832,416,207,138,103, 68}}};

void UART_Init(void)
{
	uint8_t  UCSRC_var=0;
	uint16_t UBRR_var=0;
	/***************************** transmission speed***************************/
	#if (SPEED_MODE==NORMAL_SPEED)
	CLR_BIT(UCSRA,U2X);
	#elif (SPEED_MODE==DOUBLE_SPEED)
	SET_BIT(UCSRA,U2X);
	#endif

	//******************set URSEL to write data to UCSRC register***************/
	SET_BIT(UCSRC_var,URSEL);

	//********************************synch***********************************/
	#if (SYNCH_MODE==SYNCH)
	SET_BIT(UCSRC_var,UMSEL)
	#elif (SYNCH_MODE==ASYNCH)
	CLR_BIT(UCSRC_var,UMSEL);
	#endif
	//*****************************parity mode*******************************/

	#if (PARITY_MODE==NO_PARITY)
	CLR_BIT(UCSRC_var,UPM0);
	CLR_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE==EVEN_PARITY)
	CLR_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE==ODD_PARITY)
	SET_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#endif
	//************************Data bits*******************************/
	#if (N_DATA_BITS==_5_DATA_BITS)
	CLR_BIT(UCSRC_var,UCSZ0);
	CLR_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRC_var,UCSZ2);
	#elif (N_DATA_BITS==_6_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	CLR_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRC_var,UCSZ2);
	#elif (N_DATA_BITS==_7_DATA_BITS)
	CLR_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_8_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	CLR_BIT(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_9_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
	#endif
	//************************Stop bits*******************************/
	#if (N_STOP_BITS==ONE_STOP_BIT)
	CLR_BIT(UCSRC_var,USBS);
	#elif (N_STOP_BITS==TWO_STOP_BIT)
	SET_BIT(UCSRC_var,USBS);
	#endif
	//*****************set UCSRC value   *******************************/
	UCSRC=UCSRC_var;

	//************************Baud rate *******************************/

	UBRR_var = BaudRateArray[SPEED_MODE][CPU_F][BUAD_RATE];
	UBRRH = (uint8_t)(UBRR_var>>8);
	UBRRL = (uint8_t)UBRR_var;

	//************************Enable  *******************************/
	//enable UART  receiver.
	SET_BIT(UCSRB,RXEN);
	//enable UART  transmitter .
	SET_BIT(UCSRB,TXEN);
}



void UART_SendByte(uint8_t data)
{
	/* UDRE flag is set when the buffer is empty and ready for transmitting
	a new byte so wait until this flag is set to one and it will cleared by
	hardware when u write new data to buffer */
	while(!GET_BIT(UCSRA,UDRE));   // Busy wait polling
	UDR = data;
}



uint8_t UART_ReceiveByte(void)
{
	/* RXC flag is set when the UART receives data so wait until this flag
	is set to one and it will be cleared by hardware when u read data  */
	while(!GET_BIT(UCSRA,RXC));  // When the data arrives
	return UDR;
}


uint8_t UART_ReceiveNoBlock(uint8_t *Pdata)
{
	// This way it will solve the problem of waiting until data received
	// Instead we will check every time if the data arrived or not
	if(GET_BIT(UCSRA,RXC)){
		*Pdata = UDR;
		return 1;
	}else{
		return 0;
	}
}



