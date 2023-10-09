/*    
*     Created in 6/9/2023
*     By : Ahmed Eldab3
*/
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/*Definitions of ports*/
#define  PORTA      0
#define  PORTB      1
#define  PORTC      2
#define  PORTD      3

/*Definitions of pins*/
#define PIN0        0
#define PIN1        1
#define PIN2        2
#define PIN3        3
#define PIN4        4
#define PIN5        5
#define PIN6        6
#define PIN7        7

/*Other Definitions*/
#define INPUT       0
#define OUTPUT      1
 
#define LOW         0
#define HIGH        1

/*Prototypes of functions*/

void DIO_voidSetPinDirection (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber , u8 Copy_u8Direction); 

void DIO_voidSetPinValue (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber, u8 Copy_u8Value);

u8 DIO_u8GetPinValue (u8 Copy_u8PortNumber , u8 Copy_u8PinNumber);

void DIO_voidSetPortDirection (u8 Copy_u8PortNumber , u8 Copy_u8Direction);

void DIO_voidSetPortValue (u8 Copy_u8PortNumber ,u8 Copy_u8Value);

#endif