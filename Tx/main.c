/******************************************************************************
 *
 *
 *	File Name: 		BCM.c
 *
 * 	Authors: 		Mahmoud Gaber
 *
 *	Created on:		Saturday, 11-JAN-20 10:15:18 PM
 *
 *******************************************************************************/
/************************************************************************/
/*		                     INCLUDES	                                */
/************************************************************************/


#include "interrupt.h"
#include "BCM.h"


void ack(void)
{


}

uint8 array[5]="12345";

void main(void)
{

	BCM_Init();
	sei();

	BCM_Send(array,5,ack);

	while(1)
	{
		BCM_TX_Dispatcher();
	}
}
