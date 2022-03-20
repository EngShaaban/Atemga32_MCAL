/*****************************************************************************/
/*****************************************************************************/
/* Title                 :   TIMER_Prog                                      */
/* Filename              :   TIMER_Prog.c                                    */
/* Author                :   Shaban Abdullah Awad                            */
/* Origin Date           :   Oct 29, 2021                                    */
/* Version               :   1.0.0                                           */
/* Compiler              :   mingw_GCC                                       */
/* Target                :   ATmega32                                        */
/* Notes                 :   None                                            */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*******************************  INCLUDES  **********************************/


#include"LIB\errorStates.h"
#include"LIB\STD_TYPES.h"


#include "E:\Data\EmbeddedSystem\Drivers\Atmega16\MCAL\interrupt.h"

#include "TIMER_Priv.h"
#include "TIMER_Cnfg.h"



/*****************************************************************************************/
/* Description   : Tow global array of pointers to store the Timers Addresses.           */
/*****************************************************************************************/
static TIMER_t* TIMER_ApenuTIMER[MAX_NUM_OF_TIMER]={ NULL , NULL , NULL };


static volatile u32 Timer_u32ArrOfTimersOVF[MAX_NUM_OF_TIMER]={  0  ,  0  ,  0  };

static volatile u32 Timer_u32ArrOfTimersPreload[MAX_NUM_OF_TIMER]={  0  ,  0  ,  0  };


static void (*TIMER_pvidAppFunc[MAX_NUM_OF_TIMER])(void*)={ NULL , NULL , NULL };
static void* TIMER_pvidAppPara[MAX_NUM_OF_TIMER]={ NULL , NULL , NULL };

static volatile  u8  TTIMER_u8CalculatedCopVal = 0 ;

static volatile  u8 TTIMER_u8CopyOfCalculatedCopValCopy = 0 ;



ES_t TIMER_enuInit(TIMER_t* Cpy_pstrtTimerCnfg )
{
	ES_t Local_enuErrorState = ES_NOK;

	if( Cpy_pstrtTimerCnfg != NULL )
	{

		TIMER_ApenuTIMER[TIMER0]=&(Cpy_pstrtTimerCnfg[TIMER0]);
		TIMER_ApenuTIMER[TIMER1]=&(Cpy_pstrtTimerCnfg[TIMER1]);
		TIMER_ApenuTIMER[TIMER2]=&(Cpy_pstrtTimerCnfg[TIMER2]);

		u8 Local_u8Iterator = 0  ;

		for( Local_u8Iterator = 0 ; Local_u8Iterator < MAX_NUM_OF_TIMER ; Local_u8Iterator++)
		{
			if( TIMER_ApenuTIMER[Local_u8Iterator]->TIMER_u8STATE == on )
			{

				TIMER_vidStaticInline_SetTimerMode( Local_u8Iterator );


			}
			else
			{
				//Do nothing.
			}


		}// End of for.


	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}

	return Local_enuErrorState ;
}//End of TIMER_enuInit.



ES_t TIMER_enuSyncDelay(u8 Copy_u8TimerID , u32 Copy_u32Time)
{
	ES_t  Local_enuErrorState = ES_NOK ;

	if(Copy_u8TimerID < MAX_NUM_OF_TIMER )
	{

		switch( Copy_u8TimerID )
		{

		case TIMER0 :

			switch( TIMER_ApenuTIMER[TIMER0]->TIMER_u8Mode )
			{
			case OVF :

				TIMER_vidStaticInline_SetPreload(TIMER0,Copy_u32Time );

				TCNT0  = Timer_u32ArrOfTimersPreload[TIMER0] ;

				TIMER_vidStaticInline_SetPrescaler( TIMER0 );


				while( Timer_u32ArrOfTimersOVF[ TIMER0 ] >  0 )
				{
					while( ( (TIFR>>TOV0)&1 ) == 0  );

					TIFR |=(TIMER_MSK_BIT<<TOV0);

					Timer_u32ArrOfTimersOVF[ TIMER0 ]-- ;
				}

				break;

			case CTC:



				TIMER_vidStaticInline_SetCompareMatchVal( TIMER0 ,  Copy_u32Time );

				break;

			}

			break;// TIMER0 Case .


			case TIMER2 :

				TIMER_vidStaticInline_SetPreload( TIMER2 ,  Copy_u32Time );

				TCNT2  =  Timer_u32ArrOfTimersPreload[TIMER2] ;

				TIMER_vidStaticInline_SetPrescaler( TIMER2 );

				while( Timer_u32ArrOfTimersOVF[ TIMER2 ] > 0 )
				{

					while( ((TIFR>>TOV2)&1) == 0 ) ;

					TIFR |=(TIMER_MSK_BIT<<TOV2);

					Timer_u32ArrOfTimersOVF[ TIMER2 ]-- ;

				}




				break;

		}


	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}


	return Local_enuErrorState ;
}


