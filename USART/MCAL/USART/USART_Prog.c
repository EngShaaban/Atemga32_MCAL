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
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/errorStates.h"

#include "USART_Priv.h"

#include "interrupt.h"

#include "USART_Cnfg.h"
#include "USART_Interface.h"

//void (*USART_pvidFun_TX)(void*) = NULL ;
//void (*USART_pvidFun_RX)(void*) = NULL ;
//void (*USART_pvidFun_UDR)(void*)= NULL ;

void   (*USART_pFun)(void*) = NULL ;
u8*      USART_pu8Para      = NULL ;

/****************************************************************************/
/****************************************************************************/
/* Function Name   : USART_enuInit.                                         */
/* Description     : Utility function to initialize USART Peripheral        */
/*                   according to the configuration structure.              */
/* Argument        : None.                                                  */
/* Return          : Error state of type ES_t.                              */
/**.....................*****************************************************/
void USART_enuInit(void)
{
	u8   UCSRA_u8Temp    =  0  ;
	u8   UCSRB_u8Temp    =  0  ;
	u8   UCSRC_u8Temp    =  0  ;
	f32  UBRR_f32Temp    =  0  ;

	switch( USART0.EnableMode )
	{

	case USART_Disable :
		break;

	case USART_Tx_Only :
		UCSRB_u8Temp |=(USART_MSK_BIT<<TXEN);
		break;

	case USART_Rx_Only :
		UCSRB_u8Temp |=(USART_MSK_BIT<<RXEN);
		break;

	case USART_Tx_Rx:
		UCSRB_u8Temp |=(USART_MSK_BIT<<RXEN)|(USART_MSK_BIT<<TXEN);
		break;

	default:
		break;

	}//End of switch( USART0.EnableMode ).


	switch( USART0.CommunicationMode )
	{

	case USART_Async_NormalSpeed :
		/*1.Set USART for Async. Mode Normal Speed
		 *U2X = 0. According to DataSheet page:141
		 *
		 *             F_CPU
		 * UBRR  =   ----------   - 1
		 *           16 * BAUD
		 */
		UBRR_f32Temp = ((f32)F_CPU/((16.0)*(USART0.BaudRate)))-0.5;
		break;

	case USART_Async_DoubleSpeed:
		/*1.Set USART for Async. Mode Double Speed
		 *U2X = 1. According to DataSheet page:143
		 *
		 *             F_CPU
		 * UBRR  =   ----------   - 1
		 *            8 * BAUD
		 */

		//_Enable the Double the USART Transmission Speed Mode.
		UCSRA_u8Temp |=(USART_MSK_BIT<<U2X);

		//_Calculate the UBRR Value According the Equation.
		UBRR_f32Temp = ((f32)F_CPU/((8.0)*(USART0.BaudRate)))-0.5;
		break;

	case USART_Sync:
		//_For Synchronous Operation.
		UCSRC_u8Temp |=(USART_MSK_BIT<<UMSEL);

		/*1.Set USART for Async. Mode Double Speed
		 *U2X = 1. According to DataSheet page:143
		 *
		 *             F_CPU
		 * UBRR  =   ----------   - 1
		 *            2 * BAUD
		 */
		UBRR_f32Temp = ((f32)F_CPU/((2.0)*(USART0.BaudRate)))-0.5;


		switch(USART0.ClockPolarity)
		{
		case USART_SmapleOnFalling:
			break;

		case USART_SmapleOnRasing:
			UCSRC_u8Temp |=(USART_MSK_BIT<<UCPOL);
			break;

		default:
			break;

		}//End of switch(USART0.ClockPolarity).

		break;

		default:
			break;
	}//End of switch( USART0.CommunicationMode).

	switch(USART0.CommunicationTerminal)
	{
	case USART_SingleProcessor:
		//Already Done.
		break;

	case USART_MultiProcessor:
		//_Enable the Multi_processor Communication mode.
		UCSRA_u8Temp |=(USART_MSK_BIT<<MPCM);
		break;

	default:
		break;

	}//End of switch USART0.CommunicationTerminal.


	switch(USART0.InterruptSources)
	{
	case USART_InterruptDisable :
		break;

		//_ Enables interrupt on the RXC Flag.
	case USART_RxCompletEnable:
		UCSRB_u8Temp |=(USART_MSK_BIT<<RXCIE);
		break;

		//_ Enables interrupt on the TXC Flag.
	case USART_TxCompletEnable :
		UCSRB_u8Temp |=(USART_MSK_BIT<<TXCIE);
		break;

		//_ Enables interrupt on the UDRE Flag.
	case USART_UDR_EmptyEnable :
		UCSRB |=(USART_MSK_BIT<<UDRIE);
		break;

		//_ Enables interrupt on both TXC and RXC Flag.
	case USART_RxComplet_TxComplet_Enable:
		UCSRB_u8Temp |=(USART_MSK_BIT<<RXCIE) | (USART_MSK_BIT<<TXCIE);
		break;


		//_ Enables interrupt on both RXC and The Date hes ben red from UDR Register.
	case USART_RxComplet_UDREmpty_Enable:
		UCSRB_u8Temp |=(USART_MSK_BIT<<RXCIE)|(USART_MSK_BIT<<UDRIE);
		break;


		//_ Enables interrupt on both TXC and The Date hes ben red from UDR Register.
	case USART_TxComplet_UDREmpty_Enable  :
		UCSRB_u8Temp |=(USART_MSK_BIT<<TXCIE)|(USART_MSK_BIT<<UDRIE);
		break;


		//_ Enables interrupt on RXC , TXC and The Date hes ben red from UDR Register.
	case USART_TxComplet_RxComplet_UDR_EmptyEnable:
		UCSRB_u8Temp |=(USART_MSK_BIT<<TXCIE)|(USART_MSK_BIT<<RXCIE)|(USART_MSK_BIT<<UDRIE);
		break;

	default:
		break;

	}//End of switch(USART0.InterruptSources).


	/*******************************************
	 * -Character Size in Frame configuration
	 *  Using bits. UCSZ1 UCSZ0 in UCSRC Regis.
	 *  and UCSZ2 in UCSRB Regis.
	 *******************************************/
	switch(USART0.DataFrame)
	{
	case USART_5bitData :
		break;
	case USART_6bitData :
		UCSRC_u8Temp |=(USART_MSK_BIT<<UCSZ0);
		break;
	case USART_7bitData :
		UCSRC_u8Temp |=(USART_MSK_BIT<<UCSZ1);
		break;
	case USART_8bitData :
		UCSRC_u8Temp |=(USART_MSK_BIT<<UCSZ0)|(USART_MSK_BIT<<UCSZ1);
		break;
	case USART_9bitData :
		UCSRC_u8Temp |=(USART_MSK_BIT<<UCSZ0)|(USART_MSK_BIT<<UCSZ1);
		UCSRB_u8Temp |=(USART_MSK_BIT<<UCSZ2);
		break;
	default:
		break;

	}//End of switch(USART0.DataFrame).


	/*******************************************
	 *_Parity and  Stop Bit Handling.
	 *******************************************/
	switch(USART0.FrameControl)
	{
	case USART_ParityDisable_1stopBit:
		break;

	case USART_ParityDisable_2stopBit:
		UCSRC_u8Temp |=(USART_MSK_BIT<<USBS);
		break;

	case USART_ParityEven_1stopBit:
		UCSRC_u8Temp |=(USART_MSK_BIT<<UPM1);
		break;

	case USART_ParityEven_2stopBit:
		UCSRC_u8Temp |=(USART_MSK_BIT<<UPM1)|(USART_MSK_BIT<<USBS);
		break;

	case USART_ParityOdd_1stopBit:
		UCSRC_u8Temp |=(USART_MSK_BIT<<UPM0)|(USART_MSK_BIT<<UPM1);
		break;
	case USART_ParityOdd_2stopBit:
		UCSRC_u8Temp |=(USART_MSK_BIT<<UPM0)|(USART_MSK_BIT<<UPM1)|(USART_MSK_BIT<<USBS);
		break;

	default:
		break;

	} //End of frame Control switch().



	UCSRC_u8Temp |=(USART_MSK_BIT<<URSEL);

	UBRRL = (u8)UBRR_f32Temp;
	UBRRH = ( ((u16)UBRR_f32Temp)>>8 );

	UCSRA= UCSRA_u8Temp;

	UCSRC= UCSRC_u8Temp;
	UCSRB= UCSRB_u8Temp;


}//End of UART_enuInit().




