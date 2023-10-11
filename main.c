/*    
*     Created in 6/9/2023
*     By : Ahmed Eldab3
*/

#include "../LIB/Bit_utils.h"
#include "../LIB/Std_types.h"

#define F_CPU 1000000
#include "util/delay.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/INT/INT_Interface.h"
#include "../HALL/SSD/SSD_Interface.h"
#include "../HALL/LCD/LCD_Interface.h"
#include "../HALL/KPAD/KPAD_Interface.h"


void calc_reset(void);
u16 calcArr_1 (u8 NumArr[],u8 i);
f32 calcArr_2 (u8 NumArr[],u8 i);
u8 pow (u8 x, u8 y);

int main (){
	u8 number_1[3] = {0}, number_2[2] = {0},number_3[3] = {0},number_4[2] = {0},number[3] ,next_num=0,op=0, num = 0, ans = 0, remm[8];
	f32 num_2 = 0, num_4 = 0;
	u16 num_1 = 0, num_3 = 0;
	u8 rem[8] = {0};
	s8 j = 8, i = 0, k = 0, p = 9, h = 0, m = 0, n = 0;
	u8 Local_pressed;
	LCD_voidIitialize();
	KPAD_voidInitialize();
	LCD_voidGoToPosition(LINE1,0);
	LCD_voidWriteString("Welcome..Ahmed");
	_delay_ms(500);
	LCD_voidWriteCommand(Clear_Display);
    while(1){
    	LCD_voidGoToPosition(LINE1,0);
    	LCD_voidWriteString("1)CalcMode");
    	LCD_voidGoToPosition(LINE2,0);
    	LCD_voidWriteString("2)NumberingMode");
    	Local_pressed = KPAD_u8GetPressed();
    	switch (Local_pressed){

    	case 1 :
    	LCD_voidWriteCommand(Clear_Display);

    	while (1){
    		Local_pressed = KPAD_u8GetPressed();
    		if (Local_pressed != 255){

    			if (Local_pressed != 10 && Local_pressed != 11 && Local_pressed != 12 && Local_pressed != 13 && Local_pressed != 14 && Local_pressed != 15 && num_1 ==0 && next_num==0 ){
    					number_1[i] = Local_pressed;
    					LCD_voidWriteNumber(number_1[i]);
    					i++;
    			}
    			if (Local_pressed == 15 && next_num==0){
    					LCD_voidWriteData('.');
    					next_num = 1;
    			}
    			if (Local_pressed != 10 && Local_pressed != 11 && Local_pressed != 12 && Local_pressed != 13 && Local_pressed != 14 && Local_pressed != 15 && next_num==1 ){
    		       		number_2[h] = Local_pressed;
    		       		LCD_voidWriteNumber(number_2[h]);
    		       		h++;
    			}
    			if(Local_pressed == 10){
    					num_1 = calcArr_1(number_1,i);
    					num_2 = calcArr_2(number_2,h);
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					LCD_voidWriteData('+');
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					next_num = 2;
    					op = 0;
    			}
    			if(Local_pressed == 11){
    					num_1 = calcArr_1(number_1,i);
    					num_2 = calcArr_2(number_2,h);
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					LCD_voidWriteData('-');
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					next_num = 2;
    					op = 1;
    			}
    			if(Local_pressed == 13){
    					num_1 = calcArr_1(number_1,i);
    					num_2 = calcArr_2(number_2,h);
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					LCD_voidWriteData('*');
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					next_num = 2;
    					op = 2;
    			}
    			if(Local_pressed == 12){
    					num_1 = calcArr_1(number_1,i);
    					num_2 = calcArr_2(number_2,h);
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					LCD_voidWriteData('/');
    					LCD_voidWriteCommand(Cursor_Or_Display_Shift);
    					next_num = 2;
    					op = 3;
    			}
    			if (Local_pressed != 10 && Local_pressed != 11 && Local_pressed != 12 && Local_pressed != 13 && Local_pressed != 14 && Local_pressed != 15 && next_num==2 ){
    					number_3[m] = Local_pressed;
    					LCD_voidWriteNumber(number_3[m]);
    					m++;

    			}
    			if (Local_pressed == 15 && next_num==2){
    					LCD_voidWriteData('.');
    					next_num = 3;
    			}
    			if (Local_pressed != 10 && Local_pressed != 11 && Local_pressed != 12 && Local_pressed != 13 && Local_pressed != 14 && Local_pressed != 15 && next_num==3 ){
    					number_4[n] = Local_pressed;
    					LCD_voidWriteNumber(number_4[n]);
    					n++;
    			}
    			if (Local_pressed == 14){
    					next_num = 4;
    					num_3 = calcArr_1(number_3,m);
    					num_4 = calcArr_2(number_4,n);
    					LCD_voidGoToPosition(LINE2,7);
    					LCD_voidWriteData('=');
    					LCD_voidGoToPosition(LINE2,8);
    					u16 result = 0;
    					f32 dec = 0;
    					u16 flt = 0;
    					switch (op){
    					case 0 :
    						result = num_1 + num_2 + num_3 + num_4;
    						dec = num_1 + num_2 + num_3 + num_4;
    						flt = (dec - result) * 1000;
    						LCD_voidWriteNumber(result);
    						LCD_voidWriteData('.');
    						LCD_voidWriteNumber(flt);
    					break;
    					case 1 :
    						if (num_3 > num_1 ){
    							result = (num_3 + num_4) - (num_1 + num_2);
    							dec = (num_3 + num_4) - (num_1 + num_2);
    							flt = (dec - result) * 1000;
    							LCD_voidWriteData('-');
    						}else{
    							result = - (num_3 + num_4) + (num_1 + num_2);
    							dec = - (num_3 + num_4) + (num_1 + num_2);
    							flt = (dec - result) * 1000;
    						}
    						LCD_voidWriteNumber(result);
    						LCD_voidWriteData('.');
    						LCD_voidWriteNumber(flt);
    					break;
    					case 2 :
    						result = (num_1 * num_3) + (num_1 * num_4) + (num_2 * num_3) + (num_2 * num_4);
    						dec = (num_1 * num_3) + (num_1 * num_4) + (num_2 * num_3) + (num_2 * num_4);
    						flt = (dec - result) * 1000;
    						LCD_voidWriteNumber(result);
    						LCD_voidWriteData('.');
    						LCD_voidWriteNumber(flt);
    					break;
    					case 3 :
    						if (num_3 == 0 && num_4 ==0){
    							LCD_voidGoToPosition(LINE2,6);
    							LCD_voidWriteString("Math Error");
    						}else if (num_2==0 && num_4==0){
    							result = num_1/ num_3;
    							dec = (f32)num_1 / num_3;
    							flt = (dec - result)*1000;
    							LCD_voidWriteNumber(result);
    							LCD_voidWriteData('.');
    							LCD_voidWriteNumber(flt);
    						}else {
    							result = (num_1 + num_2)/ (num_3 + num_4);
    							dec = ((f32)num_1 + num_2)/ ((f32)num_3 + num_4);
    							flt = (dec - result)*1000;
    							LCD_voidWriteNumber(result);
    							LCD_voidWriteData('.');
    							LCD_voidWriteNumber(flt);
    						}

    					break;
    				}
    			}
    			if (Local_pressed == 15 && next_num==4){
    			    	LCD_voidWriteCommand(Clear_Display);
    			    	num_1=0;
    			      	num_2=0;
    			      	num_3=0;
    			     	num_4=0;
    			      	next_num=0;
    			    	op=0;
    			    	i = 0;
    			    	h = 0;
    			    	m = 0;
    			    	n = 0;
    			    	for (u8 i=0;i<3;i++){
    			    		number_1[i] = 0;
    			    		number_3[i] = 0;
    			    	}
    			    	for (u8 i=0;i<2;i++){
    			    		number_2[i] = 0;
    			    		number_4[i] = 0;
    			    	}
    			}
    		}
    	}
    		break;

    	case 2:
    		LCD_voidWriteCommand(Clear_Display);
    		LCD_voidGoToPosition(LINE1,0);
        	LCD_voidWriteString("1)Dicimal-Binary");
        	LCD_voidGoToPosition(LINE2,0);
    		LCD_voidWriteString("2)Binary-Dicimal");
    		while (1){
    		Local_pressed = KPAD_u8GetPressed();
    			switch (Local_pressed){

    			case 1 :

    				LCD_voidWriteCommand(Clear_Display);
    				LCD_voidGoToPosition(LINE1,0);
    				LCD_voidWriteString("Dicimal =");
    				LCD_voidGoToPosition(LINE2,0);
    				LCD_voidWriteString("Binary =");
    				while (1){
    					Local_pressed = KPAD_u8GetPressed();
    					if (Local_pressed != 255 && Local_pressed != 15 && Local_pressed != 14){
    						number[k] = Local_pressed;
    						LCD_voidGoToPosition(LINE1,p);
    						LCD_voidWriteNumber(number[k]);
    						k++;
    						p++;
    					}
    					if (Local_pressed == 14 && Local_pressed != 255){
    						num = calcArr_1(number,k);
    						while (num != 0){
    							rem[7-i] = num % 2;
    							num = num / 2;
    							i++;
    						}
    						for (u8 i=0;i<8;i++){

    							LCD_voidGoToPosition(LINE2,j);
    							LCD_voidWriteNumber(rem[i]);
    							j++;
    						}
    					}
    					if(Local_pressed == 15 && Local_pressed != 255){
    						LCD_voidWriteCommand(Clear_Display);
    						LCD_voidGoToPosition(LINE1,0);
    						LCD_voidWriteString("Dicimal =");
    						LCD_voidGoToPosition(LINE2,0);
    						LCD_voidWriteString("Binary =");
    						i = 0;
    						num = 0;
    						k = 0;
    						p = 9;
    						j = 8;
    						for (u8 l = 0;l<8;l++){
    							rem[l] = 0;
    						}
    					}
    				}
    			break;
    		case 2 :

    			LCD_voidWriteCommand(Clear_Display);
    			LCD_voidGoToPosition(LINE1,0);
    			LCD_voidWriteString("Binary =");
    			LCD_voidGoToPosition(LINE2,0);
    			LCD_voidWriteString("Dicimal =");
    			while (1){
    				Local_pressed = KPAD_u8GetPressed();

    				if (Local_pressed != 255 && Local_pressed != 15 && Local_pressed != 14){

    						remm[i] = Local_pressed;
    						LCD_voidGoToPosition(LINE1,j);
    						LCD_voidWriteNumber(remm[i]);
    						i++;
    						j++;
    				}

    				if (Local_pressed != 255 && Local_pressed == 14){
    					for (i=0;i<8;i++){

    					    ans = ans + (remm[7-i] * pow(2,i));

    					}
    					LCD_voidGoToPosition(LINE2,9);
    					LCD_voidWriteNumber(ans);
    				}

    				if(Local_pressed == 15 && Local_pressed != 255){
    				    	LCD_voidWriteCommand(Clear_Display);
    				    	LCD_voidGoToPosition(LINE1,0);
    				    	LCD_voidWriteString("Binary =");
    				    	LCD_voidGoToPosition(LINE2,0);
    				    	LCD_voidWriteString("Dicimal =");
    				    	ans = 0;
    				    	i = 0;
    				    	j = 8;
    				}
    			}
    			break;
    		}
    	}
    		break;
    }

   }


}

u8 pow (u8 x, u8 y){
	u8 result = x;
	if (y==0){
		return 1;
	}else{
	for (u8 i=1;i<y;i++){

		result *= x;
	}
	return result;
	}
}

u16 calcArr_1 (u8 NumArr[],u8 i){


	u64 result = 0;
	switch (i){
	case 1 :
		result = NumArr[0];
		break;
	case 2 :
		result = NumArr[0]*10 + NumArr[1];
		break;
	case 3 :
		result = NumArr[0]*100 +NumArr[1]*10 + NumArr[2];
		break;

	}
	return result;
}

f32 calcArr_2 (u8 NumArr[],u8 i){


	f32 result = 0;
	switch (i){
	case 1 :
		result = NumArr[0]*0.1 ;
		break;
	case 2 :
		result = NumArr[0]*0.1 + NumArr[1]*0.01;
		break;

	}
	return result;
}

