/*
 * GIE_prog.c
 *
 *  Created on: Oct 13, 2021
 *      Author: Shaban
 */

#include "..\LIB\STD_TYPES.h"
#include "..\LIB\errorStates.h"

#include "GIE_priv.h"


ES_t GIE_enuEnable( void )
{
	ES_t Local_enuErrorState = ES_NOK ;

	SREG  |=(GIE_MASK_BIT<<I);


	return Local_enuErrorState ;
}
ES_t GIE_enuDisable( void )
{
	ES_t Local_enuErrorState = ES_NOK ;

	SREG  &=~(GIE_MASK_BIT<<I);



	return Local_enuErrorState ;
}
