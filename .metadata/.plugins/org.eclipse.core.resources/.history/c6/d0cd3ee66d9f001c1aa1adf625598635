/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   UART_Priv                                       */
/* Filename              :   UART_Priv.h                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Created on            :   Feb 27, 2022                                    */
/* Version               :   1.0.0                                           */
/* Toolchain             :   avr-gcc (4.3.3)                                 */
/* Target                :   ATmega32                                        */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/****************************   FILE GUARDE  *********************************/
#ifndef UART_PRIV_H_
#define UART_PRIV_H_

/*****************************************************************************/
/**************************** PRIVATE MACROS *********************************/
#define NORMAL           2U
#define DOUBLE           1U


#define ENABLE_MPCM      0
#define DISABLE_MPCM     1


#define TRANSMITTER      0
#define RECEIVER         1
#define TRANSCEIVER      2


#define CHAR_SIZE_5      0
#define CHAR_SIZE_6      1
#define CHAR_SIZE_7      2
#define CHAR_SIZE_8      3


/****************************************************************************/
/* UART REGISTERS DEFINITION.                                               */
/****************************************************************************/
#define   UDR           (*((volatile u8* const)0x2C))

#define   UCSRA         (*((volatile u8* const)0x2B))

#define   UCSRB         (*((volatile u8* const)0x2A))

//Hint: The UCSRC and UBRRH Registers share the same Address.
#define   UCSRC         (*((volatile u8* const)0x40))
#define   UBRRH         (*((volatile u8* const)0x40))

#define   UBRRL         (*((volatile u8* const)0x29))



// UCSRA Bits Definition.
#define   RXC                 7
#define   TXC                 6
#define   UDRE                5
#define   FE                  4
#define   DOR                 3
#define   PE                  2
#define   U2X                 1
#define   MPCM                0

// UCSRB Bits Definition.
#define   RXCIE               7
#define   TXCIE               6
#define   UDRIE               5
#define   RXEN                4
#define   TXEN                3
#define   UCSZ2               2
#define   RXB8                1
#define   TXB8                0


//UBRRH Bits Definition.
#define   URSEL              7


//UCSRC Bits Definition.
#define   URSEL              7
#define   UMSEL              6
#define   UPM1               5
#define   UPM0               4
#define   USBS               3
#define   UCSZ1              2
#define   UCSZ0              1
#define   UCPOL              0


#define UART_MSK_BIT         1



#define MY_UBRRL             ((F_CPU/(8*UART_SPEED_MODE)/BUAD_VAL-1)&0xFF)
#define MY_UBRRH             (((F_CPU/(8*UART_SPEED_MODE)/BUAD_VAL-1)>>8)&0x0F)


#define UART_TX_START()      UCSRB  |=(UART_MSK_BIT<<TXEN)
#define UART_TX_STOP()       UCSRB &=~(UART_MSK_BIT<<TXEN)

#define UART_RX_START()      UCSRB  |=(UART_MSK_BIT<<RXEN)
#define UART_RX_STOP()       UCSRB &=~(UART_MSK_BIT<<RXEN)


#endif /* UART_PRIV_H_ */
/***************************** END OF FILE. *********************************/
/****************************************************************************/

