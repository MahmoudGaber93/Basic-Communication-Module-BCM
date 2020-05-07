/*
 * BCM.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: ECC
 */

#include "DIO.h"
#include "BCM.h"
#include "BCM_Lcfg.h"
#include "COMM_UART.h"
#include "softwareDelay.h"
#include "error_check.h"
#include "registers.h"







typedef struct
{
	uint8 BCM_ID;
	uint16 data_size;
	uint16 data_size_recived;

	uint8 CS;
	uint8 * pa_databuffer;
	uint16 index;
}str_Data_Buffer_t;


str_Data_Buffer_t  gastr_BSMbuffer[MAX_NUM_CH];

uint8 gu8_TxBSM_state    = 0;
uint8 gu8_TxBuffer_State = 0;
uint8 gu8_Txflag = LOW;

uint8 gu8_RxBSM_state    = 0;
uint8 gu8_RxBuffer_State = 0;
static volatile uint8 gu8_Rxflag = 0;
static volatile uint8  flagRX =LOW;
uint8 data = 0;

gptrfun_cbk_t gpf_BCM_APP_cbk=NULL;

static void Clear_objects(void)
{
	uint8 count =0;
	gu8_TxBSM_state    = 0;
	gu8_TxBuffer_State = 0;
	gu8_Txflag = LOW;
	for(count = 0; count < MAX_NUM_CH ;count++)
	{
		gastr_BSMbuffer[count].BCM_ID = 0;
		gastr_BSMbuffer[count].CS = 0;
		gastr_BSMbuffer[count].pa_databuffer = NULL;
		gastr_BSMbuffer[count].data_size = 0;
		gastr_BSMbuffer[count].data_size_recived=0;
		gastr_BSMbuffer[count].index = 0;

	}
	gpf_BCM_APP_cbk=NULL;
	gu8_RxBSM_state    = 0;
	gu8_RxBuffer_State = 0;
	gu8_Rxflag = 0;


}

static void Uart_TxISR(void)
{
	gu8_Txflag = HIGH;
}



static void Uart_RxISR(void)
{


	flagRX = HIGH;
	UART_ReceiveByte(&data);
	PORTA_DATA^=0x01;


#if 0
	if(gu8_Rxflag == 0)
	{
		UART_ReceiveByte(&(gastr_BSMbuffer[UART_CH0].BCM_ID));

		gu8_Rxflag++;
		PORTA_DATA|=0x01;
	}
	else if(gu8_Rxflag == 1)
	{
		UART_ReceiveByte(&(gastr_BSMbuffer[UART_CH0].data_size_recived));
		gu8_Rxflag++;
		PORTA_DATA|=0x02;

	}
	else if(gu8_Rxflag == 2)
	{
		UART_ReceiveByte(&(gastr_BSMbuffer[UART_CH0].data_size_recived));
		gu8_Rxflag++;
		PORTA_DATA|=0x04;

	}

	else if(gu8_Rxflag == 3)
	{
		UART_ReceiveByte(&(gastr_BSMbuffer[UART_CH0].pa_databuffer[(gastr_BSMbuffer[UART_CH0].index)++]));
		//gu8_Rxflag = 5;
		PORTA_DATA|=0x08;
	}
#endif

}


ERROR_STATUS BCM_Init(void)
{
	uint8 u8_error_val = BCM_ERROR_BASE + SUCSSECE;

	if(gstr_BCM_init.Num_Ch ==  UART_CH0)
	{
		Clear_objects();

		UART_cfg_s str_Uart_init ;
		str_Uart_init.ptr_Transmit_CBK =Uart_TxISR;
		str_Uart_init.ptr_DataRegEmpty_CBk = NULL;
		str_Uart_init.ptr_Resceive_CBK = Uart_RxISR;
		str_Uart_init.u32_BaudRate =9600;
		str_Uart_init.u8_DataSize = UART_8_BIT;
		str_Uart_init.u8_DesiredOperation =TRANSCEIVER;
		str_Uart_init.u8_DoubleSpeed = UART_NO_DOUBLE_SPEED;
		str_Uart_init.u8_InterruptMode = UART_INTERRUPT;
		str_Uart_init.u8_ParityBit =UART_NO_PARITY;
		str_Uart_init.u8_StopBit = UART_ONE_STOP_BIT;
		UART_Init(&str_Uart_init);

		gu8_TxBSM_state=IDEL;
		gu8_TxBuffer_State = UNLOCKED;


		gu8_RxBSM_state=IDEL;
		gu8_RxBuffer_State = UNLOCKED;
	}

	else if(gstr_BCM_init.Num_Ch ==  SPI_CH1)
	{

	}
	else
	{
		 u8_error_val = TMU_ERROR_BASE + INVALID_INPUT;

	}
	return u8_error_val;
}


