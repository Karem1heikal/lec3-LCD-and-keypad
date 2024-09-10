/*
 * main.c
 *
 *  Created on: Jun 28, 2024
 *      Author: user
 */

#include <util/delay.h>
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/PORT_interface.h"
#include "../HAL/CLCD_interface.h"
#include "../HAL/SSD_interface.h"
#include "../HAL/LED_interface.h"
#include "../HAL/SW_interface.h"

#define Pattern {0b0000100,\
				 0b0001110,\
				 0B0010101,\
				 0B0000100,\
				 0B0000100,\
				 0B0000100,\
				 0B0000100}
//calculator 1 digit
void main()
{
	PORT_voidInit();
	CLCD_voidInit();
	u8 arr[8]= Pattern;
	SW_t enter={DIO_PORTB,DIO_PIN7,SW_PULL_UP,SW_SELF_LOCK},\
		down={DIO_PORTB,DIO_PIN6,SW_PULL_UP,SW_SELF_LOCK},\
		up={DIO_PORTB,DIO_PIN5,SW_PULL_UP,SW_SELF_LOCK};
	u8 x1,x2,x3,op1=1,oper[4]={'+','-','*','/'},op2=1,op=0,result;
	while(1)
	{
		CLCD_voidSendCommand(0x80);
		CLCD_voidWriteNumber(op1);
		CLCD_voidSendData(oper[op]);
		CLCD_voidWriteNumber(op2);
		CLCD_voidWriteSpecialCharacter(arr,0,1,0);
		do{
			SW_u8GetState(&enter,&x1);
			SW_u8GetState(&up,&x2);
			CLCD_voidGoToXY(0,0);
			CLCD_voidWriteNumber(op1);
			if(x2==SW_PRESSED)
			{
				op1++;
				if(op1>=10)
					op1=0;
			}
			SW_u8GetState(&down,&x3);
			if(x3==SW_PRESSED)
			{
				op1--;
				if(op1>=10)
					op1=9;
			}
		}while(x1==SW_NOT_PRESSED);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendData(' ');
		CLCD_voidWriteSpecialCharacter(arr,0,1,1);
		do{
			SW_u8GetState(&enter,&x1);
			SW_u8GetState(&up,&x2);
			CLCD_voidGoToXY(0,1);
			CLCD_voidSendData(oper[op]);
			if(x2==SW_PRESSED)
			{
				op++;
				if(op>=4)
					op=0;
			}
			SW_u8GetState(&down,&x3);
			if(x3==SW_PRESSED)
			{
				op--;
				if(op>=4)
					op=3;
			}
		}while(x1==SW_NOT_PRESSED);
		CLCD_voidGoToXY(1,1);
		CLCD_voidSendData(' ');
		CLCD_voidWriteSpecialCharacter(arr,0,1,2);
		do{
			SW_u8GetState(&enter,&x1);
			SW_u8GetState(&up,&x2);
			CLCD_voidGoToXY(0,2);
			CLCD_voidWriteNumber(op2);
			if(x2==SW_PRESSED)
			{
				op2++;
				if(op2>=10)
					op2=0;
			}
			SW_u8GetState(&down,&x3);
			if(x3==SW_PRESSED)
			{
				op2--;
				if(op2>=10)
					op2=9;
			}
		}while(x1==SW_NOT_PRESSED);
		CLCD_voidGoToXY(1,2);
		CLCD_voidSendData(' ');
		CLCD_voidGoToXY(0,3);
		CLCD_voidSendData('=');
		switch(oper[op]){
		case '+':
			result = op1+op2;
			CLCD_voidWriteNumber(result);
			break;
		case '-':
			if(op1<op2)
			{
				result = op2-op1;
				CLCD_voidSendData('-');
			}
			else
				result = op1-op2;
			CLCD_voidWriteNumber(result);
			break;
		case '*':
			result = op1*op2;
			CLCD_voidWriteNumber(result);
			break;
		case '/':
			if(op2==0)
			{
				CLCD_voidSendString("inf");
				break;
			}
			u8 e=op1/op2;
			u8 s=((op1/(f32)op2)-(f32)e)*1000;
			if(s==0)
			{
				CLCD_voidWriteNumber(e);
			}
			else{
				CLCD_voidWriteNumber(e);
				CLCD_voidGoToXY(0,5);
				CLCD_voidSendData('.');
				CLCD_voidGoToXY(0,6);
				CLCD_voidWriteNumber(s);
			}
			break;
		}
		do{
			SW_u8GetState(&enter,&x1);
		}while(x1==SW_NOT_PRESSED);
		CLCD_voidSendCommand(1);
	}
}
