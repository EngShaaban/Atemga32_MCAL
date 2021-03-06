/*
 * main.c
 *
 *  Created on: Feb 27, 2022
 *      Author: SHAABAN
 */

#include "LIB/STD_TYPES.h"
#include "LIB/errorStates.h"

#include "DIO_interface.h"
#include "UART_Interface.h"

#ifndef F_CPU
#define F_CPU    (1000000UL)
#endif


typedef union
{
	u8   GPGGA_LINE_FLAG:      1 ;
	u8   LAT_COMMA_FLAG :      1 ;
	u8   LONG_COMMA_FLAG:      1 ;
	u8   FIRST_DIR_FLAG :      1 ;
	u8   SECOND_DIR_FLAG:      1 ;
	u8   DOT_FLAG       :      1 ;

}GPS_FLAGS_t;



typedef struct
{
	u16  GPS_u16Lat ;

	u16  GPS_u16Long;

}GPS_t;

GPS_t GPS_stuLocation;

GPS_FLAGS_t    GPS_stuFlag ;


void gps_start(void);


//private gps var's.

u8 static GPS_u8stLinePattern[6]={'$','G','P','G','G','A' };
u8 static u8ReceivedChar=0;

int main(void)
{


	//will add to gps init function.
	GPS_stuFlag.GPGGA_LINE_FLAG = 0 ;
	GPS_stuFlag.LAT_COMMA_FLAG = 0 ;
	GPS_stuFlag.DOT_FLAG      = 0 ;



	//Configure the TXD(PD1) pin as output pin
	DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN1 , DIO_OUTPUT_PIN);

	//Configure the RXD(PD0) pin as INPUT pin
	DIO_enuSetPinDirection(DIO_PORTD , DIO_PIN0 , DIO_INPTU_PIN);

	UART_enuInit();

	while(1)
	{


		gps_start();


		if(GPS_stuFlag.LAT_COMMA_FLAG)
		{

			//UART_enuRecieveByte( &Local_u8RxData);

			gps_start();

			GPS_stuLocation.GPS_u16Lat = 'L';
			UART_enuSendByte(GPS_stuLocation.GPS_u16Lat);

		}
		else if(GPS_stuFlag.LONG_COMMA_FLAG)
		{
			gps_start();

			GPS_stuLocation.GPS_u16Lat = 'G';
			UART_enuSendByte(GPS_stuLocation.GPS_u16Lat);


		}
		else
		{

		}





	}

	return 0 ;

}// End of main().



void gps_start(void)
{
	u8 static Local_u8TempChar = 0 ;

	u8 static Local_u8CharCounter = 0 ;

	u8 static Local_u8CommaCounter = 0 ;




	UART_enuRecieveByte( &u8ReceivedChar);

	if( ( u8ReceivedChar == GPS_u8stLinePattern[Local_u8CharCounter]) )
	{
		Local_u8CharCounter++;

		if(Local_u8CharCounter == 6  )
		{
			GPS_stuFlag.GPGGA_LINE_FLAG = 1 ;

			Local_u8CharCounter = 0 ;
		}
		else
		{

		}
	}
	//$GPGGA,141848.00, 2237.63306,N,08820.86316,E,1,03,2.56,1.9,M,-54.2, M,,*74
	else if( GPS_stuFlag.GPGGA_LINE_FLAG  )
	{
		if( u8ReceivedChar == ',' )
		{
			Local_u8CommaCounter++;

			if(Local_u8CommaCounter == 1 )
			{
				GPS_stuFlag.GPGGA_LINE_FLAG = 0 ;
				GPS_stuFlag.LAT_COMMA_FLAG = 1  ;
			}
		}

	}

	//$GPGGA,141848.00,  2237.63306,N,08820.86316,E,1,03,2. 56,1.9,M,-54.2, M,,*74
	else if( (GPS_stuFlag.LAT_COMMA_FLAG) || (Local_u8CommaCounter == 2))
	{

		if(u8ReceivedChar == '.')
		{
			GPS_stuFlag.DOT_FLAG = 1 ;
		}
		else
		{

		}


		if(u8ReceivedChar == ',')
		{
			Local_u8CommaCounter++;

			if(Local_u8CommaCounter == 2)
			{
				GPS_stuFlag.LAT_COMMA_FLAG  = 0 ;
				GPS_stuFlag.DOT_FLAG        = 0 ;
			}
			else if (Local_u8CommaCounter == 3)
			{
				GPS_stuFlag.LONG_COMMA_FLAG = 1 ;
			}
			else
			{

			}

		}
	}
	else if( GPS_stuFlag.LONG_COMMA_FLAG )
	{
		if(u8ReceivedChar == ',')
		{
			GPS_stuFlag.LONG_COMMA_FLAG = 0 ;
		}

	}
	else
	{

		Local_u8CharCounter = 0 ;

	}





}//gps_start(void).