ERROR_STATUS BCM_Send(uint8 *pa_buffer,uint16 size_buffer,gptrfun_cbk_t gpf_app_ack)/*structure*/
{
	uint8 u8_error_val = BCM_ERROR_BASE + SUCSSECE;
	if(gu8_TxBuffer_State != LOCKED)
	{
		if(NULL != pa_buffer)
		{
			uint8 u8_temp;
			gastr_BSMbuffer[UART_CH0].pa_databuffer = pa_buffer;
			gastr_BSMbuffer[UART_CH0].data_size = size_buffer;
			gastr_BSMbuffer[UART_CH0].BCM_ID = 9;
			gpf_BCM_APP_cbk = gpf_app_ack;

			gu8_TxBuffer_State = LOCKED;

			UART_SendByte((gastr_BSMbuffer[UART_CH0].BCM_ID)+48);

			SwDelay_ms(0.1);


			u8_temp = ((gastr_BSMbuffer[UART_CH0].data_size) >>8);
			UART_SendByte((u8_temp+48));

			u8_temp = (gastr_BSMbuffer[UART_CH0].data_size);
			SwDelay_ms(0.1);


			UART_SendByte((u8_temp+48));


			/***change state to send byte***/
			gu8_TxBSM_state = SEND_BYTE;
		}
		else
		{
			 u8_error_val = BCM_ERROR_BASE + NULL_POINTER;

		}

	}
	else
	{
		 u8_error_val = BCM_ERROR_BASE + BUFFER_LOCKED;
	}
	return u8_error_val;

}


ERROR_STATUS BCM_TX_Dispature(void)
{
	uint8 u8_error_val = BCM_ERROR_BASE + SUCSSECE;
	switch(gu8_TxBSM_state)
	{
	case IDEL:
		gu8_TxBuffer_State = UNLOCKED;

		break;
	case SEND_BYTE:
		if(gu8_Txflag == HIGH)
		{
			/**** change state to "SEND_BYTE_COMPLET"****/
			gu8_TxBSM_state = SEND_BYTE_COMPLET;

		}
		else
		{

		}
		break;
	case SEND_BYTE_COMPLET:
		if(gastr_BSMbuffer[UART_CH0].index  < gastr_BSMbuffer[UART_CH0].data_size )
		{
			/**** change state to "SEND_BYTE"****/
			gu8_TxBSM_state = SEND_BYTE;

			/**** make the flag Low ******/
			gu8_Txflag = LOW;

			/****calculate the check sum******/
			gastr_BSMbuffer[UART_CH0].CS +=  gastr_BSMbuffer[UART_CH0].pa_databuffer[gastr_BSMbuffer[UART_CH0].index];

			/****send byte****/
			UART_SendByte(gastr_BSMbuffer[UART_CH0].pa_databuffer[gastr_BSMbuffer[UART_CH0].index ++]);


			/***check if the index reach to required  size pluse 1*****/
			if(gastr_BSMbuffer[UART_CH0].index  == gastr_BSMbuffer[UART_CH0].data_size )
			{
				/****send the check sum ****/
				SwDelay_ms(0.1);
				UART_SendByte((gastr_BSMbuffer[UART_CH0].CS)+48);
				gpf_BCM_APP_cbk();
			}
			else
			{

			}

		}
		else
		{
			/**** change state to "IDEL"****/

			gu8_TxBSM_state = IDEL;
		}

		break;
	default:
		 u8_error_val = BCM_ERROR_BASE + INVALID_INPUT;		break;

	}


	return u8_error_val ;


}


