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

int main(void)
{		
 
		
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	PWM_Init(54000,2);	 //不分频。PWM频率=72000/900=80Khz
   	while(1)			 //理论算出为（9000，15）示波器显示为周期2.000ms
	{
 	LED0_PWM_VAL=13500;//1 out	   
	}	 					
	
     	
	
}

























