/*    
*     Created in 10/9/2023
*     By : Ahmed Eldab3
*/

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H




#define                LINE1                0

#define                LINE2                1



/******************************************************|--------------|*****************************************************/
/******************************************************| LCD Commands |*****************************************************/
/******************************************************|--------------|*****************************************************/

#define                                     Clear_Display                                       0b00000001

#define                                     Return_Home                                         0b00000010

#define                                     Entry_Mode_Set                                      0b00000110

#define                                     Display_On_Off                                      0b00001100
           
#define                                     Cursor_Or_Display_Shift                             0b00010100
           
#define                                     Function_Set                                        0b00111100
           
#define                                     Set_Address_To_CGRAM                                0b01000000




/************************************************* Prototypes Of Functions *************************************************/


void LCD_voidGoToPosition (u8 Copy_Line,u8 Copy_pos);

void LCD_voidIitialize (void);

void LCD_voidWriteData (u8 Copy_Character);

void LCD_voidWriteCommand (u8 Copy_Command);

void LCD_voidWriteString (u8 *ptr);

void LCD_voidWriteNumber (u32 Copy_Number);

void LCD_voidAddPatternsToCGRAM (void);

void LCD_voidWritePattern (u8 Copy_PatternNumber);

u8 LCD_u8GetRow (void);

u8 LCD_u8GetColumn (void);

#endif
