/*
  LCD5110_Graph.cpp - Arduino/chipKit library support for Nokia 5110 compatible LCDs
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  Basic functionality of this library are based on the demo-code provided by
  ITead studio. You can find the latest version of the library at
  http://www.RinkyDinkElectronics.com/

  This library has been made to make it easy to use the Nokia 5110 LCD module 
  as a graphics display on an Arduino or a chipKit.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#include "LCD5110_Graph.h"
#include "stdlib.h"


#include "nokia5110/HW_ARM.h"


void _LCD_Write(unsigned char data, unsigned char mode)
{   
    //cbi(P_CS, B_CS);

	if (mode==LCD_COMMAND)
		//cbi(P_DC, B_DC);
        DC_Write(0);
	else
		//sbi(P_DC, B_DC);
        DC_Write(1);

//    char c;
//	for (c=0; c<8; c++)
//	{
//		if (data & 0x80)
//			sbi(P_MOSI, B_MOSI);
//		else
//			cbi(P_MOSI, B_MOSI);
//		data = data<<1;
//		pulseClock;
//	}
    CE_Write(0);
//    SPIM_WriteTxData(data);
    SwSPI_Master_SendByte(data);
    CE_Write(1);

	//sbi(P_CS, B_CS);
}

void InitLCD(int contrast)
{
//    SPIM_Start();
    
	if (contrast>0x7F)
		contrast=0x7F;
	if (contrast<0)
		contrast=0;

	resetLCD;

	_LCD_Write(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION, LCD_COMMAND);
	_LCD_Write(PCD8544_SETVOP | contrast, LCD_COMMAND);
	_LCD_Write(PCD8544_SETTEMP | LCD_TEMP, LCD_COMMAND);
	_LCD_Write(PCD8544_SETBIAS | LCD_BIAS, LCD_COMMAND);
	_LCD_Write(PCD8544_FUNCTIONSET, LCD_COMMAND);
	_LCD_Write(PCD8544_SETYADDR, LCD_COMMAND);
	_LCD_Write(PCD8544_SETXADDR, LCD_COMMAND);
	_LCD_Write(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL, LCD_COMMAND);

	clrScr();
	update();
	cfont.font=0;
	_sleep=false;
	_contrast=contrast;
}

void setContrast(int contrast)
{
	if (contrast>0x7F)
		contrast=0x7F;
	if (contrast<0)
		contrast=0;
	_LCD_Write(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION, LCD_COMMAND);
	_LCD_Write(PCD8544_SETVOP | contrast, LCD_COMMAND);
	_LCD_Write(PCD8544_FUNCTIONSET, LCD_COMMAND);
	_contrast=contrast;
}

void enableSleep()
{
	_sleep = true;
	_LCD_Write(PCD8544_SETYADDR, LCD_COMMAND);
	_LCD_Write(PCD8544_SETXADDR, LCD_COMMAND);
    int b;
	for (b=0; b<504; b++)
		_LCD_Write(0, LCD_DATA);
	_LCD_Write(PCD8544_FUNCTIONSET | PCD8544_POWERDOWN, LCD_COMMAND);
}

void disableSleep()
{
	_sleep = false;
	_LCD_Write(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION, LCD_COMMAND);
	_LCD_Write(PCD8544_SETVOP | _contrast, LCD_COMMAND);
	_LCD_Write(PCD8544_SETTEMP | LCD_TEMP, LCD_COMMAND);
	_LCD_Write(PCD8544_SETBIAS | LCD_BIAS, LCD_COMMAND);
	_LCD_Write(PCD8544_FUNCTIONSET, LCD_COMMAND);
	_LCD_Write(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL, LCD_COMMAND);
	update();
}

void update()
{
	if (_sleep==false)
	{
		_LCD_Write(PCD8544_SETYADDR, LCD_COMMAND);
		_LCD_Write(PCD8544_SETXADDR, LCD_COMMAND);
        int b;
		for (b=0; b<504; b++)
			_LCD_Write(scrbuf[b], LCD_DATA);
	}
}

void clrScr()
{
    int c;
	for (c=0; c<504; c++)
		scrbuf[c]=0;
}

void fillScr()
{
    int c;
	for (c=0; c<504; c++)
		scrbuf[c]=255;
}

void invert(bool mode)
{
	if (mode==true)
		_LCD_Write(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYINVERTED, LCD_COMMAND);
	else
		_LCD_Write(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL, LCD_COMMAND);
}

void setPixel(uint16_t x, uint16_t y)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
		by=((y/8)*84)+x;
		bi=y % 8;

		scrbuf[by]=scrbuf[by] | (1<<bi);
	}
}

void clrPixel(uint16_t x, uint16_t y)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
		by=((y/8)*84)+x;
		bi=y % 8;

		scrbuf[by]=scrbuf[by] & ~(1<<bi);
	}
}

void invPixel(uint16_t x, uint16_t y)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
		by=((y/8)*84)+x;
		bi=y % 8;

		if ((scrbuf[by] & (1<<bi))==0)
			scrbuf[by]=scrbuf[by] | (1<<bi);
		else
			scrbuf[by]=scrbuf[by] & ~(1<<bi);
	}
}

void invertText(bool mode)
{
	if (mode==true)
		cfont.inverted=1;
	else
		cfont.inverted=0;
}

void print(char *st, int x, int y)
{
	unsigned char ch;
	int stl;

	stl = strlen(st);
	if (x == RIGHT)
		x = 84-(stl*cfont.x_size);
	if (x == CENTER)
		x = (84-(stl*cfont.x_size))/2;

    int cnt;
	for (cnt=0; cnt<stl; cnt++)
			_print_char(*st++, x + (cnt*(cfont.x_size)), y);
}

void prints(char *st, int x, int y)
{
//	char buf[st.length()+1];
//
//	st.toCharArray(buf, st.length()+1);
	print(st, x, y);
}

void printNumI(long num, int x, int y, int length, char filler)
{
	char buf[25];
	char st[27];
	bool neg=false;
	int c=0, f=0;
  
	if (num==0)
	{
		if (length!=0)
		{
			for (c=0; c<(length-1); c++)
				st[c]=filler;
			st[c]=48;
			st[c+1]=0;
		}
		else
		{
			st[0]=48;
			st[1]=0;
		}
	}
	else
	{
		if (num<0)
		{
			neg=true;
			num=-num;
		}
	  
		while (num>0)
		{
			buf[c]=48+(num % 10);
			c++;
			num=(num-(num % 10))/10;
		}
		buf[c]=0;
	  
		if (neg)
		{
			st[0]=45;
		}
	  
		if (length>(c+neg))
		{
            int i;
			for (i=0; i<(length-c-neg); i++)
			{
				st[i+neg]=filler;
				f++;
			}
		}

        int i;
		for (i=0; i<c; i++)
		{
			st[i+neg+f]=buf[c-i-1];
		}
		st[c+neg+f]=0;

	}

	print(st,x,y);
}

void printNumF(double num, uint8 dec, int x, int y, char divider, int length, char filler)
{
	char st[27];
    uint8_t size;
	bool neg=false;

	if (num<0)
		neg = true;

	_convert_float(st, num, length, dec);

	if (divider != '.')
	{
        size = sizeof st;
        int i;
		for (i=0; i<size; i++)
			if (st[i]=='.')
				st[i]=divider;
	}

	if (filler != ' ')
	{
		if (neg)
		{
			st[0]='-';
            size = sizeof st;
            int i;
			for (i=1; i<size; i++)
				if ((st[i]==' ') || (st[i]=='-'))
					st[i]=filler;
		}
		else
		{
            size = sizeof st;
            int i;
			for (i=0; i<size; i++)
				if (st[i]==' ')
					st[i]=filler;
		}
	}

	print(st,x,y);
}

void _print_char(unsigned char c, int x, int y)
{
	if ((cfont.y_size % 8) == 0)
	{
		int font_idx = ((c - cfont.offset)*(cfont.x_size*(cfont.y_size/8)))+4;
        int rowcnt;
		for (rowcnt=0; rowcnt<(cfont.y_size/8); rowcnt++)
		{
            int cnt;
			for(cnt=0; cnt<cfont.x_size; cnt++)
			{
                int b;
				for (b=0; b<8; b++)
					if ((fontbyte(font_idx+cnt+(rowcnt*cfont.x_size)) & (1<<b))!=0)
						if (cfont.inverted==0)
							setPixel(x+cnt, y+(rowcnt*8)+b);
						else
							clrPixel(x+cnt, y+(rowcnt*8)+b);
					else
						if (cfont.inverted==0)
							clrPixel(x+cnt, y+(rowcnt*8)+b);
						else
							setPixel(x+cnt, y+(rowcnt*8)+b);
			}
		}
	}
	else
	{
		int font_idx = ((c - cfont.offset)*((cfont.x_size*cfont.y_size/8)))+4;
		int cbyte=fontbyte(font_idx);
		int cbit=7;
        int cx;
		for (cx=0; cx<cfont.x_size; cx++)
		{
            int cy;
			for (cy=0; cy<cfont.y_size; cy++)
			{
				if ((cbyte & (1<<cbit)) != 0)
					if (cfont.inverted==0)
						setPixel(x+cx, y+cy);
					else
						clrPixel(x+cx, y+cy);
				else
					if (cfont.inverted==0)
						clrPixel(x+cx, y+cy);
					else
						setPixel(x+cx, y+cy);
				cbit--;
				if (cbit<0)
				{
					cbit=7;
					font_idx++;
					cbyte=fontbyte(font_idx);
				}
			}
		}
	}
}

void setFont(uint8_t* font)
{
	cfont.font=font;
	cfont.x_size=fontbyte(0);
	cfont.y_size=fontbyte(1);
	cfont.offset=fontbyte(2);
	cfont.numchars=fontbyte(3);
	cfont.inverted=0;
}

void drawHLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
        int cx;
		for (cx=0; cx<l; cx++)
		{
			by=((y/8)*84)+x;
			bi=y % 8;

			scrbuf[by+cx] |= (1<<bi);
		}
	}
}

void clrHLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
        int cx;
		for (cx=0; cx<l; cx++)
		{
			by=((y/8)*84)+x;
			bi=y % 8;

			scrbuf[by+cx] &= ~(1<<bi);
		}
	}
}

void drawVLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
        int cy;
		for (cy=0; cy<l; cy++)
		{
			setPixel(x, y+cy);
		}
	}
}

void clrVLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) && (x<84) && (y>=0) && (y<48))
	{
        int cy;
		for (cy=0; cy<l; cy++)
		{
			clrPixel(x, y+cy);
		}
	}
}

void drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=((double)(y2-y1)/(double)(x2-x1));
		ty=(double)(y1);
		if (x1>x2)
		{
            int i;
			for (i=x1; i>=x2; i--)
			{
				setPixel(i, (int)(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
            int i;
			for (i=x1; i<=x2; i++)
			{
				setPixel(i, (int)(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=((float)(x2-x1)/(float)(y2-y1));
		tx=(float)(x1);
        if (y1>y2)
        {
            int i;
			for (i=y2+1; i>y1; i--)
			{
		 		setPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
            int i;
			for (i=y1; i<y2+1; i++)
			{
		 		setPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void clrLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	double m, b, dx, dy;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		clrHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		clrVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=((double)(y2-y1))/((double)(x2-x1));
		ty=(double)(y1);
		if (x1>x2)
		{
            int i;
			for ( i=x1; i>=x2; i--)
			{
				clrPixel(i, (int)(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
            int i;
			for (i=x1; i<=x2; i++)
			{
				clrPixel(i, (int)(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=((float)(x2-x1)/(float)(y2-y1));
		tx=(float)(x1);
        if (y1>y2)
        {
            int i;
			for (i=y2+1; i>y1; i--)
			{
		 		clrPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
            int i;
			for (i=y1; i<y2+1; i++)
			{
		 		clrPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	drawHLine(x1, y1, x2-x1);
	drawHLine(x1, y2, x2-x1);
	drawVLine(x1, y1, y2-y1);
	drawVLine(x2, y1, y2-y1+1);
}

void clrRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	clrHLine(x1, y1, x2-x1);
	clrHLine(x1, y2, x2-x1);
	clrVLine(x1, y1, y2-y1);
	clrVLine(x2, y1, y2-y1+1);
}

void drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		setPixel(x1+1,y1+1);
		setPixel(x2-1,y1+1);
		setPixel(x1+1,y2-1);
		setPixel(x2-1,y2-1);
		drawHLine(x1+2, y1, x2-x1-3);
		drawHLine(x1+2, y2, x2-x1-3);
		drawVLine(x1, y1+2, y2-y1-3);
		drawVLine(x2, y1+2, y2-y1-3);
	}
}

void clrRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		clrPixel(x1+1,y1+1);
		clrPixel(x2-1,y1+1);
		clrPixel(x1+1,y2-1);
		clrPixel(x2-1,y2-1);
		clrHLine(x1+2, y1, x2-x1-3);
		clrHLine(x1+2, y2, x2-x1-3);
		clrVLine(x1, y1+2, y2-y1-3);
		clrVLine(x2, y1+2, y2-y1-3);
	}
}

void drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	setPixel(x, y + radius);
	setPixel(x, y - radius);
	setPixel(x + radius, y);
	setPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		setPixel(x + x1, y + y1);
		setPixel(x - x1, y + y1);
		setPixel(x + x1, y - y1);
		setPixel(x - x1, y - y1);
		setPixel(x + y1, y + x1);
		setPixel(x - y1, y + x1);
		setPixel(x + y1, y - x1);
		setPixel(x - y1, y - x1);
	}
}

void clrCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	char ch, cl;
	
	clrPixel(x, y + radius);
	clrPixel(x, y - radius);
	clrPixel(x + radius, y);
	clrPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		clrPixel(x + x1, y + y1);
		clrPixel(x - x1, y + y1);
		clrPixel(x + x1, y - y1);
		clrPixel(x - x1, y - y1);
		clrPixel(x + y1, y + x1);
		clrPixel(x - y1, y + x1);
		clrPixel(x + y1, y - x1);
		clrPixel(x - y1, y - x1);
	}
}

void drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy)
{
	int bit;
	uint8_t data;

    int cy;
	for (cy=0; cy<sy; cy++)
	{
		bit= cy % 8;
        int cx;
		for(cx=0; cx<sx; cx++)
		{
			data=bitmapbyte(cx+((cy/8)*sx));
			if ((data & (1<<bit))>0)
				setPixel(x+cx, y+cy);
			else
				clrPixel(x+cx, y+cy);
		}
	}      
}
