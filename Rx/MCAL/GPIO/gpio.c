/*
 * gpio.c
 *
 *  Created on:
 *      Author: Gaber
 */

#include "std_types.h"
#include "registers.h"
#include "gpio.h"


void gpioPortDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DIR = direction;
		break;
	case GPIOB :
		PORTB_DIR = direction;
		break;
	case GPIOC :
		PORTC_DIR = direction;
		break;
	case GPIOD :
		PORTD_DIR = direction;
		break;
	default:
		break;

	}

}

void gpioPortWrite(uint8 port, uint8 value)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA = value;
		break;
	case GPIOB :
		PORTB_DATA = value;
		break;
	case GPIOC :
		PORTC_DATA = value;
		break;
	case GPIOD :
		PORTD_DATA = value;
		break;
	default:
		break;

	}
}

void gpioPortToggle(uint8 port)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA ^= 0xff;
		break;
	case GPIOB :
		PORTB_DATA ^=  0xff;
		break;
	case GPIOC :
		PORTC_DATA ^=  0xff;
		break;
	case GPIOD :
		PORTD_DATA ^=  0xff;
		break;
	default:
		break;

	}
}

uint8 gpioPortRead(uint8 port)
{
	uint8 port_value  =0x55;
	switch(port)
	{
	case GPIOA :
		port_value = PORTA_PIN ;
		break;
	case GPIOB :
		port_value = PORTB_PIN ;
		break;
	case GPIOC :
		port_value = PORTC_PIN;
		break;
	case GPIOD :
		port_value = PORTD_PIN ;
		break;
	default:
		break;

	}
	return port_value;
}

void gpioPinDirection(uint8 port, uint8 pins, uint8 direction)
{
	if(port <= GPIOD && pins <= BIT7)
	{
		if(direction == OUTPUT)
		{
			switch(port)
			{
			case GPIOA :
				PORTA_DIR |=pins;
				break;
			case GPIOB :
				PORTB_DIR |=pins;
				break;
			case GPIOC :
				PORTC_DIR |=pins;
				break;
			case GPIOD :
				PORTD_DIR |=pins;
				break;
			default:
				break;
			}
		}
		else if(direction == INPUT)
		{
			switch(port)
			{
			case GPIOA :
				PORTA_DIR &= ~pins;
				break;
			case GPIOB :
				PORTB_DIR  &= ~pins;
				break;
			case GPIOC :
				PORTC_DIR &= ~pins;
				break;
			case GPIOD :
				PORTD_DIR  &= ~pins;
				break;
			default:
				break;
			}

		}
		else{

		}
	}
	else{
		/*invaled input*/
	}
}

void gpioPinWrite(uint8 port, uint8 pins, uint8 value)
{
	if(port <= GPIOD && pins <= BIT7)
	{
		if(value == OUTPUT)
		{
			switch(port)
			{
			case GPIOA :
				PORTA_DATA |=pins;
				break;
			case GPIOB :
				PORTB_DATA |=pins;
				break;
			case GPIOC :
				PORTC_DATA |=pins;
				break;
			case GPIOD :
				PORTD_DATA |=pins;
				break;
			default:
				break;
			}
		}
		else if(value == INPUT)
		{
			switch(port)
			{
			case GPIOA :
				PORTA_DATA &= ~pins;
				break;
			case GPIOB :
				PORTB_DATA  &= ~pins;
				break;
			case GPIOC :
				PORTC_DATA &= ~pins;
				break;
			case GPIOD :
				PORTD_DATA  &= ~pins;
				break;
			default:
				break;
			}

		}
		else{

		}
	}
	else{
		/*invaled input*/
	}
}
void gpioPinToggle(uint8 port, uint8 pins)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA ^= pins;
		break;
	case GPIOB :
		PORTB_DATA ^=  pins;
		break;
	case GPIOC :
		PORTC_DATA ^=  pins;
		break;
	case GPIOD :
		PORTD_DATA ^=  pins;
		break;
	default:
		break;

	}
}

uint8 gpioPinRead(uint8 port, uint8 pin)
{
	uint8 pin_check ;
	uint8 pin_value = 0x55;

	switch(port)
	{
	case GPIOA :
		pin_check = PORTA_PIN & pin;

		if(pin_check == pin)
		{
			pin_value =  HIGH ;
		}
		else if(pin_check == 0x00)
		{
			pin_value = LOW ;
		}
		else
		{
			/*invalid data*/
		}
		break;
	case GPIOB :
		pin_check = PORTB_PIN & pin;
		if(pin_check == pin)
		{
			pin_value =  HIGH ;
		}
		else if(pin_check == 0x00)
		{
			pin_value = LOW ;
		}
		else
		{
			/*invalid data*/
		}
		break;
	case GPIOC :
		pin_check = PORTC_PIN & pin;
		if(pin_check == pin)
		{
			pin_value =  HIGH ;
		}
		else if(pin_check == 0x00)
		{
			pin_value = LOW ;
		}
		else
		{
			/*invalid data*/
		}
		break;
	case GPIOD :
		pin_check = PORTD_PIN & pin;
		if(pin_check == pin)
		{
			pin_value =  HIGH ;
		}
		else if(pin_check == 0x00)
		{
			pin_value = LOW ;
		}
		else
		{
			/*invalid data*/
		}
		break;
	default:
		break;

	}


	return pin_value ;

}


