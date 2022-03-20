/********************** main.c *************************/

#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\STD_TYPES.h"
#include "E:\NTI\AVR\ATmeg16_Drivers\LIB\errorStates.h"

#include "MCAL/DIO_interface.h"

#include "EXTI_Cnfg.h"
#include "EXTI_interface.h"

void tog(void)
{
	DIO_enuToggelPin( DIO_PORTA, DIO_PIN0 );
}

int main(void)
{
	DIO_enuSetPinDirection( DIO_PORTA , DIO_PIN0 , DIO_OUTPUT_PIN );
	DIO_enuSetPinValue( DIO_PORTA , DIO_PIN0 , DIO_HIGH );


	DIO_enuSetPinDirection( DIO_PORTD, DIO_PIN2 , DIO_INPTU_PIN );

	EXTI_enuInit( EXTI_AstrCnfg );

	EXTI_enuCallBack( tog , NULL , EXTI_0 );

	while(1)
	{
	}

}// End of main.
