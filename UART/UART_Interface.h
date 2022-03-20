/*
 * UART_Interface.h
 *
 *  Created on: Feb 27, 2022
 *      Author: SHAABAN
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

/****************************************************************************/
/****************************************************************************/
/* Function Name   : UART_enuInit.                                          */
/* Description     : Utility function to initialize the Enabled interrupts. */
/* Argument        : Address array of interrupts .                          */
/* Return          : Error state of type ES_t.                              */
/**............................................******************************/
ES_t UART_enuInit( void );

ES_t UART_enuSendByte( u8   Copy_u8Data  );

ES_t UART_enuRecieveByte( u8*  Copy_pu8Data );

ES_t UART_enuSendString( u8*  Copy_pcData  );

ES_t UART_enuReceiveString(u8* Copy_pcData  );

#endif /* UART_INTERFACE_H_ */
