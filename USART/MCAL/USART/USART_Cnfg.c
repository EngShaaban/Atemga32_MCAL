/*
 * USART_Cnfg.c
 *
 *  Created on: Mar 11, 2022
 *      Author: SHAABAN
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/errorStates.h"

#include "USART_Interface.h"

USART_strCnfg USART0=
{
        .EnableMode             =  USART_Tx_Rx                     ,
        .CommunicationMode      =  USART_Async_DoubleSpeed         ,
        .CommunicationTerminal  =  USART_SingleProcessor           ,
        .InterruptSources       =  USART_RxCompletEnable           ,
        .DataFrame              =  USART_8bitData                  ,
        .FrameControl           =  USART_ParityDisable_1stopBit    ,
		.ClockPolarity          =  USART_SmapleOnFalling           ,
 		.BaudRate               =  9600ul                          ,


};

