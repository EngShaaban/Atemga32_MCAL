/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   UART_Prog                                       */
/* Filename              :   UART_Prog.c                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Created on            :   Feb 27, 2022                                    */
/* Version               :   1.0.0                                           */
/* Toolchain             :   avr-gcc (4.3.3)                                 */
/* Target                :   ATmega32                                        */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/******************************  INCLUDES  ***********************************/
#include "LIB/STD_TYPES.h"
#include "LIB/errorStates.h"

#include "UART_Priv.h"
#include "UART_Cnfg.h"


void UART_enuInit( void )
{

#if    UART_PURE_DATA_IN_FRAME == CHAR_SIZE_5
#elif  UART_PURE_DATA_IN_FRAME == CHAR_SIZE_6

	/* 5.Configure the UCSRC Regis. to:                                          *
	 *                               5.0_ Write on the UCSRC Regis.              *
	 *                                    Set URSEL Bit.                         *
	 *                                                                           *
	 *                               5.1_ Asynchronous Operation                 *
	 *                                        Clear UMSEL Bit.                   *
	 *                                                                           *
	 *                               5.2_ Disable Parity Check                   *
	 *                                        Clear  UPM0 Bit.                   *
	 *                                        Clear  UPM1 Bit.                   *
	 *                                                                           *
	 *                               5.3_ Enable Tow Stop Bit                    *
	 *                                         Set USBS Bit                      *
	 *                                                                           *
	 *                               5.4_ Select 8-Bit for character Size.       *
	 *                                          Set UCSZ0 Bit                    *
	 *                                          Set UCSZ1 Bit                    *
	 *                                                                           *
	 *                               5.4_ For Asynchronous mode .                *
	 *                                          Clear UCPOL Bit.                 *
	 *                                                                           *
	 ****************************************************************************/
	UCSRC =( (UART_MSK_BIT<<URSEL)|(UART_MSK_BIT<<UCSZ0)  );

#elif  UART_PURE_DATA_IN_FRAME == CHAR_SIZE_7

	/****************************************************************************
	 * 5.Configure the UCSRC Regis. to:                                          *
	 *                               5.0_ Write on the UCSRC Regis.              *
	 *                                    Set URSEL Bit.                         *
	 *                                                                           *
	 *                               5.1_ Asynchronous Operation                 *
	 *                                        Clear UMSEL Bit.                   *
	 *                                                                           *
	 *                               5.2_ Disable Parity Check                   *
	 *                                        Clear  UPM0 Bit.                   *
	 *                                        Clear  UPM1 Bit.                   *
	 *                                                                           *
	 *                               5.3_ Enable Tow Stop Bit                    *
	 *                                         Set USBS Bit                      *
	 *                                                                           *
	 *                               5.4_ Select 8-Bit for character Size.       *
	 *                                          Set UCSZ0 Bit                    *
	 *                                          Set UCSZ1 Bit                    *
	 *                                                                           *
	 *                               5.4_ For Asynchronous mode .                *
	 *                                          Clear UCPOL Bit.                 *
	 *                                                                           *
	 ****************************************************************************/
	UCSRC =( (UART_MSK_BIT<<URSEL)|(UART_MSK_BIT<<UCSZ1)  );


#elif      UART_PURE_DATA_IN_FRAME == CHAR_SIZE_8

	/****************************************************************************
	 * 5.Configure the UCSRC Regis. to:                                          *
	 *                               5.0_ Write on the UCSRC Regis.              *
	 *                                    Set URSEL Bit.                         *
	 *                                                                           *
	 *                               5.1_ Asynchronous Operation                 *
	 *                                        Clear UMSEL Bit.                   *
	 *                                                                           *
	 *                               5.2_ Disable Parity Check                   *
	 *                                        Clear  UPM0 Bit.                   *
	 *                                        Clear  UPM1 Bit.                   *
	 *                                                                           *
	 *                               5.3_ Enable Tow Stop Bit                    *
	 *                                         Set USBS Bit                      *
	 *                                                                           *
	 *                               5.4_ Select 8-Bit for character Size.       *
	 *                                          Set UCSZ0 Bit                    *
	 *                                          Set UCSZ1 Bit                    *
	 *                                                                           *
	 *                               5.4_ For Asynchronous mode .                *
	 *                                          Clear UCPOL Bit.                 *
	 *                                                                           *
	 ****************************************************************************/
	UCSRC =( (UART_MSK_BIT<<URSEL)|(UART_MSK_BIT<<UCSZ0)|(UART_MSK_BIT<<UCSZ1)  );

#endif





	//1.Configure the UART Transmission Speed.
#if UART_SPEED_MODE == NORMAL

	UCSRA  &=~(UART_MSK_BIT<<U2X);

#elif UART_SPEED_MODE == DOUBLE

	UCSRA  |=(UART_MSK_BIT<<U2X);

#endif



	UBRRL = MY_UBRRL  ;
	UBRRH = MY_UBRRH  ;

#if  UART_MODE  ==  TRANSMITTER

	UART_TX_START();

#elif   UART_MODE  ==  RECEIVER

	UART_RX_START();

#elif   UART_MODE   == TRANSCEIVER

	//3.Enable the  RXEN and TXEN Bit
	UART_TX_START();
	UART_RX_START();


#endif




	//2.Configure the UART Multi-processor Communication Mode.
#if  UART_MPC_MODE   ==  DISABLE_MPCM

	UCSRA  &=~(UART_MSK_BIT<<MPCM);

#elif UART_MPC_MODE   ==  ENABLE_MPCM

	UCSRA  |=(UART_MSK_BIT<<MPCM);

#endif

}//End of UART_



