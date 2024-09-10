/*
 * LED_program.c
 *
 *  Created on: Jul 16, 2024
 *      Author: user
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"

#include "../HAL/LED_private.h"
#include "../HAL/LED_config.h"
#include "../HAL/LED_interface.h"

u8 LED_u8TurnOn(LED_t * Copy_LED)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_LED->ConnType==LED_SOUCE)
	{
		DIO_u8SetPinValue(Copy_LED->Port,Copy_LED->Pin,DIO_PIN_HIGH);
	}
	else if(Copy_LED->ConnType==LED_SINK)
	{
		DIO_u8SetPinValue(Copy_LED->Port,Copy_LED->Pin,DIO_PIN_LOW);
	}
	else
		Local_u8ErrorState = NOTOK;

	return Local_u8ErrorState;
}
u8 LED_u8TurnOff(LED_t * Copy_LED)
{
	u8 Local_u8ErrorState = OK;
	if(Copy_LED->ConnType==LED_SOUCE)
	{
		DIO_u8SetPinValue(Copy_LED->Port,Copy_LED->Pin,DIO_PIN_LOW);
	}
	else if(Copy_LED->ConnType==LED_SINK)
	{
		DIO_u8SetPinValue(Copy_LED->Port,Copy_LED->Pin,DIO_PIN_HIGH);
	}
	else
		Local_u8ErrorState = NOTOK;

	return Local_u8ErrorState;
}
u8 LED_u8TogLed(LED_t *Copy_LED)
{
	u8 Local_u8ErrorState = OK;
	static u8 Local_u8State = 0;
	if(Copy_LED->ConnType==LED_SOUCE)
	{
		TOG_BIT(Local_u8State,0);
		DIO_u8SetPinValue(Copy_LED->Port,Copy_LED->Pin,Local_u8State);
	}
	else if(Copy_LED->ConnType==LED_SINK)
	{
		TOG_BIT(Local_u8State,0);
		DIO_u8SetPinValue(Copy_LED->Port,Copy_LED->Pin,Local_u8State);
	}
	else
		Local_u8ErrorState = NOTOK;

	return Local_u8ErrorState;
}
