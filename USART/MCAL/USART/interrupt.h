/*
 * interrupt.h
 *
 *  Created on: Oct 10, 2021
 *      Author: Shaban
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#define ISR(VECT_NUM)    void VECT_NUM(void) __attribute__ ((signal));\
	                     void VECT_NUM(void)


#define VECT_INT0              __vector_1
#define VECT_INT1              __vector_2
#define VECT_INT2              __vector_3
#define VECT_TIMER2_CTC        __vector_4
#define VECT_TIMER2_OVF        __vector_5
#define VECT_TIMER1_CAPT       __vector_6
#define VECT_TIMER1_COMPA      __vector_7
#define VECT_TIMER1_COMPB      __vector_8
#define VECT_TIMER1_OVF        __vector_9
#define VECT_TIMER0_COMP       __vector_10
#define VECT_TIMER0_OVF        __vector_11
#define VECT_USART_RXC         __vector_13
#define VECT_USART_UDRE        __vector_14
#define VECT_USART_TXC         __vector_15


#define VECT_ADC               __vector_16



#endif /* INTERRUPT_H_ */