ES_t TIMER_enuSetAsyncDelay( u8 Copy_u8TimerID , u32 Copy_u32Time , void (*Copy_pAppFun)(void*) , void* Copy_pvidParameter )
{
	ES_t    Local_enuErrorState = ES_NOK  ;

	if( Copy_u8TimerID < MAX_NUM_OF_TIMER  )
	{
		if( Copy_pAppFun != NULL )
		{

			switch(  Copy_u8TimerID  )
			{
			case TIMER0 :
				TIMER_pvidAppFunc[TIMER0] = Copy_pAppFun  ;
				TIMER_pvidAppPara[TIMER0] = Copy_pvidParameter ;

				{
					switch (TIMER_ApenuTIMER[TIMER0]->TIMER_u8Mode)
					{
					case OVF :
					{
						TIMSK |= (TIMER_MSK_BIT<<TOIE0);

						TIMER_vidStaticInline_SetPreload( TIMER0 ,  Copy_u32Time );

						TIMER_vidStaticInline_SetPrescaler( TIMER0 );
					}
					break;



					case CTC :
					{

						TIMSK |= (TIMER_MSK_BIT<<OCIE0);

						TIMER_vidStaticInline_SetCompareMatchVal( TIMER0 ,  Copy_u32Time );

						TIMER_vidStaticInline_SetPrescaler( TIMER0 );
					}
					break;

					}


				}
				break ;

			case TIMER1 :
				TIMER_pvidAppFunc[TIMER1] = Copy_pAppFun  ;
				TIMER_pvidAppPara[TIMER1] = Copy_pvidParameter ;


				TIMSK |= (TIMER_MSK_BIT<<TOIE1);

				TIMER_vidStaticInline_SetPreload( TIMER1 ,  Copy_u32Time );

				TIMER_vidStaticInline_SetPrescaler( TIMER1 );

				break ;
			case TIMER2 :
				TIMER_pvidAppFunc[TIMER2] = Copy_pAppFun  ;
				TIMER_pvidAppPara[TIMER2] = Copy_pvidParameter ;


				TIMSK |= (TIMER_MSK_BIT<<TOIE2);

				TIMER_vidStaticInline_SetPreload( TIMER2 ,  Copy_u32Time );

				TIMER_vidStaticInline_SetPrescaler( TIMER2 );

				break ;
			}

		}
		else
		{
			Local_enuErrorState = ES_NULL_POINTER ;
		}
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE  ;
	}



	return Local_enuErrorState ;
}// End of TIMER_enuAsyncDelay().


ES_t TIMER_enuCTCMode( u8 Copy_u8TimerID , u32 Copy_u32Time )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Copy_u8TimerID < MAX_NUM_OF_TIMER )
	{

		if( TIMER_ApenuTIMER[Copy_u8TimerID]->TIMER_u8Mode == CTC )
		{
			switch( Copy_u8TimerID )
			{

			case TIMER0 :

				//TIMER_vidStaticInline_SetMatchVal(Copy_u8TimerID ,  Copy_u32Time );
				TIMER_vidStaticInline_SetPrescaler( TIMER0 );
				break;

			case TIMER1 :
				break;

			case TIMER2 :
				break;

			}
		}
		else
		{
			//Nothing to Do.
		}

	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}


	return Local_enuErrorState ;
}// End of TIMER_enuCTCMode().

ES_t TIMER_enuStop(u8 Copy_u8TimerID )
{
	ES_t Local_enuErrorState = ES_NOK ;

	if( Copy_u8TimerID < MAX_NUM_OF_TIMER )
	{
		switch(Copy_u8TimerID )
		{

		case  TIMER0  :

			if( TIMER_ApenuTIMER[TIMER0]->TIMER_u8STATE == on)
			{
				TCCR0 &=~( (TIMER_MSK_BIT<< CS02)|(TIMER_MSK_BIT<< CS01)| (TIMER_MSK_BIT<< CS00));
			}
			else
			{
				//D0 N0thing.
			}

			break ;


		case  TIMER1  :

			if(TIMER_ApenuTIMER[TIMER1]->TIMER_u8STATE == on)
			{
				TCCR1B &=~( (TIMER_MSK_BIT<< CS12)|(TIMER_MSK_BIT<< CS11)| (TIMER_MSK_BIT<< CS10));
			}
			else
			{
				//D0 N0thing.
			}

			break ;

		case  TIMER2  :

			if(TIMER_ApenuTIMER[TIMER2]->TIMER_u8STATE == on)
			{
				TCCR2 &=~( (TIMER_MSK_BIT<< CS22)|(TIMER_MSK_BIT<< CS21)| (TIMER_MSK_BIT<< CS20));
			}
			else
			{
				//D0 N0thing.
			}
			break ;

		}

	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}

	return Local_enuErrorState ;

}//End of TIMER_enuStop().



