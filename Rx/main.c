/*
 * main.c
 *
 *      Author: GABER
 */

/************************************************************************/
/*		                     INCLUDES	                                */
/************************************************************************/


#include "interrupt.h"
#include "BCM.h"
#include "DIO.h"

void ack(void)
{

}

uint8 array[5];

void main(void)
{
	PORTA_DIR |= 0xff;
 	BCM_Init();
	sei();
//	BCM_Send(array,50,ack);

	BCM_Rx_Setup(array,5,ack);

	while(1)
	{
		BCM_RX_Dispature();
		//BCM_TX_Dispature();

	}
}
