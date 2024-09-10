/*
 * SSD_program.c
 *
 *  Created on: Jul 16, 2024
 *      Author: user
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"

#include "../HAL/SSD_private.h"
#include "../HAL/SSD_config.h"
#include "../HAL/SSD_interface.h"

u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_t *Copy_SSD)
{
	u8 Local_u8ErrorState= OK;
	static u8 SSD_Arr[10] = SSD_ARR_OF_NUM;
	if(Copy_SSD->ComType==ANODE)
	{
		Local_u8ErrorState = DIO_u8SetPortValue(Copy_SSD->Port,~SSD_Arr[Copy_u8Number]);
	}
	else if(Copy_SSD->ComType==CATHODE )
	{
		Local_u8ErrorState = DIO_u8SetPortValue(Copy_SSD->Port,SSD_Arr[Copy_u8Number]);
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;

}
u8 SSD_u8Enable(SSD_t *Copy_SSD)
{
	u8 Local_u8ErrorState= OK;
	if(Copy_SSD->ComType==ANODE)
	{
		Local_u8ErrorState = DIO_u8SetPinValue(Copy_SSD->EnablePort,Copy_SSD->EnablePin,DIO_PIN_HIGH);
	}
	else if(Copy_SSD->ComType==CATHODE )
	{
		Local_u8ErrorState = DIO_u8SetPinValue(Copy_SSD->EnablePort,Copy_SSD->EnablePin,DIO_PIN_LOW);
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}

u8 SSD_u8Disable(SSD_t *Copy_SSD)
{
	u8 Local_u8ErrorState= OK;
	if(Copy_SSD->ComType==ANODE)
	{
		Local_u8ErrorState = DIO_u8SetPinValue(Copy_SSD->EnablePort,Copy_SSD->EnablePin,DIO_PIN_LOW);
	}
	else if(Copy_SSD->ComType==CATHODE )
	{
		Local_u8ErrorState = DIO_u8SetPinValue(Copy_SSD->EnablePort,Copy_SSD->EnablePin,DIO_PIN_HIGH);
	}
	else
		Local_u8ErrorState = NOTOK;
	return Local_u8ErrorState;
}
