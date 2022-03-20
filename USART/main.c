/*
 * main.c
 *
 *  Created on: Feb 27, 2022
 *      Author: SHAABAN
 */

#include "LIB/STD_TYPES.h"
#include "LIB/errorStates.h"

#include "DIO\DIO_interface.h"

#include "USART_Interface.h"
#include "USART_Cnfg.h"



#ifndef F_CPU
#define F_CPU    (1000000UL)
#endif


int main(void)
{


	u8 Local_u8Data ='S';
	//Configure the TXD(PD1) pin as output pin
	DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN1 , DIO_OUTPUT_PIN);

	//Configure the RXD(PD0) pin as INPUT pin
	DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN0 , DIO_INPTU_PIN);

	 USART_enuInit();

	while(1)
	{

				UART_enuSendByte(Local_u8Data);

				 UART_enuRecieveByte( &Local_u8Data);

       //USART_enuReceiveString(  Local_u8RxData );
       //USART_enuSendString(  Local_u8RxData  );


	}




	return 0 ;

}
