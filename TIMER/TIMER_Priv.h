/*
 * TIMER_Priv.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */

#ifndef TIMER_PRIV_H_
#define TIMER_PRIV_H_

typedef enum
{
	off      ,
	on       ,

}STATE_t;



//*******************************************************************************/
/* TIMER Registers Definitions.                                                    */
/*******************************************************************************/
#define TCCR0   (*((volatile u8* const)0x53))
#define TCNT0   (*((volatile u8* const)0x52))
#define OCR0    (*((volatile u8* const)0x5C))

#define TCCR1B  (*((volatile u8* const)0x4E))

#define TCCR2   (*((volatile u8* const)0x45))
#define TCNT2   (*((volatile u8* const)0x44))

#define TIMSK   (*((volatile u8* const)0x59))
#define TIFR    (*((volatile u8* const)0x58))





// Define TCCR0 Bits
#define    FOC0                 7
#define    WGM00                6
#define    COM01                5
#define    COM00                4
#define    WGM01                3
#define    CS02                 2
#define    CS01                 1
#define    CS00                 0

// Define TIMSK Bits
#define    TOIE0                0
#define    OCIE0                1

#define    TOIE1                2

#define    TOIE2                6
#define    OCIE2                7

// Define TCCR1B Bits
#define     ICNC1              7
#define     ICES1              6
#define     WGM13              4
#define     WGM12              3
#define     CS12               2
#define     CS11               1
#define     CS10               0


// Define TCCR2 Bits
#define    FOC2                 7
#define    WGM20                6
#define    COM21                5
#define    COM20                4
#define    WGM21                3
#define    CS22                 2
#define    CS21                 1
#define    CS20                 0

// Define TIFR Register Bits.
#define    TOV0                 0
#define    OCF0                 1
#define    TOV1                 2
#define    TOV2                 6


/*******************************************************************************/
/********************************* PRIVATE MACROS ******************************/
// TIMER MODES.
#define    OVF                   (0U)
#define    PWM_PHASE_CORRECT     (1U)
#define    CTC                   (2U)
#define    FAST_PWM              (3U)

// TIMER PRESCALER
#define    PRES_NONE             (0)
#define    PRES_1                (1)
#define    PRES_8                (8)
#define    PRES_64               (64)
#define    PRES_256              (256UL)
#define    PRES_1024             (1024UL)



#define DISCONNECTED             0
#define TOGGLE_ON_COMP_MATCH     1
#define CLEAR_ON_COMP_MATCH      2
#define SET_ON_COMP_MATCH        3


#define TIMER0                   0
#define TIMER1                   1
#define TIMER2                   2



#define TIMER_MSK_BIT            1

#define MAX_NUM_OF_TIMER             3

/**********************************************************************/
/***************************** PRIVATE FUNCTION ******************/

void static inline TIMER_vidStaticInline_SetTimerMode( u8 Copy_u8TimerID );

void static inline TIMER_vidStaticInline_SetOC0State( u8 Copy_u8TimerID );

void static inline TIMER_vidStaticInline_SetPrescaler( u8 Copy_u8TimerID );

void static inline TIMER_vidStaticInline_SetPreload( u8 Copy_u8TimerID , u32 Copy_u32Time);

void static inline TIMER_vidStaticInline_SetCompareMatchVal( u8 Copy_u8TimerID , u32 Copy_u32Time );

void static inline TIMER_vidStaticInline_SetPrescalerInPhaseCorrectMode( u8 Copy_u8TimerID );


#endif /* TIMER_PRIV_H_ */
