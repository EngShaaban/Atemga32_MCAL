/*
 * TIMER_interface.h
 *
 *  Created on: Oct 29, 2021
 *      Author: Shaban
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER0                   0
#define TIMER1                   1
#define TIMER2                   2




ES_t TIMER_enuInit(TIMER_t* Cpy_pstrtTimerCnfg );

ES_t TIMER_enuSetSyncDelay(u8 Copy_u8TimerID , u32 Copy_u32Time);

ES_t TIMER_enuSetAsyncDelay( u8 Copy_u8TimerID , u32 Copy_u32Time , void (*Copy_pAppFun)(void*) , void* Copy_pvidParameter );

ES_t TIMER_enuCTCMode( u8 Copy_u8TimerID , u32 Copy_u32Time );

ES_t TIMER_enuPWMPhaseCorrect( u8 Copy_u8TimerID , f32 Copy_f32Vrms );

ES_t TIMER_enuStop(u8 Copy_u8TimerID );




#endif /* TIMER_INTERFACE_H_ */
