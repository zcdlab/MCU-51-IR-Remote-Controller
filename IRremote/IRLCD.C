/*************************************
*        ?? ??????           *
*				     *
*	??  ???????         *
*		                     *
* LED_D(?????) LED_W(?????)*
*                                    *
*        ?????? Ht6221         *
*   ??????«???51???»   *
*                                    *
*   http://591881218.qzone.qq.com/   *
*************************************/
#include<reg51.h>
#define uchar unsigned char 
#define uint unsigned int 
#define LED_W P2
#define LED_D P0

sbit IR=P3^2;

uchar irtime,startflag,bitnum,irpro_ok,irrece_ok,num;
uchar ircode[4];
uchar irdata[33];

void delay(uint z)
{
	uint x,y;
	for(x=0;x<z;x++)
		for(y=0;y<110;y++);
}
void act1()
{
P0=0xf0; 
delay(100);
P0=0x0f; 
delay(100);
}

void act2()
{
P0=0xaa; 
delay(100);
P0=0x55; 
delay(100);
}

void act3()
{

}

void act4()
{

}




void init()
{
	TMOD=0x02;
	TH0=0;
	TL0=0;
	ET0=1;
	TR0=1;

	IT0=1;
	EX0=1;

	EA=1;
	
	IR=1;
}


void irpro()
{
	uchar i,j,k=1;
	uchar value;
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			value=value>>1;
			if(irdata[k]>6)
			{
				value=value|0x80;
			}
			k++;
		}
		ircode[i]=value;
	}
	irpro_ok=1;
}

void irwork()
{
	switch(ircode[2])
	{
		case 0x45:num=1;break;
		case 0x46:num=2;break;
		case 0x47:num=3;break;
		case 0x44:num=4;break;
		case 0x40:num=5;break;
		case 0x43:num=6;break;
		case 0x07:num=7;break;
		case 0x15:num=8;break;
		case 0x09:num=9;break;
		case 0x16:num=10;break;
		case 0x19:num=11;break;
		case 0x0D:num=12;break;
		case 0x0C:num=13;break;
		case 0x18:num=14;break;
		case 0x5E:num=15;break;
		case 0x08:num=16;break;
		case 0x1C:num=17;break;
		case 0x5A:num=18;break;
		case 0x42:num=19;break;
		case 0x52:num=20;break;
		case 0x4A:num=21;break;
	}
}

void display()
{
	switch(num)
	{
		case 1:act1();break;
		case 2:act2();break;
		
	}

}



void main()
{
	init();
	while(1)
	{
		if(irrece_ok)
		{
			irrece_ok=0;
			irpro();
		}
		if(irpro_ok)
		{
			irpro_ok=0;
			irwork();
		}
		display();
	}
}

void timer0(void) interrupt 1
{
	irtime++;
}

void int0(void) interrupt 0
{
	if(startflag)
	{
		if(irtime>32)
		{
			bitnum=0;
		}
		irdata[bitnum]=irtime;
		irtime=0;
		bitnum++;
		if(bitnum==33)
		{
			startflag=0;
			bitnum=0;
			irrece_ok=1;
		}
	}
	else
	{
		startflag=1;
		irtime=0;
	}
}