
   	typedef unsigned char BYTE;	//用BYTE代替unsigned char 
	typedef bit BOOL;  // 用BOOL代替bit 
		
	sbit LCD_RS = P2^6;  //复位端            
	sbit LCD_RW = P2^5;	 //写数据端
	sbit LCD_EP = P2^7;	 //使能端

	void delay1(int ms);
	BOOL lcd_bz();
	void lcd_wcmd(int cmd);
	void lcd_pos(BYTE pos);
	void lcd_wdat(BYTE dat);
	void lcd_init();