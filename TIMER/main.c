/*
 * main.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */
#include "LIB\STD_TYPES.h"
#include "LIB\errorStates.h"

#include "GIE\GIE_interface.h"

#include "DIO\DIO_interface.h"

#include "TIMER_Cnfg.h"
#include "TIMER_interface.h"





int main(void)
{

	//1. Set the OC0 pin as output pin.
	DIO_enuSetPinDirection(DIO_PORTB , DIO_PIN3 , DIO_OUTPUT_PIN );

	//2. Initialize the Timer;
	TIMER_enuInit(TIMRE_AstrCnfg);

	//3. Use timer0 to Generate PWM With Vrms= 2.5 Volt.
	TIMER_enuPWMPhaseCorrect(TIMER0 , 0.5);




	while(1)
	{

	}
}



