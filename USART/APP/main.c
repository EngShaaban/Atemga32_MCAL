/*
 * main.c
 *
 *  Created on: Feb 27, 2022
 *      Author: SHAABAN
 */

#include "../LIB\STD_TYPES.h"
#include "../LIB\errorStates.h"


#include "../MCAL/DIO/DIO_interface.h"

#include "../MCAL/USART/USART_Interface.h"
#include "../MCAL/USART/USART_Cnfg.h"
#include "../MCAL/GIE/GIE_interface.h"



#ifndef F_CPU
#define F_CPU    (1000000UL)
#endif

u16 Local_u16Data ;

void func( u8* para )
{
	Local_u16Data = (u16)(*para);
}

int main(void)
{

	GIE_enuEnable();


	//Configure the TXD(PD1) pin as output pin
	DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN1 , DIO_OUTPUT_PIN);

	//Configure the RXD(PD0) pin as INPUT pin
	DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN0 , DIO_INPTU_PIN);

	USART_enuInit();
	//USART_enuRecieveByteASync(void (*Cpy_pFunc)(void*) , u8* Cpy_pu8Para );

	while(1)
	{

		USART_enuRecieveByteASync( func , (u8*)Local_u16Data);
		//USART_enuRecieveByteSync( &Local_u16Data );
		USART_enuSendByteSync( &Local_u16Data  );


	}




	return 0 ;

}
