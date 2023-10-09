/*    
*     Created in 17/9/2023
*     By : Ahmed Eldab3
*/

/******************************************************||---------||*****************************************************/
/******************************************************|| Key Pad ||*****************************************************/
/******************************************************||---------||*****************************************************/

#include "../../LIB/Bit_utils.h"
#include "../../LIB/Std_types.h"
#define  F_CPU 12000000
#include "util/delay.h"
#include "KPAD_Interface.h"
#include "KPAD_Private.h"
#include "KPAD_Config.h"
#include "../../MCAL/DIO/DIO_Interface.h"


/************************************************* Implementations Of Functions *************************************************/


/***********************************************************************************************************************************/
/* Function Name   : KPAD_voidInitialize
*  Function return : void
*  Function Inputs : void (No Inputs)
/***********************************************************************************************************************************/
void KPAD_voidInitialize (void)
{
	//	Set Rows as OUTPUT
	DIO_voidSetPinDirection(KPAD_PORT	, R0	, OUTPUT	);
	DIO_voidSetPinDirection(KPAD_PORT	, R1	, OUTPUT	);
	DIO_voidSetPinDirection(KPAD_PORT	, R2	, OUTPUT	);
	DIO_voidSetPinDirection(KPAD_PORT	, R3	, OUTPUT	);

	//	Set Cols as Input
	DIO_voidSetPinDirection(KPAD_PORT	, C0	, INPUT	);
	DIO_voidSetPinDirection(KPAD_PORT	, C1	, INPUT	);
	DIO_voidSetPinDirection(KPAD_PORT	, C2	, INPUT	);
	DIO_voidSetPinDirection(KPAD_PORT	, C3	, INPUT	);

	//	Set	Rows Value To High
	DIO_voidSetPinValue(KPAD_PORT	, R0	, HIGH	);
	DIO_voidSetPinValue(KPAD_PORT	, R1	, HIGH	);
	DIO_voidSetPinValue(KPAD_PORT	, R2	, HIGH	);
	DIO_voidSetPinValue(KPAD_PORT	, R3	, HIGH	);

	//	Set	Rows Value To High
	DIO_voidSetPinValue(KPAD_PORT	, C0	, HIGH	);
	DIO_voidSetPinValue(KPAD_PORT	, C1	, HIGH	);
	DIO_voidSetPinValue(KPAD_PORT	, C2	, HIGH	);
	DIO_voidSetPinValue(KPAD_PORT	, C3	, HIGH	);


}


/***********************************************************************************************************************************/
/* Function Name   : KPAD_u8GetPressed
*  Function return : u8
*  Function Inputs : void (No Inputs)
/***********************************************************************************************************************************/
u8	KPAD_u8GetPressed	(void)
{

	u8 Local_u8ReturnedKey	=	255 ;
	u8 Local_u8PressedKey	;
	for	(u8 Local_Rows	= KPAD_ROW_INIT 	; Local_Rows	<=	KPAD_ROW_END	; Local_Rows++	)
	{
		/*	Set Low	Rows Pin	*/
		DIO_voidSetPinValue(KPAD_PORT	,	Local_Rows	,	LOW	);
		/*	ASk for Cols	*/
		for( u8 Local_Cols = KPAD_COL_INIT ; Local_Cols <= KPAD_COL_END ; Local_Cols++)
		{

			Local_u8PressedKey = DIO_u8GetPinValue(KPAD_PORT ,Local_Cols);
			// Local_u8PressedKey == 0  -- > Key Pressed
			if(Local_u8PressedKey == PRESSED )
			{
				/*Delay for Debouncing*/
				_delay_ms(20);
				Local_u8PressedKey = DIO_u8GetPinValue(KPAD_PORT ,Local_Cols);
				if(Local_u8PressedKey == PRESSED )
				{

					Local_u8ReturnedKey = 	KPAD_Au8Keyss[Local_Rows -KPAD_ROW_INIT][Local_Cols - KPAD_COL_INIT];
					//Local_u8ReturnedKey =	KPAD_Au8Keys[Local_Rows -KPAD_ROW_INIT][Local_Cols - KPAD_COL_INIT];
					while(Local_u8PressedKey == PRESSED)
					{
						Local_u8PressedKey = DIO_u8GetPinValue(KPAD_PORT ,Local_Cols);
					}

					break ;

				}


			}


		}
        
        // return row to high again 
		DIO_voidSetPinValue(KPAD_PORT	,	Local_Rows	,	HIGH	);
		if(Local_u8ReturnedKey != 255 )
		{
			break ;
		}

	}


	return Local_u8ReturnedKey ;
}