/****************************************************************************/
/****************************************************************************/
/* Function Name   : USART_enuSendByteSync.                                     */
/* Description     : Polling technique based function To Send one Byte.     */
/* Argument        : The byte to be transmitted.                            */
/* Return          : Error state of type ES_t.                              */
/**.........................................................****************/
USART_ES_t USART_enuSendByteSync( u16 const* const Copy_pu16Data  )
{
	USART_ES_t Local_enuUSART_Error_State = USART_No_Error ;

	if( Copy_pu16Data != NULL )
	{
		// Poll the for the UDRE
		while( !((UCSRA>>UDRE) & USART_MSK_BIT) );

		if(  USART0.DataFrame == USART_9bitData )
		{
		   /**************************************************
			 * Clear the TXB8 bit in the UCSRB to make sure it
			 * is clean before writing the new Data.
			**************************************************/
			UCSRB &=~(USART_MSK_BIT<<TXB8);

			//_Write 9th bit in TXB8 in reg. UCSRB.
			UCSRB |=(((*Copy_pu16Data)>>7)&USART_MSK_BIT);
		}
		else{ /*_Nothing to Do!  */ }

		UDR = (u8)(*Copy_pu16Data) ;

	}
	else
	{
		Local_enuUSART_Error_State = USART_Null_Pointer ;
	}


	//Check for the Completion of Transmition.
	if( (UCSRA>>TXC)&1 )
	{
		//Clear the flag.
		UCSRA |=(USART_MSK_BIT<<TXC);

		Local_enuUSART_Error_State = USART_No_Error ;
	}
	else
	{
		Local_enuUSART_Error_State = USART_TX_Error;
	}

	return Local_enuUSART_Error_State  ;
}//End of UART_enuSendByte().


