/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   I2C_Prog                                      */
/* Filename              :   I2C_Prog.c                                     */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Dec 27, 2021                                     */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw GCC                                       */
/* Target                :   ATmega16 , ATmega32                             */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/

/****************************************************************************/
/******************************  INCLUDES  **********************************/
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "I2C_Private.h"
#include "I2C_Cnfg.h"


/*****************************************************************************/
/*****************************************************************************/
/* Return          : Error state of type ES_t.                               */
/**.............**************************************************************/
ES_t TWI_enuInitMaster(void)
{
	ES_t Local_enuErrorState = ES_NOK;

	// Enable I2C .


	/*********************************************************
	 * Prescaler Cases Handeling.                            *
	 *********************************************************/
#if I2C_PRESCALER == I2C_PRES_1

	SET_I2C_PRES_1;

	I2C_ENABLE ;

	Local_enuErrorState = ES_OK;

#elif      I2C_PRESCALER == I2C_PRES_4
	SET_I2C_PRES_4;

	I2C_ENABLE ;
	Local_enuErrorState = ES_OK;

#elif      I2C_PRESCALER == I2C_PRES_16
	SET_I2C_PRES_16 ;

	I2C_ENABLE ;
	Local_enuErrorState = ES_OK;

#elif      I2C_PRESCALER == I2C_PRES_32

	SET_I2C_PRES_32;

	I2C_ENABLE ;
	Local_enuErrorState = ES_OK;

#else
#error"THE SELECTED I2C PRESCALER IS WRONG!."
#endif


	return Local_enuErrorState ;
}//End of ().




/*****************************************************************************/
/*****************************************************************************/
/* Return          : Error state of type ES_t.                               */
/**.............**************************************************************/
ES_t TWI_enuSentByte(u8 Copy_u8Byte)
{
	ES_t Local_enuErrorState = ES_NOK;

	return Local_enuErrorState ;
}//End of ().



/*****************************************************************************/
/*****************************************************************************/
/* Return          : Error state of type ES_t.                               */
/**.............**************************************************************/
ES_t TWI_enuReadByte(u8 Copy_u8Byte)
{
	ES_t Local_enuErrorState = ES_NOK;

	return Local_enuErrorState ;
}//End of ().





/***************************** END OF FILE. *********************************/
/****************************************************************************/
