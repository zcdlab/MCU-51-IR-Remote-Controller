
	#include <reg51.h>	//51寄存器文件
	#include <intrins.h>
	#include"1602.h"
/****************延时函数************************/	
	void delay1(int ms)
	{                    //延时子程序
	int i;
	while(ms--)
	{
	  for(i = 0; i< 250; i++)
	  {
	   _nop_();	  //空执行
	   _nop_();
	   _nop_();
	   _nop_();
	  }
	}
	}

/****************侧忙函数************************/		
	BOOL lcd_bz()
	{                         
	BOOL result;
	LCD_RS = 0;
	LCD_RW = 1;
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	result = (BOOL)(P0 & 0x80);	 //检测P0最高位是否为1
	LCD_EP = 0;
	return result;//返回侧忙结果
	}

/****************写命令函数************************/
		
	void lcd_wcmd_8bit(int cmd)
	{                          // 写入指令数据到LCD
	while(lcd_bz());
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EP = 0;
	_nop_();
	_nop_(); 
	P0 = cmd; //将高4位位指令通过P0口传给1602
	_nop_();
	_nop_(); //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0;  
	}	
		
	void lcd_wcmd(int cmd)
	{                          // 写入指令数据到LCD
	while(lcd_bz());
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_EP = 0;
	_nop_();
	_nop_(); 
	P0 = cmd; //将高4位位指令通过P0口传给1602
	_nop_();
	_nop_(); //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0;  
	P0 = (cmd&0x0f)<<4; //将低4位指令通过P0口传给1602
	_nop_();
	_nop_(); //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0;  
	}
	
	void lcd_pos(BYTE pos)
	{                          //设定显示位置
	lcd_wcmd(pos | 0x80);
	}

/****************写数据函数************************/	
	void lcd_wdat(BYTE dat) 
	{                   //写入字符显示数据到LCD
	while(lcd_bz());
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EP = 0;
	P0 = dat ;  //将高4位数据通过P0口传给1602
	_nop_();
	_nop_();   //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0; 

	LCD_RS = 1;
	LCD_RW = 0;
	LCD_EP = 0;
		_nop_();
	_nop_();
	_nop_();
	_nop_();
	P0 = (dat&0x0f)<<4;  //将低4位位数据通过P0口传给1602
	_nop_();
	_nop_();   //用于产生一个脉冲宽度
	_nop_();
	_nop_();
	LCD_EP = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	LCD_EP = 0; 
	}
	
	void lcd_init()					//LCD初始化设定
	{ 
    lcd_wcmd_8bit(0x38);                       //16*2显示，5*7点阵，8位数据
	delay1(1);  
	lcd_wcmd_8bit(0x38);                       //16*2显示，5*7点阵，8位数据
	delay1(1);  
	lcd_wcmd_8bit(0x28);     //16*2显示，5*7点阵，8位数据
	delay1(1);  
	lcd_wcmd(0x28);
	delay1(1);
  	lcd_wcmd(0x0c);     //显示开，关光标
	delay1(1);
   	lcd_wcmd(0x02);     //显示开，关光标
	delay1(1);
   	lcd_wcmd(0x01);     //清除LCD的显示内容
	delay1(1);



/*	lcd_wcmd(0x38);     //16*2显示，5*7点阵，8位数据
	delay(1);
	lcd_wcmd(0x08);     //显示开，关光标
	delay(1);
//	lcd_wcmd(0x04);     //移动光标
	delay(1);
	lcd_wcmd(0x02);     // 4位选择
	delay(1);
	lcd_wcmd(0x01);     //清除LCD的显示内容
	delay(1); */
	}