ES_t TIMER_enuPWMPhaseCorrect( u8 Copy_u8TimerID , f32 Copy_f32Vrms )
{
	ES_t Local_enuErrorState = ES_NOK  ;

	if( Copy_u8TimerID < MAX_NUM_OF_TIMER )
	{

		switch( Copy_u8TimerID )
		{

		case TIMER0 :
		{
			f32 Local_f32DutyCycleVal = (( Copy_f32Vrms / 5.0  )*( Copy_f32Vrms / 5.0 )) ;

			f32 Local_f32OCR_Val = 255.0 * Local_f32DutyCycleVal ;

			if ( (Local_f32OCR_Val)-((u32)(Local_f32OCR_Val)) > 0.80)
			{
				Local_f32OCR_Val++;
			}
			else
			{

			}

			OCR0 = Local_f32OCR_Val ;



			TIMER_vidStaticInline_SetCompareMatchVal( TIMER0 , 0 );

			TIMER_vidStaticInline_SetPrescaler( TIMER0 );

			TIMER_vidStaticInline_SetPrescalerInPhaseCorrectMode( TIMER0 );

		}break; // Timer0 .

		case TIMER1 :
		{

		}break; // Timer1 .
		case TIMER2 :
		{

		}break; // Timer2 .

		}//End of Switch.


		Local_enuErrorState = ES_OK ;
	}
	else
	{
		Local_enuErrorState = ES_OUT_OF_RANGE ;
	}

	return Local_enuErrorState ;
}// End of TIMER_enuPWMPhaseCorrect.


/**************************************************************************************************/
/***************************************** PRIVATE FUNCTIONS DEFINITIONS **************************/

void static inline TIMER_vidStaticInline_SetTimerMode( u8 Copy_u8TimerID )
{


	if(  Copy_u8TimerID == TIMER0 )
	{
		switch( TIMER_ApenuTIMER[TIMER0]->TIMER_u8Mode )
		{

		TCCR0 &=~( (TIMER_MSK_BIT<<WGM00) | (TIMER_MSK_BIT<<WGM01) );
		case OVF  :
			//Already Done.
			break;

		case PWM_PHASE_CORRECT  :
			TCCR0 |=(TIMER_MSK_BIT<<WGM00) ;
			break;

		case CTC :
		{
			TCCR0 |=(TIMER_MSK_BIT<<WGM01) ;

			TIMER_vidStaticInline_SetOC0State(TIMER0);
		}


		break;



		}

	}
	else if (Copy_u8TimerID == TIMER1)
	{

	}
	else if( Copy_u8TimerID == TIMER2)
	{

		switch( TIMER_ApenuTIMER[TIMER2]->TIMER_u8Mode )
		{

		TCCR2 &=~( (TIMER_MSK_BIT<<WGM21) | (TIMER_MSK_BIT<<WGM20) );
		case OVF  :
			break;

		case PWM_PHASE_CORRECT  :

			TCCR2 |= (TIMER_MSK_BIT<<WGM20);
			break;


		}

	}
	else
	{
		// Do nothing.
	}

}// End of TIMER_vidStaticInline_TimerMode().




