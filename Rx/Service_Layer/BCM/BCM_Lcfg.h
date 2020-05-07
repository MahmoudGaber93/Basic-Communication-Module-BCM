/*
 * BCM_Lcfg.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: GABER
 */

#if 1
#include "std_types.h"
#include "COMM_UART.h"
#define UART_CH0  0
#define SPI_CH1   1


typedef struct
{
	uint8 Num_Ch;
	uint8  operation_mode;

}str_BCM_cfg_t;


extern str_BCM_cfg_t  gstr_BCM_init;
#endif
