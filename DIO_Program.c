/*    
*     Created in 6/9/2023
*     By : Ahmed Eldab3
*/


/*****************************************************|----------------------|*******************************************************/
/*****************************************************| Digital Input Output |*******************************************************/
/*****************************************************|----------------------|*******************************************************/

#include "../../LIB/Bit_utils.h"
#include "../../LIB/Std_types.h"

#include "DIO_Interface.h"
#include "DIO_Config.h"
#include "DIO_Private.h"

/***********************************************************************************************************************************/
/* Function Name   : DIO_voidSetPinDirection
*  Function return : void
*  Function Inputs : PortNumber & PinNumber & Direction
*  PortNumber input: PORTA or PORTB or PORTC or PORTD
*  PinNumber input : 0 : 7
*  Direction input : OUTPUT or INPUT
/***********************************************************************************************************************************/
void DIO_voidSetPinDirection (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber , u8 Copy_u8Direction)
{
    switch(Copy_u8Direction)
    {
        case OUTPUT : 
                        switch(Copy_u8PortNumber)
                        {
                            case PORTA : SET_BIT(DDRA_REG,Copy_u8PinNumber); break;
                            case PORTB : SET_BIT(DDRB_REG,Copy_u8PinNumber); break;
                            case PORTC : SET_BIT(DDRC_REG,Copy_u8PinNumber); break;
                            case PORTD : SET_BIT(DDRD_REG,Copy_u8PinNumber); break;
                        }
                        break;
        case INPUT  : 
                        switch(Copy_u8PortNumber)
                        {
                            case PORTA : CLR_BIT(DDRA_REG,Copy_u8PinNumber); break;
                            case PORTB : CLR_BIT(DDRB_REG,Copy_u8PinNumber); break;
                            case PORTC : CLR_BIT(DDRC_REG,Copy_u8PinNumber); break;
                            case PORTD : CLR_BIT(DDRD_REG,Copy_u8PinNumber); break;
                        }
                        break;
        default :       break;
    }
}

/***********************************************************************************************************************************/
/* Function Name   : DIO_voidSetPinValue
*  Function return : void
*  Function Inputs : PortNumber & PinNumber & Value
*  PortNumber input: PORTA or PORTB or PORTC or PORTD
*  PinNumber input : 0 : 7
*  Value input     : HIGH or LOW
/***********************************************************************************************************************************/
void DIO_voidSetPinValue (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber, u8 Copy_u8Value)
{
    switch(Copy_u8Value)
    {
        case HIGH : 
                        switch(Copy_u8PortNumber)
                        {
                            case PORTA : SET_BIT(PORTA_REG,Copy_u8PinNumber); break;
                            case PORTB : SET_BIT(PORTB_REG,Copy_u8PinNumber); break;
                            case PORTC : SET_BIT(PORTC_REG,Copy_u8PinNumber); break;
                            case PORTD : SET_BIT(PORTD_REG,Copy_u8PinNumber); break;
                        }
                        break;
        case LOW  : 
                        switch(Copy_u8PortNumber)
                        {
                            case PORTA : CLR_BIT(PORTA_REG,Copy_u8PinNumber); break;
                            case PORTB : CLR_BIT(PORTB_REG,Copy_u8PinNumber); break;
                            case PORTC : CLR_BIT(PORTC_REG,Copy_u8PinNumber); break;
                            case PORTD : CLR_BIT(PORTD_REG,Copy_u8PinNumber); break;
                        }
                        break;
        default :       break;
    }
}

/***********************************************************************************************************************************/
/* Function Name   : DIO_u8GetPinValue
*  Function return : u8
*  Function Inputs : PortNumber & PinNumber 
*  PortNumber input: PORTA or PORTB or PORTC or PORTD
*  Direction input : 0 : 7
/***********************************************************************************************************************************/
u8 DIO_u8GetPinValue (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber)
{
    u8 Local_u8Value ;
    switch(Copy_u8PortNumber)
    {
        case PORTA : Local_u8Value = GET_BIT(PINA_REG,Copy_u8PinNumber); break;
        case PORTB : Local_u8Value = GET_BIT(PINB_REG,Copy_u8PinNumber); break;
        case PORTC : Local_u8Value = GET_BIT(PINC_REG,Copy_u8PinNumber); break;
        case PORTD : Local_u8Value = GET_BIT(PIND_REG,Copy_u8PinNumber); break;
    }
    return Local_u8Value ;
}

/***********************************************************************************************************************************/
/* Function Name   : DIO_voidSetPortDirection
*  Function return : void
*  Function Inputs : PortNumber & Direction 
*  PortNumber input: PORTA or PORTB or PORTC or PORTD
*  Direction input : INPUT or OUTPUT
/***********************************************************************************************************************************/
void DIO_voidSetPortDirection (u8 Copy_u8PortNumber , u8 Copy_u8Direction)
{
    switch(Copy_u8Direction)
    {
        case OUTPUT : 
                        switch(Copy_u8PortNumber)
                        {
                            case PORTA : DDRA_REG = 0xFF; break;
                            case PORTB : DDRB_REG = 0xFF; break;
                            case PORTC : DDRC_REG = 0xFF; break;
                            case PORTD : DDRD_REG = 0xFF; break;
                        }
                        break;
        case INPUT  : 
                        switch(Copy_u8PortNumber)
                        {
                            case PORTA : DDRA_REG = 0x00; break;
                            case PORTB : DDRB_REG = 0x00; break;
                            case PORTC : DDRC_REG = 0x00; break;
                            case PORTD : DDRD_REG = 0x00; break;
                        }
                        break;
        default :       break;
    }
}

/***********************************************************************************************************************************/
/* Function Name   : DIO_voidsetPortValue
*  Function return : void
*  Function Inputs : PortNumber & Value 
*  PortNumber input: PORTA or PORTB or PORTC or PORTD
*  Value input     : HIGH or LOW
/***********************************************************************************************************************************/
void DIO_voidSetPortValue (u8 Copy_u8PortNumber ,u8 Copy_u8Value)
{
    switch(Copy_u8PortNumber)
    {
        case PORTA : PORTA_REG = Copy_u8Value; break;
        case PORTB : PORTB_REG = Copy_u8Value; break;
        case PORTC : PORTC_REG = Copy_u8Value; break;
        case PORTD : PORTD_REG = Copy_u8Value; break;
    }
}