ERROR_STATUS BCM_Rx_Setup(uint8 *pa_Rxbuffer,uint16 size_Rxbuffer,gptrfun_cbk_t gpf_app_Rxack)/*structure*/
{
	uint8 u8_error_val = BCM_ERROR_BASE + SUCSSECE;
	if(NULL != pa_Rxbuffer && NULL != gpf_app_Rxack )
	{
		if(gu8_RxBuffer_State != LOCKED)
		{
			gastr_BSMbuffer[UART_CH0].pa_databuffer =  pa_Rxbuffer;
			gastr_BSMbuffer[UART_CH0].data_size     =  size_Rxbuffer;
			gastr_BSMbuffer[UART_CH0].BCM_ID        =  RX_TX_ID ;
			gpf_BCM_APP_cbk = gpf_app_Rxack;

			gu8_RxBuffer_State = UNLOCKED;
		}
		else
		{
			u8_error_val = BCM_ERROR_BASE + BUFFER_LOCKED;
		}
	}
	else
	{
		u8_error_val = BCM_ERROR_BASE + NULL_POINTER;

	}
	return u8_error_val;


}

ERROR_STATUS BCM_RX_Dispature(void)
{
	uint8 u8_error_val = BCM_ERROR_BASE + SUCSSECE;
	if(flagRX == HIGH)
	{
	switch(gu8_RxBSM_state)
	{
	case IDEL:
		if(gu8_RxBuffer_State != LOCKED)
		{
			gu8_RxBSM_state =RECIVE_BYTE;
			gu8_RxBuffer_State = LOCKED;
			PORTA_DATA^=0x02;


		}
		else
		{

		}
			break;
	case RECIVE_BYTE:
		if(gu8_Rxflag == 0)
		{
			if( RX_TX_ID == data-48)
			{
				gu8_Rxflag++;
				flagRX = LOW;
				PORTA_DATA^=0x04;


			}
			else
			{
				u8_error_val = BCM_ERROR_BASE + NOT_MATCHED_ID;
				//PORTA_DATA^=0x08;

			}

		}
		else if(gu8_Rxflag == 1)
		{
			(gastr_BSMbuffer[UART_CH0].data_size_recived) =data-48;
			(gastr_BSMbuffer[UART_CH0].data_size_recived) = (gastr_BSMbuffer[UART_CH0].data_size_recived)<<8;
			PORTA_DATA|=0x10;

			gu8_Rxflag++;
			flagRX =LOW;
		}

	else if(gu8_Rxflag == 2)
	{
		(gastr_BSMbuffer[UART_CH0].data_size_recived) |= data-48;
		if( (gastr_BSMbuffer[UART_CH0].data_size_recived) == (gastr_BSMbuffer[UART_CH0].data_size))
		{			PORTA_DATA =0x20;

			gu8_Rxflag++;
			flagRX =LOW;
		}
		else
		{
			u8_error_val = BCM_ERROR_BASE + NOT_MATCHED_SIZE;
			PORTA_DATA|=0x40;

		}

	}

	else
	{
		gu8_RxBSM_state =RECIVE_BYTE_COMPLET;
		//PORTA_DATA^=0x80;

	}
	break;

	case RECIVE_BYTE_COMPLET:
		if( gastr_BSMbuffer[UART_CH0].index <  gastr_BSMbuffer[UART_CH0].data_size)
		{
			//PORTA_DATA^=0x10;
			gastr_BSMbuffer[UART_CH0].pa_databuffer[ gastr_BSMbuffer[UART_CH0].index] = data;

			gastr_BSMbuffer[UART_CH0].CS += gastr_BSMbuffer[UART_CH0].pa_databuffer[ gastr_BSMbuffer[UART_CH0].index++];
					flagRX =LOW;
					gu8_RxBSM_state =RECIVE_BYTE;



		}
		else
		{
			if(gastr_BSMbuffer[UART_CH0].CS  == gastr_BSMbuffer[UART_CH0].pa_databuffer[ gastr_BSMbuffer[UART_CH0].index])
			{
				PORTA_DATA^=0x80;

				gpf_BCM_APP_cbk();
				flagRX =LOW;
			}
			else
			{
				u8_error_val = BCM_ERROR_BASE + NOT_MATCHED_CS;
						//PORTA_DATA^=0x40;


			}
		}

		break;
	default:
		u8_error_val = BCM_ERROR_BASE + INVALID_INPUT;
		break;
}
	}
	else
	{

	}
return u8_error_val;
}



ERROR_STATUS BCM_RX_Unlock(void)
{
	uint8 u8_error_val = BCM_ERROR_BASE + SUCSSECE;
	gu8_RxBuffer_State = UNLOCKED;
	return u8_error_val;


}


