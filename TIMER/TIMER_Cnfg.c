/*
 * TIMER_Cnfg.c
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */
#include "LIB\STD_TYPES.h"
#include "LIB\errorStates.h"

#include "TIMER_Priv.h"
#include "TIMER_Cnfg.h"

TIMER_t TIMRE_AstrCnfg[MAX_NUM_OF_TIMER]=
{
		{
				/* Timer0 configurations. */
				.TIMER_u8STATE        = on                     ,
				.TIMER_u8Mode         = PWM_PHASE_CORRECT                     ,  //init. func.
				.TIMER_u8OC0_State    = DISCONNECTED   ,        // init .
				.TIMER_u16Prescaler   = PRES_64              ,  // Start.
				.TIMER_u16Freq_in_khz = (1000UL)                 ,   // Start

		}
		,
		{
				/* Timer1 configurations. */
				.TIMER_u8STATE          = off              ,
				.TIMER_u8Mode         = OVF                 ,  //init. func.
				.TIMER_u8OC0_State    = DISCONNECTED     ,  // init .
				.TIMER_u16Prescaler   = PRES_1024        ,  // Start.
	 			.TIMER_u16Freq_in_khz = 1000UL          ,   // Start

		}
		,
		{
				/* Timer2 configurations. */
				.TIMER_u8STATE        = off           ,
				.TIMER_u8Mode         = OVF                 ,  //init. func.
				.TIMER_u8OC0_State    = DISCONNECTED  ,  // init .
				.TIMER_u16Prescaler   = PRES_1024      ,   // Start
				.TIMER_u16Freq_in_khz = 1000UL          ,

		}


};
