/*
 * main.c
 *
 *  Created on: Feb 15, 2022
 *      Author: SHAABAN
 */


#include "STD_TYPES.h"
#include "errorStates.h"
#include "AVR_REG.h"

#include "E:\Data\EmbeddedSystem\Drivers\Atmega16\MCAL\interrupt.h"
#include "GIE_interface.h"

#include "DIO/DIO_interface.h"

#include "GIE_interface.h"

enum
{
	start ,
	Ton  ,
	Ttot ,
	Toff

}state = start ;

volatile u8 Timeon = 0 ;
volatile u8 Total = 0 ;

volatile u8 ovfCounter = 0 ;

// The number of ovf that occurs in high state.
volatile u8 ovfHigh  = 0 ;

// The number of ovf that occurs during the whole period.
volatile u8 ovfTot  = 0 ;



int main(void)
{
	//1. Set the INT0 Pin as output pin.
	DDRD &=~(1<<2);

	//2. Set the EXT0 To Detect the Raising Edge.
	MCUCR  = 0x03 ;

	//3. Enable Interrupt bit in EXTI0.
	GICR |=(1<<6);

	//4. Enable Global Interrupt Bit
	SREG |=(1<<7);

	//5.Config. Timer0 in OVF Mode and 1024 prescaler.
	TCCR0 = 0b00000101;

	//6.Enable Timer0 Interrupt Bit.
	TIMSK |=(1<<0);




	while(1)
	{
		if(state == Toff )
		{
			f32 duty = ((f32)Timeon+((f32)ovfHigh*256.0))/(Total + (ovfTot*256));

			f32 time = ((f32)ovfTot*256.0+ (f32)Total)* (1024.0/1000000);

			//f32 time = (f32)Total+ovfTot*256.0 * (8.0/1000000UL);
			f32 freq = 1.0 / time  ;
			(*((u8* const )0x31))= (u8)(duty*100) ;
			(*((u8* const )0x34))= freq ;

			//state == 22;

		}
	}

	return 0;
}

ISR( VECT_INT0 )
{
	if(state == start)
	{
		TCNT0  =  0  ;

		// Set the sense level to Raising .
		MCUCR  &=~(1<<0);
		MCUCR  |=(1<<1);

		state = Ton ;

	}
	else if (state == Ton )
	{
		Timeon= TCNT0 ;
		ovfHigh = ovfCounter ;


		// Set the sense level to Falling .
		MCUCR  |=(1<<0);
		MCUCR  |=(1<<1);

		state = Ttot ;

	}
	else if (state == Ttot )
		{
			Total = TCNT0 ;

			ovfTot = ovfCounter ;

			state = Toff ;

		}

}

ISR( VECT_TIMER0_OVF )
{
	ovfCounter++;
}