void gpioLowerNibbleDirection(uint8 port, uint8 direction)
{
	direction &= 0x0f;
	switch(port)
	{
	case GPIOA :
		PORTA_DIR &= 0xf0;
		PORTA_DIR |= direction;
		break;
	case GPIOB :
		PORTB_DIR &= 0xf0;
		PORTB_DIR |= direction;
		break;
	case GPIOC :
		PORTC_DIR &= 0xf0;
		PORTC_DIR |= direction;
		break;
	case GPIOD :
		PORTD_DIR &= 0xf0;
		PORTD_DIR |= direction;
		break;
	default:
		break;

	}

}
void gpioLowerNibbleWrite(uint8 port, uint8 value)
{
	value &= 0x0f;
	switch(port)
	{
	case GPIOA :
		PORTA_DATA &= 0xf0;
		PORTA_DATA|= value;
		break;
	case GPIOB :
		PORTB_DATA &= 0xf0;
		PORTB_DATA |= value;
		break;
	case GPIOC :
		PORTC_DATA &= 0xf0;
		PORTC_DATA |= value;
		break;
	case GPIOD :
		PORTD_DATA &= 0xf0;
		PORTD_DATA |= value;
		break;
	default:
		break;

	}

}

void gpioLowerNibbleToggle(uint8 port)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA ^= 0x0f;
		break;
	case GPIOB :
		PORTB_DATA ^=  0x0f;
		break;
	case GPIOC :
		PORTC_DATA ^=  0x0f;
		break;
	case GPIOD :
		PORTD_DATA ^=  0x0f;
		break;
	default:
		break;

	}

}

uint8 gpioLowerNibbleRead(uint8 port)
{
	uint8 nipple_value=0xff;
	switch(port)
	{
	case GPIOA :
		nipple_value = PORTA_PIN & 0x0f;
		break;
	case GPIOB :
		nipple_value = PORTB_PIN & 0x0f;
		break;
	case GPIOC :
		nipple_value = PORTC_PIN & 0x0f;
		break;
	case GPIOD :
		nipple_value = PORTD_PIN & 0x0f;
		break;
	default:
		break;

	}

	return nipple_value;
}
void gpioUpperNibbleDirection(uint8 port, uint8 direction)
{
	direction &= 0xf0;
	switch(port)
	{
	case GPIOA :
		PORTA_DIR &= 0x0f;
		PORTA_DIR |= direction;
		break;
	case GPIOB :
		PORTB_DIR &= 0x0f;
		PORTB_DIR |= direction;
		break;
	case GPIOC :
		PORTC_DIR &= 0x0f;
		PORTC_DIR |= direction;
		break;
	case GPIOD :
		PORTD_DIR &= 0x0f;
		PORTD_DIR |= direction;
		break;
	default:
		break;

	}
}

void gpioUpperNibbleWrite(uint8 port, uint8 value)
{
	value &= 0xf0;
	switch(port)
	{
	case GPIOA :
		PORTA_DATA &= 0x0f;
		PORTA_DATA|= value;
		break;
	case GPIOB :
		PORTB_DATA &= 0x0f;
		PORTB_DATA |= value;
		break;
	case GPIOC :
		PORTC_DATA &= 0x0f;
		PORTC_DATA |= value;
		break;
	case GPIOD :
		PORTD_DATA &= 0x0f;
		PORTD_DATA |= value;
		break;
	default:
		break;

	}

}

void gpioUpperNibbleToggle(uint8 port)
{
	switch(port)
	{
	case GPIOA :
		PORTA_DATA ^= 0xf0;
		break;
	case GPIOB :
		PORTB_DATA ^=  0xf0;
		break;
	case GPIOC :
		PORTC_DATA ^=  0xf0;
		break;
	case GPIOD :
		PORTD_DATA ^=  0xf0;
		break;
	default:
		break;

	}

}

uint8 gpioUpperNibbleRead(uint8 port)
{
	uint8 nipple_value=0xff;
	switch(port)
	{
	case GPIOA :
		nipple_value = PORTA_PIN & 0xf0;
		nipple_value>>=4;
		break;
	case GPIOB :
		nipple_value = PORTB_PIN & 0xf0;
		nipple_value>>=4;
		break;
	case GPIOC :
		nipple_value = PORTC_PIN & 0xf0;
		nipple_value>>=4;
		break;
	case GPIOD :
		nipple_value = PORTD_PIN & 0xf0;
		nipple_value>>=4;
		break;
	default:
		break;

	}


	return nipple_value;
}


