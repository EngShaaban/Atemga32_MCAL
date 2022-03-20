#include<stdio.h>

#include"LIB/errorStates.h"



typedef enum
{
	off      ,
	on       ,

}STATE_t;

STATE_t   TIMER_enuSTATE  = off ;

typedef struct {
	int a ;
	int b ;
}ST_t;

static ST_t*  Array[2]={NULL,NULL};

ST_t  ArrayOfST[2]={
		{
				.a = 11 ,
				.b = 12 ,

		}
		,
		{
				.a = 21 ,
				.b = 22 ,

		}


};

void fun(ST_t* p2ArrayOfST );

ES_t Local_enuErrorState=  ES_NOK;

int  main(void)
{
	printf("ArrayOfST   =%x\n",ArrayOfST);

	printf("ArrayOfST[0]=%x\n\n",&ArrayOfST+0);

	printf("ArrayOfST+1 =%x\n",ArrayOfST+1);


	fun(ArrayOfST);

	printf("Timer State = %d \n",TIMER_enuSTATE);

}


void fun(ST_t* p2ArrayOfST )
{

	Array[0]=&(p2ArrayOfST[0]);
	Array[1]=&(p2ArrayOfST[1]);

	printf("===========Inside the fun()==============\n");
	printf("Array[0]=%x\n",Array[0]);
	printf("Array[1]=%x\n",Array[1]);









}


