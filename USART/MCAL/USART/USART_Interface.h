/*
 * USART_Interface.h
 *
 *  Created on: Feb 27, 2022
 *      Author: SHAABAN
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


/****************************************************************************
 * Enumeration to configure Multiprocessor Communication Mode in USART Using *
 * the Bit0?MPCM in UCSRA Register.                                          *
 ****************************************************************************/
typedef enum
{

	USART_SingleProcessor ,
	USART_MultiProcessor  ,

}USART_enuCommunicationTerminal;


/****************************************************************************
 * Enumeration to configure USART Trans. Speed for either Normal or Double   *
 * Speed mode using the Bit1?U2X: in UCSRA Register.                         *
 ****************************************************************************/
typedef enum
{

	USART_Async_NormalSpeed  ,
	USART_Async_DoubleSpeed  ,
	USART_Sync        ,


}USART_enuCommunicationMode;


/****************************************************************************
 * Enumeration to configure USART as Transmitter, Receiver or Transceiver    *
 * by manipulating in RXEN and TXEN in UCSRB Register.                       *
 ****************************************************************************/
typedef enum
{

	USART_Disable ,
	USART_Tx_Only ,
	USART_Rx_Only ,
	USART_Tx_Rx   ,

}USART_enuEnableMode;


/****************************************************************************
 * Enumeration Covers all USART Interrupt possible.                          *
 ****************************************************************************/
typedef enum
{
	USART_InterruptDisable                    ,
	USART_RxCompletEnable                     ,
	USART_TxCompletEnable                     ,
	USART_UDR_EmptyEnable                     ,
	USART_RxComplet_TxComplet_Enable          ,
	USART_RxComplet_UDREmpty_Enable                ,
	USART_TxComplet_UDREmpty_Enable                ,
	USART_TxComplet_RxComplet_UDR_EmptyEnable ,

}USART_enuInterruptSource;



/****************************************************************************
 * USART Character Size possibilities per Frame.                             *
 *****************************************************************************/
typedef enum
{
	USART_5bitData              ,
	USART_6bitData              ,
	USART_7bitData              ,
	USART_8bitData              ,
	USART_9bitData              ,

}USART_enuDataFrame;


/*****************************************************************************
 * USART Frame Configurations possibilities.                                 *
 *****************************************************************************/
typedef enum
{
	USART_ParityDisable_1stopBit             ,
	USART_ParityDisable_2stopBit             ,
	USART_ParityEven_1stopBit                ,
	USART_ParityEven_2stopBit                ,
	USART_ParityOdd_1stopBit                 ,
	USART_ParityOdd_2stopBit                 ,

}USART_enuFrameControl;



/*****************************************************************************
 * USART Clock polarity Configurations possibilities.                        *
 *****************************************************************************/
typedef enum
{
	USART_SmapleOnFalling   ,
	USART_SmapleOnRasing    ,

}USART_enuClockPolarity;

typedef enum
{
	USART_No_Error             ,
	USART_Frame_Error          ,
	USART_Data_Over_Run_Error  ,
	USART_Parity_Error         ,
	USART_TX_Error             ,
	USART_Null_Pointer         ,

}USART_ES_t;

typedef struct
{

	USART_enuEnableMode                 EnableMode              ;
	USART_enuCommunicationMode          CommunicationMode       ;
	USART_enuCommunicationTerminal      CommunicationTerminal   ;
	USART_enuInterruptSource            InterruptSources        ;
	USART_enuDataFrame                  DataFrame               ;
	USART_enuFrameControl               FrameControl            ;

	// Assign This Option ONLY When working in Sync Mode.
	USART_enuClockPolarity              ClockPolarity           ;

	u16                                 BaudRate                ;

	//  *EXTI_ApfunINTFunc[3])(void*)
	//void*                               USART_

}USART_strCnfg;

extern USART_strCnfg USART0 ;

/****************************************************************************/
/****************************************************************************/
/* Function Name   : USART_enuInit.                                         */
/* Description     : Utility function to initialize USART Peripheral        */
/*                   according to the configuration structure.              */
/* Argument        : None.                                                  */
/* Return          : Error state of type ES_t.                              */
/**.....................*****************************************************/
void USART_enuInit(void);



/****************************************************************************/
/****************************************************************************/
/* Function Name   : USART_enuSendByte.                                     */
/* Description     : Polling technique based function To Send one Byte.     */
/* Argument        : The byte to be transmitted.                            */
/* Return          : Error state of type ES_t.                              */
/**.......................................***********************************/
USART_ES_t USART_enuSendByteSync( u16 const*const Copy_pu16Data  );


/****************************************************************************/
/****************************************************************************/
/* Function Name   : USART_enuRecieveByteSync.                              */
/* Description     : Polling technique based function To Receive one Byte.  */
/* Argument        : Address of u8 Variable to write the Received data in.  */
/* Return          : Error state of type ES_t.                              */
/**............................................******************************/
USART_ES_t USART_enuRecieveByteSync( u16*const Copy_pu16Data );

USART_ES_t USART_enuRecieveStringSync( u8*const Copy_pu8Data );

USART_ES_t USART_enuSendStringSync( u8 const* Copy_pu8Data );


USART_ES_t USART_enuRecieveByteASync(void (*Cpy_pFunc)(u8*) , u8* Cpy_pu8Para );

ES_t USART_enuSyncReceiveString(u8* Copy_pcData  );

#endif /* USART_INTERFACE_H_ */
