#include <reg51.h>
#include <intrins.h>
#include "1602.h"
//#include "key.h"
#define uchar unsigned char
#define uint  unsigned int
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
void keyscan();
void delay(uchar x);  //x*0.14MS
void delay1(int ms);
void beep();
void IR_IN();
sbit IRIN = P3^2;         //红外接收器数据线
sbit BEEP = P1^5;         //蜂鸣器驱动线
sbit RELAY= P1^4;         //继电器驱动线
unsigned char code LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};

uchar IRCOM[8];
uchar IRAddr[2];
uchar IRRev[8];
uint key=10;

uchar code  cdis1[ ] = {"  IR-addr: --H  "};
uchar code  cdis2[ ] = {"  IR-ctrl: --H  "};


/*******************************************************************/
main()
{
 uchar m;
    P2=0xff;
    IRIN=1;                    //I/O口初始化
    BEEP=1;
    RELAY=1; 
	
    delay1(10);                 //延时
    lcd_init();                //初始化LCD             
        
    lcd_pos(0);                //设置显示位置为第一行的第1个字符

     m = 0;
    while(cdis1[m] != '\0')
     {                         //显示字符
       lcd_wdat(cdis1[m]);
       m++;
     }

    lcd_pos(0x40);             //设置显示位置为第二行第1个字符
     m = 0;
    while(cdis2[m] != '\0')
     {
       lcd_wdat(cdis2[m]);      //显示字符
       m++;
     }


	IE = 0x81;                 //允许总中断中断,使能 INT0 外部中断
	TCON = 0x01;               //触发方式为脉冲负边沿触发
  while(1)
	{
	
		keyscan();
 
	delay(10);
    	switch(key)								   //读出对应值
		{
					
			case 1:P1= 0x08;break;
			case 2:P1= 0x3f;break;
			case 3:P1= 0x2d;break;
			case 4:P1= 0x08;break;
			case 5:P1= 0x10;break;
			case 6:P1= 0x20;break;
			case 7:P1= 0x40;break;
			case 8:P1= 0x80;break;
			default:break; 
		 
		}  
}
}//end main
/**********************************************************/
void IR_IN() interrupt 0 using 0
{
  unsigned char j,k,N=0;
     EX0 = 0;   
	 delay(15);
	 if (IRIN==1) 
     { EX0 =1;
	   return;
	  } 
                           //确认IR信号出现
  while (!IRIN)            //等IR变为高电平，跳过9ms的前导低电平信号。
    {delay(1);}

 for (j=0;j<4;j++)         //收集四组数据
 { 
  for (k=0;k<8;k++)        //每组数据有8位
  {
   while (IRIN)            //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
     {delay(1);}
    while (!IRIN)          //等 IR 变为高电平
     {delay(1);}
     while (IRIN)           //计算IR高电平时长
      {
    delay(1);
    N++;           
    if (N>=30)
	 { EX0=1;
	 return;}                  //0.14ms计数过长自动离开。
      }                        //高电平计数完毕                
     IRCOM[j]=IRCOM[j] >> 1;                  //数据最高位补“0”
     if (N>=8) {IRCOM[j] = IRCOM[j] | 0x80;}  //数据最高位补“1”
     N=0;
  }//end for k
 }//end for j
   
    if (IRCOM[0]!=~IRCOM[1])
   { EX0=1;
     return; }
 
 
   if (IRCOM[2]!=~IRCOM[3])
   { EX0=1;
     return; }

   IRCOM[4]=IRCOM[0] & 0x0F;     //取键码的低四位
   IRCOM[5]=IRCOM[0] >> 4;       //右移4次，高四位变为低四位
    IRCOM[6]=IRCOM[2] & 0x0F; 
   IRCOM[7]=IRCOM[2] >> 4;     
		 if(IRCOM[4]>9)
    { IRCOM[4]=IRCOM[4]+0x37;}
   else
	  IRCOM[4]=IRCOM[4]+0x30;

   if(IRCOM[5]>9)
    { IRCOM[5]=IRCOM[5]+0x37;}
   else
	  IRCOM[5]=IRCOM[5]+0x30;

	 if(IRCOM[6]>9)
    { IRCOM[6]=IRCOM[6]+0x37;}
   else
	  IRCOM[6]=IRCOM[6]+0x30;

   if(IRCOM[7]>9)
    { IRCOM[7]=IRCOM[7]+0x37;}
   else
	  IRCOM[7]=IRCOM[7]+0x30;
     
	   lcd_pos(0x0b);             
     lcd_wdat(IRCOM[5]);        //第一位数显示 
     lcd_pos(0x0c);             
     lcd_wdat(IRCOM[4]);        //第二位数显示

     lcd_pos(0x4b);             
     lcd_wdat(IRCOM[7]);        //第一位数显示 
     lcd_pos(0x4c);             
     lcd_wdat(IRCOM[6]);        //第二位数显示
     
     beep();
	   IRAddr[0]=IRCOM[4];
	   IRAddr[1]=IRCOM[5];
	 
  
     EX0 = 1; 
} 

/**********************************************************/
void beep()
{
  unsigned char i;
  for (i=0;i<100;i++)
   {
   delay(4);
   BEEP=!BEEP;                 
   } 
  BEEP=1;                     
}
/**********************************************************/
void delay(unsigned char x)    //x*0.14MS
{
 unsigned char i;
  while(x--)
 {
  for (i = 0; i<13; i++) {}
 }
}

/**********************************************************/

void keyscan()							 //按键检测函数
{
	if(P2== 0xfe)
		key= 1;
	if(P2== 0xfd)
		key= 2;
	if(P2== 0xfb)
		key= 3;
	if(P2== 0xf7)
		key= 4;
	if(P2== 0xef)
		key= 5;
	if(P2== 0xdf)
		key= 6;
	if(P2== 0xbf)
		key= 7;
	if(P2== 0x7f)
		key= 8;

}