ES_t UART_enuSendByte(u8 Copy_u8Data)
{
	ES_t Local_enuErrorState  = ES_NOK ;

	// Poll the for the UDRE
	while( !((UCSRA>>UDRE)&1) );

	UDR = Copy_u8Data  ;

	//Check for the Completion of Transmittioin.
	if( (UCSRA>>TXC)&1 )
	{
		//Clear the flag.
		UCSRA |=(UART_MSK_BIT<<TXC);

		Local_enuErrorState = ES_OK ;
	}
	else
	{
		//Do nothing.
	}

	return Local_enuErrorState  ;
}//End of UART_enuSendByte().


ES_t UART_enuRecieveByte( u8* Copy_u8Data )
{
	ES_t Local_enuErrorState  = ES_NOK ;

	if(  Copy_u8Data != NULL  )
	{
		//There is NO Data to Read.
		while( !(( UCSRA>>RXC)&1) );

		*Copy_u8Data = UDR ;

		Local_enuErrorState  = ES_OK ;
	}
	else
	{
		Local_enuErrorState  = ES_NULL_POINTER;
	}

	return Local_enuErrorState  ;
}//End of UART_enuRecieveByte().

//          UART_enuSendString( arr );

ES_t UART_enuSendString( const u8* Copy_pcData)
{
	ES_t Local_enuErrorState  = ES_NOK ;

	if( Copy_pcData != NULL )
	{

		while( *Copy_pcData != '\0')
		{

			while( !((UCSRA>>UDRE)&1) );

			UDR = *Copy_pcData ;

			Copy_pcData++ ;

		}

		Local_enuErrorState  = ES_OK ;
	}
	else
	{
		Local_enuErrorState  = ES_NULL_POINTER ;
	}

	return Local_enuErrorState  ;
}//End of UART_enuRecieveByte().



ES_t UART_enuReceiveString(u8*  Copy_pcData)
{
	ES_t Local_enuErrorState  = ES_NOK ;

	if( Copy_pcData != 	NULL )
	{
		u8 Local_u8Data  = 0  ;

		u8 Local_u8Index = 0  ;

		while( !((UCSRA>>RXC)&1) );

		u8 Local_u8Terminator = UDR ;

		while(1)
		{
			while( !((UCSRA>>RXC)&1) );

			Local_u8Data = UDR ;

			if(Local_u8Data == Local_u8Terminator )
			{
				Copy_pcData[Local_u8Index] = '\0' ;

				break;
			}
			else
			{
				Copy_pcData[Local_u8Index] = Local_u8Data ;

				Local_u8Index++ ;
			}

		}

		Local_enuErrorState = ES_OK ;
	}
	else
	{
		Local_enuErrorState = ES_NULL_POINTER ;
	}

	return Local_enuErrorState  ;
}//End of UART_enuRecieveByte().

