/*
 * BCM.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: ECC
 */

#define debug 0
#define real  1
#if real

#ifndef SERVICE_LAYER_BCM_BCM_H_
#define SERVICE_LAYER_BCM_BCM_H_

#include "common_macros.h"
#include "std_types.h"
#include "COMM_UART.h"


#define MAX_NUM_CH   2

#define IDEL                0
#define SEND_BYTE           1
#define SEND_BYTE_COMPLET   2

#define RECIVE_BYTE         3
#define RECIVE_BYTE_COMPLET 4

#define LOCKED     0
#define UNLOCKED   1

#define RX_TX_ID    9

ERROR_STATUS BCM_Init(void);
ERROR_STATUS BCM_Send(uint8 *pa_Txbuffer,uint16 size_Txbuffer,gptrfun_cbk_t gpf_app_Txack);/*structure*/
ERROR_STATUS BCM_TX_Dispature(void);
ERROR_STATUS BCM_Rx_Setup(uint8 *pa_Rxbuffer,uint16 size_Rxbuffer,gptrfun_cbk_t gpf_app_Rxack);/*structure*/
ERROR_STATUS BCM_RX_Dispature(void);
ERROR_STATUS BCM_RX_Unlock(void);







#endif /* SERVICE_LAYER_BCM_BCM_H_ */
#endif
