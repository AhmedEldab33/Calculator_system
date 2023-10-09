/*    
*     Created in 10/9/2023
*     By : Ahmed Eldab3
*/

/******************************************************||----------------------||*****************************************************/
/******************************************************||Liquid Crystal Display||*****************************************************/
/******************************************************||----------------------||*****************************************************/

#include "../../LIB/Bit_utils.h"
#include "../../LIB/Std_types.h"
#define  F_CPU 12000000
#include "util/delay.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "LCD_Config.h"
#include "../../MCAL/DIO/DIO_Interface.h"


/******************************************************|--------------------- |*****************************************************/
/******************************************************|  My Custom Patterns  |*****************************************************/
/******************************************************|--------------------- |*****************************************************/

// pattern أ
u8 arr_1[8] = {0b00110,0b00100,0b01110,0b00000,0b00100,0b00100,0b00100,0b00100};

// pattern ح
u8 arr_2[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b11100,0b00010,0b11111};

// pattern م
u8 arr_3[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00111,0b00101,0b11111};

// pattern د
u8 arr_4[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00001,0b00001,0b01111};

// pattern mario open legs
u8 arr_5[8] = {0b01110,0b01110,0b01110,0b00100,0b01110,0b10101,0b01010,0b10001};

// pattern mario close legs
u8 arr_6[8] = {0b01110,0b01110,0b01110,0b00100,0b01110,0b10101,0b00100,0b00100};

/************************************************* Implementations Of Functions *************************************************/


/***********************************************************************************************************************************/
/* Function Name   : LCD_voidInitialize
*  Function return : void
*  Function Inputs : void (No Inputs)
/***********************************************************************************************************************************/
void LCD_voidIitialize (void){
// Steps for initializing-->

    
    //(1) Function Set Command
    LCD_voidWriteCommand (Function_Set);

    //(2) delay by 1ms
    _delay_ms(2);

    //(3) Display ON/Off command
    LCD_voidWriteCommand (Display_On_Off);

    //(4) delay by 1ms
    _delay_ms(2);

    //(5) Display Clear command
    LCD_voidWriteCommand (Clear_Display);

    //(6) delay by 2ms
    _delay_ms(2);

    //(7) Entry Mode Set command
    LCD_voidWriteCommand (Entry_Mode_Set);

    

}


/***********************************************************************************************************************************/
/* Function Name    : LCD_voidWrite Command
*  Function return  : void
*  Function Inputs  : Command Binary Number
*  Command Input    : Its an Binary Number according to DataSheet
/***********************************************************************************************************************************/
void LCD_voidWriteCommand (u8 Copy_command)
{
    

    // RS Direction = OUTPUT
    DIO_voidSetPinDirection(LCD_Control_Pins_Port,RS_Pin,OUTPUT);

    // RW Direction = OUTPUT
    DIO_voidSetPinDirection(LCD_Control_Pins_Port,RW_Pin,OUTPUT);

    // Enable Direction = OUTPUT
    DIO_voidSetPinDirection(LCD_Control_Pins_Port,EN_Pin,OUTPUT);

    // DB0 : DB7 Direction = OUTPUT
    DIO_voidSetPortDirection (LCD_Data_Pins_Port,OUTPUT);

    // RS = 0
    DIO_voidSetPinValue(LCD_Control_Pins_Port,RS_Pin,LOW);

    // RW = 0
    DIO_voidSetPinValue(LCD_Control_Pins_Port,RW_Pin,LOW);

    // En = 1
    DIO_voidSetPinValue (LCD_Control_Pins_Port,EN_Pin,HIGH);

    // DB0 : DB7 Value = Command Code
    DIO_voidSetPortValue (LCD_Data_Pins_Port,Copy_command);

    // En = 0
    DIO_voidSetPinValue (LCD_Control_Pins_Port,EN_Pin,LOW);

    _delay_ms(2);



}