void static inline TIMER_vidStaticInline_SetPrescaler( u8 Copy_u8TimerID )
{
	if( Copy_u8TimerID == TIMER0 )
	{

		TCCR0 &=~( (TIMER_MSK_BIT<<CS02) | (TIMER_MSK_BIT<<CS01) | (TIMER_MSK_BIT<<CS00) );

		if(TIMER_ApenuTIMER[TIMER0]->TIMER_u8STATE == on)
		{
			switch( TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler )
			{

			case PRES_1024 :
				TCCR0 |= ( (TIMER_MSK_BIT<<CS02) | (TIMER_MSK_BIT<<CS00) );

				break ;

				//Do Nothing.

			}//End of switch.

		}
		else
		{
			// You will be here Only if Timer0 State is off .
		}

	}
	else if(Copy_u8TimerID == TIMER2)
	{

		TCCR2 &=~( (TIMER_MSK_BIT<<CS22) | (TIMER_MSK_BIT<<CS21) | (TIMER_MSK_BIT<<CS20) );

		if(TIMER_ApenuTIMER[TIMER2]->TIMER_u8STATE == on)
		{
			switch( TIMER_ApenuTIMER[TIMER2]->TIMER_u16Prescaler )
			{

			case PRES_1 :
				TCCR2 |=  (TIMER_MSK_BIT<<CS20) ;
				break;

			case PRES_1024 :

				TCCR2 |= ( (TIMER_MSK_BIT<<CS22) | (TIMER_MSK_BIT<<CS21) | (TIMER_MSK_BIT<<CS20) );

				break ;

				//Do Nothing.

			}//End of switch.

		}
		else
		{
			// You will be here Only if Timer0 State is off .
		}

	}
	else
	{

	}

}//End of void static inline TIMER_vidStaticInline_Prescaler().

void static inline TIMER_vidStaticInline_SetOC0State( u8 Copy_u8TimerID )
{
	if( Copy_u8TimerID == TIMER0 )
	{
		switch( TIMER_ApenuTIMER[TIMER0]->TIMER_u8OC0_State )
		{

		TCCR0 &=~( (TIMER_MSK_BIT<<COM01)|(TIMER_MSK_BIT<<COM00));

		case DISCONNECTED :
			//Already Done.
			break;

		case TOGGLE_ON_COMP_MATCH :

			TCCR0 |= (TIMER_MSK_BIT<< COM00);

			break;

		case CLEAR_ON_COMP_MATCH  :

			TCCR0 |= (TIMER_MSK_BIT<< COM01);

			break;

		case SET_ON_COMP_MATCH   :

			TCCR0 |= ((TIMER_MSK_BIT<<COM01)|(TIMER_MSK_BIT<<COM00));

			break;



		}
	}
	else if (Copy_u8TimerID == TIMER1)
	{

	}
	else if(Copy_u8TimerID == TIMER2)
	{
		switch( TIMER_ApenuTIMER[TIMER2]->TIMER_u8OC0_State )
		{

		TCCR2 &=~( (TIMER_MSK_BIT<<COM21)|(TIMER_MSK_BIT<<COM20));

		case DISCONNECTED :
			//Already Done.
			break;

		case TOGGLE_ON_COMP_MATCH :
			TCCR2  |= ((TIMER_MSK_BIT<<COM21)|(TIMER_MSK_BIT<<COM20) );
			break;



		}

	}
	else
	{

	}

}// End of TIMER_vidStaticInline_OC0State().




void static inline TIMER_vidStaticInline_SetPreload( u8 Copy_u8TimerID , u32 Copy_u32Time)
{
	if(Copy_u8TimerID == TIMER0  )
	{
		f32  Local_f32OVFTime     = 256* ( (f32)(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler) / (TIMER_ApenuTIMER[TIMER0]->TIMER_u16Freq_in_khz));

		f32  Local_f32NumOfOVFs   = (f32)Copy_u32Time/Local_f32OVFTime ;


		if( (Local_f32NumOfOVFs)-(u32)(Local_f32NumOfOVFs) != 0.0 )
		{
			u32 Local_u32IntNumOfOVFs = (u32)(Local_f32NumOfOVFs) +1 ;

			Timer_u32ArrOfTimersOVF[TIMER0]= (u32)Local_u32IntNumOfOVFs ;

			u32 Local_u32Preload = 256 - (256*((Local_f32NumOfOVFs)-(u32)(Local_f32NumOfOVFs) ));

			Timer_u32ArrOfTimersPreload[TIMER0] = Local_u32Preload ;

		}
		else
		{

			Timer_u32ArrOfTimersOVF[TIMER0]     =    (u32) Local_f32NumOfOVFs;

			Timer_u32ArrOfTimersPreload[TIMER0] =    0 ;

		}

	}

	else if(Copy_u8TimerID == TIMER2)
	{

		f32 Local_f32OVFTime    = 256*( (f32)(TIMER_ApenuTIMER[TIMER2]->TIMER_u16Prescaler)/(TIMER_ApenuTIMER[TIMER2]->TIMER_u16Freq_in_khz) );

		f32 Local_f32NumOfOVFs  = (f32)Copy_u32Time / Local_f32OVFTime ;



		if( (Local_f32NumOfOVFs)-(u32)(Local_f32NumOfOVFs) != 0.0 )
		{
			u32 Local_u32IntNumOfOVF         =  (u32)Local_f32NumOfOVFs + 1 ;

			Timer_u32ArrOfTimersOVF[TIMER2]  =  Local_u32IntNumOfOVF ;

			u32 Local_u32Preload             =  256 - (256 * ((Local_f32NumOfOVFs)-(u32)(Local_f32NumOfOVFs) ));

			Timer_u32ArrOfTimersPreload[TIMER2] = Local_u32Preload ;

		}
		else
		{
			Timer_u32ArrOfTimersOVF[TIMER2]  =  (u32)Local_f32NumOfOVFs ;

			Timer_u32ArrOfTimersPreload[TIMER2] =    0 ;


		}
	}
	else
	{

	}

}//End of TIMER_vidStaticInline_Preload().


