/*
 * UART_Cnfg.h
 *
 *  Created on: Feb 27, 2022
 *      Author: SHAABAN
 */

#ifndef UART_CNFG_H_
#define UART_CNFG_H_


/****************************************************************************/
/***************************** PUBLIC MACROS ********************************/

/****************************************************************************/
/* MACOR NAME  :   UART_SPEED_MODE.                                         */
/* Description :   Macro to Configure the speed mode of the UART.           */
/* Options     :   NORMAL   or  DOUBLE .                                    */
/****************************************************************************/
#define UART_SPEED_MODE              DOUBLE


/****************************************************************************/
/* MACOR NAME  :   UART_MPC_MODE.                                           */
/* Description :   Macro to Configure  Multi-processor Communication Mode.  */
/* Options     :   ENABLE_MPCM  or DISABLE_MPCM  .                          */
/****************************************************************************/
#define UART_MPC_MODE                DISABLE_MPCM


/****************************************************************************/
/* MACOR NAME  :   UART_MODE.                                               */
/* Description :   Macro to Configure the UART Mode.                        */
/* Options     :   TRANSMITTER , RECEIVER or TRANSCEIVER                    */
/****************************************************************************/
#define UART_MODE                     TRANSCEIVER

/****************************************************************************/
/* MACOR NAME  :   UART_PURE_DATA_IN_FRAME.                                 */
/* Description :   Macro to Configure The number of pure Data per-frame.    */
/* Options     :   CHAR_SIZE_5       CHAR_SIZE_8                            */
/*                 CHAR_SIZE_6       CHAR_SIZE_7                            */
/*                                                                          */
/****************************************************************************/
#define UART_PURE_DATA_IN_FRAME        CHAR_SIZE_8


/****************************************************************************/
/* MACOR NAME  :   BAUD_RATE.                                               */
/* Description :   Macro to Configure the Baud Rater Value.                 */
/* Options     :                                                            */
/****************************************************************************/
#define BUAD_VAL                 9600




#endif /* UART_CNFG_H_ */

/***************************** END OF FILE. *********************************/
/****************************************************************************/

