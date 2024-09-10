/*
 * SW_program.c
 *
 *  Created on: Jul 16, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include <util/delay.h>
#include "../HAL/SW_private.h"
#include "../HAL/SW_config.h"
#include "../HAL/SW_interface.h"


/* Function Name: SW_u8GetState
 * Tokens : *Copy_SW, *Copy_u8State
 * 			Copy_SW     : Full with Port,Pin,SelfType,switch function
 * 			Copy_u8State: return State of switch as (0) Pressed , (1) Not pressed
 * use for: Get Switch by delay debouncing of switch as (0) Pressed , (1) Not pressed
 *  */
u8 SW_u8GetState(SW_t* Copy_SW,u8 *Copy_u8State)
{
	u8 Local_u8ErrorState = OK;
	//static u8 pressed_conf_level = 0;
	//static u8 released_conf_level = 0;
	//static u8 pressed = 0;
	//static u8 pressed2 = 0;
	*Copy_u8State = SW_NOT_PRESSED;
	static u8 Local_u8SwState;
	if(Copy_SW->Pulltype == SW_PULL_UP)
	{
		if(Copy_SW->SelfLockType == SW_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
			if(Local_u8SwState == DIO_PIN_LOW)
			{
				_delay_ms(150);
				DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
				if(Local_u8SwState == DIO_PIN_LOW )
				{
					*Copy_u8State = SW_PRESSED;
				}
				else
				{
					*Copy_u8State = SW_NOT_PRESSED;
				}
			}
		}
		else if(Copy_SW->SelfLockType == SW_NOT_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,Copy_u8State);
			if (Local_u8SwState == DIO_PIN_LOW)
				*Copy_u8State = SW_PRESSED;
			else
				*Copy_u8State = SW_NOT_PRESSED;
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else if(Copy_SW->Pulltype == SW_PULL_DOWN)
	{

		if(Copy_SW->SelfLockType == SW_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
			if(Local_u8SwState == DIO_PIN_HIGH)
			{
				_delay_ms(150);
				DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
				if(Local_u8SwState == DIO_PIN_HIGH )
				{
					*Copy_u8State = SW_PRESSED;
				}
			}
		}
		else if(Copy_SW->SelfLockType == SW_NOT_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,Copy_u8State);
			if (Local_u8SwState == DIO_PIN_HIGH)
				*Copy_u8State = SW_PRESSED;
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else
		Local_u8ErrorState = NOTOK;

	return Local_u8ErrorState;
}

 /* Function Name: SW_u8GetState2
 * Tokens : *Copy_SW, *Copy_u8State
 * 			Copy_SW     : Full with Port,Pin,SelfType,switch function
 * 			Copy_u8State: return State of switch as (0) Pressed , (1) Not pressed
 * use for: Get Switch by Function Call Back i.e (switch function )
 *  */
u8 SW_u8GetState2(SW_t* Copy_SW,u8 *Copy_u8State)
{
	u8 Local_u8ErrorState = OK;
	static u8 pressed_conf_level = 0;
	static u8 released_conf_level = 0;
	static u8 pressed = 0;
	*Copy_u8State = SW_NOT_PRESSED;
	static u8 Local_u8SwState;
	if(Copy_SW->Pulltype == SW_PULL_UP)
	{
		pressed = 0;
		if(Copy_SW->SelfLockType == SW_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
			if(Local_u8SwState == DIO_PIN_LOW)
			{
				DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
				if(Local_u8SwState == DIO_PIN_LOW)
				{
					pressed_conf_level++;
					if(pressed_conf_level>20)
					{
						if(pressed==0)
						{
							*Copy_u8State = SW_PRESSED;
							Copy_SW->Notification();
							pressed=1;
						}
						pressed_conf_level=0;
					}
					else
					{
						released_conf_level++;
						if(released_conf_level>20)
						{
							pressed = 0;
							released_conf_level = 0;
						}
					}
				}
			}
		}
		else if(Copy_SW->SelfLockType == SW_NOT_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,Copy_u8State);
			if (Local_u8SwState == DIO_PIN_LOW)
				*Copy_u8State = SW_PRESSED;
			else
				*Copy_u8State = SW_NOT_PRESSED;
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else if(Copy_SW->Pulltype == SW_PULL_DOWN)
	{
		pressed = 1;
		if(Copy_SW->SelfLockType == SW_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,&Local_u8SwState);
			if(Local_u8SwState == DIO_PIN_HIGH)
			{
				pressed_conf_level++;
				if(pressed_conf_level>20)
				{
					if(pressed==1)
					{
						*Copy_u8State = SW_PRESSED;
						Copy_SW->Notification();
						pressed=0;
					}
					pressed_conf_level=0;
				}
				else
				{
					released_conf_level++;
					if(released_conf_level>20)
					{
						pressed = 1;
						released_conf_level = 0;
					}
				}
			}
		}
		else if(Copy_SW->SelfLockType == SW_NOT_SELF_LOCK)
		{
			DIO_u8GetPinValue(Copy_SW->Port,Copy_SW->Pin,Copy_u8State);
			if (Local_u8SwState == DIO_PIN_HIGH)
				*Copy_u8State = SW_PRESSED;
		}
		else
			Local_u8ErrorState = NOTOK;
	}
	else
		Local_u8ErrorState = NOTOK;

	return Local_u8ErrorState;
}
