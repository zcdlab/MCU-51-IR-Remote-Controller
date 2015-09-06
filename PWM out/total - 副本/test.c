#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"	 	 
//Mini STM32开发板范例代码8
//PWM输出 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	 
#define uchar	unsigned	char
#define uint	unsigned	int 
void out0(void)
{

		
 	
	PWM_Init(9000,8);	 //不分频。PWM频率=72000/900/(8+1)=888hz
   
 		LED0_PWM_VAL=4500;	
			//0 out
	 
		 
}

void out1(void)
{

	PWM_Init(18000,8);	 //不分频。PWM频率=72000/900=444hz
   	
 	LED0_PWM_VAL=4500;//1 out	   
		  
		 
}

int main(void)
{	uchar addr[2]={0,0};
uint flag,j;	
 
		
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口


	 while(flag<2)
   {
          for(j = 0; j< 2 ; j++ )
    {	             
         if(addr[j] == 0)	    //地址码
      {	
      PWM_Init(9000,8);	 //不分频。PWM频率=72000/900/(8+1)=888hz
   
 		LED0_PWM_VAL=4500;	

      }
      else if (addr[j] == 1)
      {	   
       PWM_Init(18000,8);	 //不分频。PWM频率=72000/900=444hz
   	
 	LED0_PWM_VAL=4500;//1 out	 	    	
      }
      flag++;	
    }	    	  
   }
  
	
  
	 //sync();
	



	/* out0();
	 out1();
	 out0();
	 out1();
	 out0();
	 out1();//control bit
	 out1();
	 out0();
	 out1();
	 out0();
	 out1();
	 out0();
	 out1();
	 out0();//
	 		  */  
		 
	  
     	
	
}














