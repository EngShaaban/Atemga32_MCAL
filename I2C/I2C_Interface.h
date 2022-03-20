/*****************************************************************************/
/* Title                 :   I2C_Interface                                   */
/* Filename              :   I2C_Interface.h                                 */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Dec 27, 2021                                    */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/**************************   FILE GUARDE  ***********************************/
#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

ES_t TWI_enuInitMaster(void);
ES_t TWI_enuSentByte(u8 Copy_u8Byte);
ES_t TWI_enuReadByte(u8 Copy_u8Byte);

#endif /* I2C_INTERFACE_H_ */
/***************************** END OF FILE. *********************************/
/****************************************************************************/