/***********************************************************************************************************************************/
/* Function Name    : LCD_voidWriteData
*  Function return  : void
*  Function Inputs  : Character you wanna print
*  Character Input  : you can write the char. direct OR Binary number represent this char.
/***********************************************************************************************************************************/
void LCD_voidWriteData (u8 Copy_Character)
{

    // RS Direction = OUTPUT
    DIO_voidSetPinDirection(LCD_Control_Pins_Port,RS_Pin,OUTPUT);

    // RW Direction = OUTPUT
    DIO_voidSetPinDirection(LCD_Control_Pins_Port,RW_Pin,OUTPUT);

    // Enable Direction = OUTPUT
    DIO_voidSetPinDirection(LCD_Control_Pins_Port,EN_Pin,OUTPUT);

    // DB0 : DB7 Direction = OUTPUT
    DIO_voidSetPortDirection (LCD_Data_Pins_Port,OUTPUT);

    // set RS = 1
    DIO_voidSetPinValue(LCD_Control_Pins_Port,RS_Pin,HIGH);

    // set RW = 0
    DIO_voidSetPinValue(LCD_Control_Pins_Port,RW_Pin,LOW);

    // En = 1
    DIO_voidSetPinValue (LCD_Control_Pins_Port,EN_Pin,HIGH);

    // DB0 : DB7 Value = Command Code
    DIO_voidSetPortValue (LCD_Data_Pins_Port,Copy_Character);

    // En = 0
    DIO_voidSetPinValue (LCD_Control_Pins_Port,EN_Pin,LOW);

    _delay_ms(2);



}


/***********************************************************************************************************************************/
/* Function Name    : LCD_voidGoToPosition--> used to move cursor to any position
*  Function return  : void
*  Function Inputs  : Line & Position
*  Line Input       : LINE1 or LINE2
*  Position Input   : 0 : 15
/***********************************************************************************************************************************/
void LCD_voidGoToPosition (u8 Copy_Line,u8 Copy_pos)
{

    if (Copy_pos >= 0 && Copy_pos <= 15){

        switch (Copy_Line){
    
            case LINE1 :

            LCD_voidWriteCommand (0x80 + Copy_pos);

            break;

            case LINE2 :

            LCD_voidWriteCommand (0xc0 + Copy_pos);

            break;
        }
    
    
    
    }else{

        // DO NOTHING
    }


}


/***********************************************************************************************************************************/
/* Function Name    : LCD_voidWriteString
*  Function return  : void
*  Function Inputs  : pointer
*  Pointer Input    : array of characters
/***********************************************************************************************************************************/
void LCD_voidWriteString (u8 *ptr)
{

    u8 i = 0;

    while (ptr[i] != '\0')
    {

        LCD_voidWriteData (ptr[i]);
        i++;

    }

}


/***********************************************************************************************************************************/
/* Function Name    : LCD_voidWriteNumber
*  Function return  : void
*  Function Inputs  : Number
/***********************************************************************************************************************************/
void LCD_voidWriteNumber (u32 Copy_Number)
{

    u32 arr[20];
    u8 rem = 0, i = 0, j;
    if (Copy_Number == 0){
    	LCD_voidWriteData(0 + '0');
    }else{

    while (Copy_Number != 0)
    {

        rem = Copy_Number % 10;

        arr[i] = rem;

        i++;

        Copy_Number = Copy_Number / 10; 

    }

    i--;

    for (j=0;j<=i;j++){

        LCD_voidWriteData (arr[i-j] + '0');

    }
    }

}


/***********************************************************************************************************************************/
/* Function Name    : LCD_AddPatternsToCGRAM
*  Function return  : void
*  Function Inputs  : void
/***********************************************************************************************************************************/
void LCD_voidAddPatternsToCGRAM (void)
{
    u8 i;

    // Set Address to CGRAM
    LCD_voidWriteCommand (Set_Address_To_CGRAM);

    // pattern 1
    for (i=0;i<8;i++){
    LCD_voidWriteData (arr_1[i]);
    }
    // pattern 2
    for (i=0;i<8;i++){
    LCD_voidWriteData (arr_2[i]);
    }

    // pattern 3
    for (i=0;i<8;i++){
    LCD_voidWriteData (arr_3[i]);
    }

    // pattern 4
    for (i=0;i<8;i++){
    LCD_voidWriteData (arr_4[i]);
    }

    // pattern 5
    for (i=0;i<8;i++){
    LCD_voidWriteData (arr_5[i]);
    }

    // pattern 6
    for (i=0;i<8;i++){
    LCD_voidWriteData (arr_6[i]);
    }

}


/***********************************************************************************************************************************/
/* Function Name    : LCD_WritePattern
*  Function return  : void
*  Function Inputs  : Number of pattern
*  Number of pattern: 0 : 7
/***********************************************************************************************************************************/
void LCD_voidWritePattern (u8 Copy_PatternNumber)
{

    if (Copy_PatternNumber >= 0  && Copy_PatternNumber <= 7)
    {

        LCD_voidWriteData (Copy_PatternNumber);
    }else{

        //DO Nothing
    }


}
