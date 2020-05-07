/******************************************************************************
 *
 * 	Module: 		BCM
 *
 *	File Name: 		BCM.h
 *
 * 	Authors: 		Mahmoud Gaber
 *
 *	Created on:		Saturday, 11-JAN-20 10:15:18 PM
 *
 *******************************************************************************/


#ifndef SERVICE_LAYER_BCM_BCM_H_
#define SERVICE_LAYER_BCM_BCM_H_

/************************************************************************/
/*	                        	 INCLUDES		            	        */
/************************************************************************/
#include "common_macros.h"
#include "std_types.h"
#include "COMM_UART.h"

/************************************************************************/
/*				                   DEFINES	            		        */
/************************************************************************/

#define MAX_NUM_CH   2

#define IDEL                0
#define SEND_BYTE           1
#define SEND_BYTE_COMPLET   2

#define RECIVE_BYTE         3
#define RECIVE_BYTE_COMPLET 4

#define LOCKED     0
#define UNLOCKED   1

#define RX_TX_ID    9


/** *******************************************************************
 * Input: NONE
 * Output:
 * In/Out:
 * Return: ERROR_STATUS.
 * Description: initiate the BCM  .
 *
 ********************************************************************/
ERROR_STATUS BCM_Init(void);
/** *******************************************************************
 * Input: NONE
 * Output:
 * In/Out:
 * Return: ERROR_STATUS.
 * Description: provide the BCM by the Buffer address and size .
 *
 ********************************************************************/
ERROR_STATUS BCM_Send(uint8 *pa_Txbuffer,uint16 size_Txbuffer,gptrfun_cbk_t gpf_app_Txack);/*structure*/
/** *******************************************************************
 * Input: NONE
 * Output:
 * In/Out:
 * Return: ERROR_STATUS.
 * Description:   .BCM_TX_Dispatcher
 *
 ********************************************************************/
ERROR_STATUS BCM_TX_Dispatcher(void);
/** *******************************************************************
 * Input: NONE
 * Output:
 * In/Out:
 * Return: ERROR_STATUS.
 * Description: make the BCM ready to recive
 *
 ********************************************************************/
ERROR_STATUS BCM_Rx_Setup(uint8 *pa_Rxbuffer,uint16 size_Rxbuffer,gptrfun_cbk_t gpf_app_Rxack);/*structure*/
/** *******************************************************************
 * Input: NONE
 * Output:
 * In/Out:
 * Return: ERROR_STATUS.
 * Description: BCM_RX_Dispatcher  .
 *
 ********************************************************************/
ERROR_STATUS BCM_RX_Dispatcher(void);

/** *******************************************************************
 * Input: NONE
 * Output:
 * In/Out:
 * Return: ERROR_STATUS.
 * Description:  Unlock the buffer
 *
 ********************************************************************/
ERROR_STATUS BCM_RX_Unlock(void);







#endif /* SERVICE_LAYER_BCM_BCM_H_ */