void static inline TIMER_vidStaticInline_SetCompareMatchVal( u8 Copy_u8TimerID , u32 Copy_u32Time )
{

	switch(  Copy_u8TimerID )
	{

	case TIMER0 :
	{
		switch( TIMER_ApenuTIMER[TIMER0]->TIMER_u8Mode)
		{

		case CTC :
		{
			f32 Local_f32TimeOfOneTick =  (f32)(TIMER_ApenuTIMER[TIMER0]->TIMER_u16Prescaler) / TIMER_ApenuTIMER[TIMER0]->TIMER_u16Freq_in_khz ;

			f32 Local_f32CompVal       = (f32)Copy_u32Time /Local_f32TimeOfOneTick ;

			u8 Local_u8Counter = 0  ;

			while(  Local_f32CompVal > 255.0 )
			{
				Local_u8Counter++;

				Local_f32CompVal =  (f32)Copy_u32Time /Local_u8Counter * Local_f32TimeOfOneTick ;
			}

			OCR0   = (u8)Local_f32CompVal ;

			TTIMER_u8CalculatedCopVal = Local_u8Counter - 1  ;

			TTIMER_u8CopyOfCalculatedCopValCopy = Local_u8Counter - 1 ;

		}break; // End of CTC mode.

		case PWM_PHASE_CORRECT :
		{
			TCCR0 &=~( TIMER_MSK_BIT<<COM00);

			TCCR0 |=( TIMER_MSK_BIT<<COM01);


		}break;

		}// End of mode switch .



	}//End of TIMER0.
	break;


	case TIMER1 :
	{

	}//End of TIMER1.
	break;


	case TIMER2 :
	{

	}//End of TIMER2.
	break;


	}//End of Switch.


}//End of TIMER_vidStaticInline_CompareMatchVal.


void static inline TIMER_vidStaticInline_SetPrescalerInPhaseCorrectMode( u8 Copy_u8TimerID )
{
	switch( Copy_u8TimerID )
	{

	case TIMER0 :
	{
		TCCR0 &=~(TIMER_MSK_BIT<<CS02);
		TCCR0 |=((TIMER_MSK_BIT<<CS01)|(TIMER_MSK_BIT<<CS00));

	}break ; //End of case TIMER0 .


	}
}



ISR(VECT_TIMER0_OVF)
{
	static u32 Local_u32Counter = 0 ;

	Local_u32Counter++ ;


	if(Local_u32Counter == Timer_u32ArrOfTimersOVF[TIMER0])
	{
		TCNT0 = Timer_u32ArrOfTimersPreload[TIMER0];

		Local_u32Counter = 0 ;

		(*TIMER_pvidAppFunc[TIMER0])(TIMER_pvidAppPara[TIMER0]);
	}


}


ISR(VECT_TIMER1_OVF)
{
	static u32 Local_u32Counter  = 0 ;

	Local_u32Counter++ ;

	if( Local_u32Counter == Timer_u32ArrOfTimersOVF[TIMER1] )
	{
		TCNT2 = Timer_u32ArrOfTimersPreload[TIMER1];

		Local_u32Counter  = 0 ;

		(*TIMER_pvidAppFunc[TIMER1])(TIMER_pvidAppPara[TIMER1]);
	}

}

ISR(VECT_TIMER2_OVF)
{
	static u32 Local_u32Counter  = 0 ;

	Local_u32Counter++ ;

}

ISR(VECT_TIMER0_COMP)
{
	if ( TTIMER_u8CalculatedCopVal != 0)
	{
		TTIMER_u8CalculatedCopVal-- ;
	}
	else
	{

		TTIMER_u8CalculatedCopVal = TTIMER_u8CopyOfCalculatedCopValCopy ;

		(*TIMER_pvidAppFunc[TIMER0])( TIMER_pvidAppPara[TIMER0] );
	}

}







