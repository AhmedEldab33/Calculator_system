/*    
*     Created in 17/9/2023
*     By : Ahmed Eldab3
*/

#ifndef KPAD_CONFIG_H
#define KPAD_CONFIG_H

/*This File contents can be edited by the user*/

#define      KPAD_PORT       PORTD

#define      R0                0
#define      R1                1
#define      R2                2
#define      R3                3

#define      C0                4
#define      C1                5
#define      C2                6
#define      C3                7

#define   KPAD_ROW_INIT	       0
#define   KPAD_ROW_END	       3

#define   KPAD_COL_INIT	       4
#define   KPAD_COL_END	       7

u8	KPAD_Au8Keys[4][4]	=	{	{'1','2','3','+'},
								{'4','5','6','-'},
								{'7','8','9','/'},
								{'.','0','=','C'}
};

u8	KPAD_Au8Keyss[4][4]	=	{	{7,8,9,12},
								{4,5,6,13},
								{1,2,3,11},
								{15,0,14,10}
};


#endif