/****************************************************************************/
/****************************************************************************/
/* Function Name   : USART_enuRecieveByte.                                  */
/* Description     : Polling technique based function To Receive one Byte.  */
/* Argument        : Address of u8 Variable to write the Received data in.  */
/* Return          : Error state of type USART_ES_t.                        */
/**...........................................................***************/
USART_ES_t USART_enuRecieveByteSync( u16*const Copy_pu16Data )
{

	USART_ES_t Local_enuUSART_Error_State = USART_No_Error ;

	if(  Copy_pu16Data != NULL  )
	{
		//There is NO Data to Read.
		while( !(( UCSRA>>RXC) & USART_MSK_BIT) ){};

		if( USART_FRAME_ERROR  | USART_DATA_OVER_RUN_ERROR | USART_PRITY_ERROR)
		{
			if( USART_FRAME_ERROR )
			{
				//_ Frame Error Handling Code.
				Local_enuUSART_Error_State  = USART_Frame_Error     ;

			}
			else if ( USART_DATA_OVER_RUN_ERROR )
			{
				//_ Data Over Run Error Handling Code.
				Local_enuUSART_Error_State  = USART_Data_Over_Run_Error   ;
			}
			else
			{
				//_ Parity Error Handling Code.
				Local_enuUSART_Error_State  =  USART_Parity_Error  ;
			}

		}
		else  //_ No Error Occurred.
		{
			if( USART0.DataFrame == USART_9bitData )
			{
				/*_Read the 8th Bit first.
				 *                                    UCSRB:   1010 0110
				 *                      USART_MSK_BIT<<RXB8:   0000 0010
				 *                      -----------------------------------&
				 *                                       =     0000 0010
				 * (UCSRB &(USART_MSK_BIT<<RXB8))<<7          10000 0000
				 *
				 *
				 * *Copy_pu16Data = 0000 0001 0000 0000
				 *
				 */

				//_Clear Variable before Receiving a new data.
				*Copy_pu16Data  &=0x0000   ;

				*Copy_pu16Data = (( (UCSRB>>RXB8)&USART_MSK_BIT)<<7);

				//_Clear the RXB8 Bit After Reading.
				UCSRB &=~(USART_MSK_BIT<<RXB8);

			}
			else{}

			//_Clear the first eight bits in the Variable before Receiving a new data.
			*Copy_pu16Data  &=0xFF00   ;

			//_Write the new Data in the variable .
			*Copy_pu16Data |= UDR ;
		}

	}
	else
	{
		Local_enuUSART_Error_State  = USART_Null_Pointer ;
	}

	return Local_enuUSART_Error_State  ;

}//End of USART_enuRecieveByteSync().






USART_ES_t USART_enuRecieveStringSync( u8*const Copy_pu8Data )
{
	ES_t Local_enuErrorState  = ES_NOK ;

	if( Copy_pu8Data != 	NULL )
	{
		u8 Local_u8Data  = 0  ;

		u8 Local_u8Index = 0  ;

		while( !((UCSRA>>RXC)&USART_MSK_BIT) );

		u8 Local_u8Terminator = UDR ;

		while(1)
		{
			while( !((UCSRA>>RXC)&USART_MSK_BIT) );

			Local_u8Data = UDR ;

			if(Local_u8Data == Local_u8Terminator )
			{
				Copy_pu8Data[Local_u8Index] = '\0' ;

				break;
			}
			else
			{
				Copy_pu8Data[Local_u8Index] = Local_u8Data ;

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
}//End of USART_enuRecieveStringSync().


USART_ES_t USART_enuSendStringSync( u8 const* Copy_pu8Data )
{
	USART_ES_t Local_enuUSARTErrorState  = ES_NOK ;

	if( Copy_pu8Data != NULL )
	{

		while( *Copy_pu8Data != '\0')
		{

			while( !((UCSRA>>UDRE)&USART_MSK_BIT) );

			UDR = *Copy_pu8Data ;

			Copy_pu8Data++ ;

		}

	}
	else
	{
		Local_enuUSARTErrorState  = USART_Null_Pointer ;
	}

	return Local_enuUSARTErrorState  ;

}//End of USART_enuSendStringSync().

USART_ES_t USART_enuRecieveByteASync(void (*Cpy_pFunc)(u8*) , u8* Cpy_pu8Para )
{
	USART_ES_t Local_enuUSARTErrorState  = USART_No_Error ;

	if( Cpy_pFunc != NULL )
	{
		USART_pFun      =  Cpy_pFunc    ;
		USART_pu8Para   =  Cpy_pu8Para ;
	}
	else
	{
		Local_enuUSARTErrorState  = USART_Null_Pointer ;
	}

	return Local_enuUSARTErrorState  ;

}//End of USART_enuRecieveByteASync().


ISR( VECT_USART_RXC )
{
	 *USART_pu8Para  = UDR      ;
	(*USART_pFun)(USART_pu8Para);
}

ISR( VECT_USART_TXC )
{

}

ISR( VECT_USART_UDRE )
{

}

