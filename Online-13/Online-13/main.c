

#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"


#include "DIO_Inteface.h"
#include "MOTOR_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "KeyPad_Cfg.h"
#include "ADC_Interface.h"
#include "EX_Interrupt_Interface.h"
#include "Timers.h"

	
	int main(void)
	{
		  DIO_Init();
		  MOTOR_Init();
		  LCD_Init();
		  KEYPAD_Init();
		 u8 operation=0;
		u8 k;
		u8 flag_num1=0;
		u8 flag_num2=0;
		u8 flag_acculm=0;
		u8 flag=0;
		s32 num1=0;
		s32 num2=0;
		s32 result=0;
		
		while (1)
		{
			
			k=KEYPAD_GetKey();
			//  LCD_WriteChar(k);
			  
		  if (k!=NO_KEY){
			 
				  // clear screen 
		      if (k=='C')
				  {
					  LCD_ClearPosition(0,0,15);
					  LCD_ClearPosition(1,0,15);
					  LCD_GoTo(0,0);
					 flag_acculm=0;
					
				  }
				  
			  if (k>='0'&&k<='9'&&flag_num1==0)
				  {
					  
					  if (flag==0)
					  {
						  LCD_GoTo(0,0);
						  LCD_WriteString("       ");
						  LCD_GoTo(0,0);
						  flag=1;
					  }
					  num1=num1*10+(k-'0');
					  LCD_WriteChar(k);
					  
			  }else if(((k=='+')||(k=='-')||(k=='*')||(k=='/'))&&(flag_num2==0)){
					  flag_num1=1;
					   LCD_WriteChar(k);
					   operation=k;
					  	  
			  }else if (k>='0'&&k<='9')
			  {
				  flag_num2=1;
				  
				  num2=num2*10+(k-'0');
				  LCD_WriteChar(k);
				  
			  }  if (k=='=')
			  {
				  switch(operation){
					  	case '+':
					  	result=num1+num2;
					  	break;
					  	
					  	case '-':
					  	result=num1-num2;
					  	break;
					  	
					  	case '*':
					  	result=num1*num2;
					  	break;
					  	
					  	case '/':
					  	result=num1/num2;
					  	break;
					  
				  }
				  
				  LCD_GoTo(1,0);
				  LCD_WriteNumber(result);
				  LCD_WriteString("       ");
				   num1=0;
				   num2=0;
				   flag=0;
				  flag_num1=0;
				  flag_num2=0;
				  flag_acculm=1;
				 
				
				
			  }
			  
			  if ((flag_acculm==1)&&((k=='+')||(k=='-')||(k=='*')||(k=='/')))
			  {
				   
				  LCD_GoTo(0,0);
				  LCD_WriteString("          ");
				  LCD_GoTo(0,0);
				  LCD_WriteNumber(result);
				  LCD_WriteChar(k);
				 num1=result;
				
			  }
			  
				
			  }
					  
		}
	}
	

	
	