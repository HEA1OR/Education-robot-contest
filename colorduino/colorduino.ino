/*
  Colorduino - Colorduino DEMO for Arduino.
  Copyright (c) 2010 zzy@IteadStudio.  All right reserved.

  This DEMO is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This DEMO is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Publicv
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <Wire.h>
#include "Arduino.h"
#include <avr/pgmspace.h>
#include <time.h>

/*****************************
  define the operate commands
*****************************/

/*****************************
  define the status
*****************************/

/*****************************
  define the IO
*****************************/
#define RST_BIT 0x04
#define LAT_BIT 0x02
#define SLB_BIT 0x01
#define SCL_BIT 0x40
#define SDA_BIT 0x80

#define RST PORTC
#define LAT PORTC
#define SLB PORTC
#define SDA PORTD
#define SCL PORTD

#define open_line0	{PORTB=0x01;}
#define open_line1	{PORTB=0x02;}
#define open_line2	{PORTB=0x04;}
#define open_line3	{PORTB=0x08;}
#define open_line4	{PORTB=0x10;}
#define open_line5	{PORTB=0x20;}
#define open_line6	{PORTD=0x08;}
#define open_line7	{PORTD=0x10;}
#define close_all_line	{PORTD=0x00;PORTB=0x00;}

/*******************************************
  define the data zone
*******************************************/
/*
  //Test dots
  unsigned char Tdots[8][8][3]=     {{{0,0,255},     {0,0,255},      {0,0,255},     {0,0,255},    {0,0,255},      {0,0,255},       {0,0,255},        {0,0,255}},
                                  {{0,165,255},   {0,165,255},    {0,165,255},   {0,165,255},  {0,165,255},    {0,165,255},     {0,165,255},      {0,165,255}},
                                  {{0,255,255},   {0,255,255},    {0,255,255},   {0,255,255},  {0,255,255},    {0,255,255},     {0,255,255},      {0,255,255}},
                                  {{0,255,0},     {0,255,0},      {0,255,0},     {0,255,0},    {0,255,0},      {0,255,0},       {0,255,0},        {0,255,0}},
                                  {{255,127,0},   {255,127,0},    {255,127,0},   {255,127,0},  {255,127,0},    {255,127,0},     {255,127,0},      {255,127,0}},
                                  {{255,0,0},     {255,0,0},      {255,0,0},     {255,0,0},    {255,0,0},      {255,0,0},       {255,0,0},        {255,0,0}},
                                  {{255,0,139},   {255,0,139},    {255,0,139},   {255,0,139},  {255,0,139},    {255,0,139},     {255,0,139},      {255,0,139}},
                                  {{255,255,255}, {255,255,255},  {255,255,255}, {255,255,255},{255,255,255},  {255,255,255},   {255,255,255},    {255,255,255}}
                                 };
*/
unsigned char dots[2][8][8][3] = {0};
//dots matrix
//[2]:Page:one for display, one for receive data
//[8]:Row:8 row in LED plane
//[8]:Column:8 column in one row
//[3]:Color:RGB data: 0 for Red; 1 for green, 2 for Blue
unsigned char Gamma_Value[3] = {10, 63, 63};
//Gamma correctly value, every LED plane is different.value range is 0~63
//[3]:RGB data, 0 for Red; 1 for green, 2 for Blue
unsigned char Page_Index = 0; // the index of buffer
unsigned char row = 0;//the value of row in LED plane, from 0~7
unsigned char column = 0;//the value of every row, from 0~7
unsigned char color = 0;//the value of every dots, 0 is Red, 1 is Green, 2 is Blue

unsigned char line = 0;

/**************************************************
  define the extern data zone
**************************************************/
extern unsigned char font8_8[92][8];
extern unsigned char pic[4][8][8][3];
/***************************************************
  all parts inition functions zone
***************************************************/
void _IO_Initial()
{
  DDRD = 0xff; // set all pins direction of PortD
  DDRC = 0xff; // set all pins direction of PortC
  DDRB = 0xff; // set all pins direction of PortB

  PORTD = 0x00; // set all pins output is low of PortD
  PORTC = 0x00;
  // set all pins output is low of PortC
  PORTB = 0x00; // set all pins output is low of PortB
}
void _LED_Init()
{
  /*
    LED_RST(1);
    LED_Delay(1);
    LED_RST(0);
    LED_Delay(1);
    LED_RST(1);
    LED_Delay(1);
  */
  LED_RST(1);
  SetGamma();
  line = 0;

}
void _TC2_Init()
{
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  TCCR2B |= ((1 << CS22) | (1 << CS20)); // by clk/64
  TCCR2B &= ~((1 << CS21)); // by clk/64
  TCCR2A &= ~((1 << WGM21) | (1 << WGM20)); // Use normal mode
  ASSR |= (1 << AS2);     // Use internal clock - external clock not used in Arduino
  TIMSK2 |= (1 << TOIE2) | (0 << OCIE2B); //Timer2 Overflow Interrupt Enable
  TCNT2 = 0xff;
  sei();
}


/****************************************************
  the timer2 operate functions zone
****************************************************/
ISR(TIMER2_OVF_vect)          //Timer2  Service
{
  cli();
  TCNT2 = 0x64;      //flash a led matrix frequency is 100.3Hz,period is 9.97ms
  //TCNT2 = 0x63;      //flash a led matrix frequency is 99.66Hz,period is 10.034ms
  if (line > 7) line = 0;
  close_all_line;
  run(line);
  open_line(line);
  line++;
  sei();
}
/****************************************************
  the LED Hardware operate functions zone
****************************************************/
void LED_SDA(unsigned char temp)
{
  if (temp)
    SDA |= SDA_BIT;
  else
    SDA &= ~SDA_BIT;
}

void LED_SCL(unsigned char temp)
{
  if (temp)
    SCL |= SCL_BIT;
  else
    SCL &= ~SCL_BIT;
}

void LED_RST(unsigned char temp)
{
  if (temp)
    RST |= RST_BIT;
  else
    RST &= ~RST_BIT;
}

void LED_LAT(unsigned char temp)
{
  if (temp)
    LAT |= LAT_BIT;
  else
    LAT &= ~LAT_BIT;
}

void LED_SLB(unsigned char temp)
{
  if (temp)
    SLB |= SLB_BIT;
  else
    SLB &= ~SLB_BIT;
}
/***************************************************
  the LED datas operate functions zone
***************************************************/
void SetGamma()
{
  unsigned char i = 0;
  unsigned char j = 0;
  unsigned char k = 0;
  unsigned char temp = 0;
  LED_LAT(0);
  LED_SLB(0);
  for (k = 0; k < 8; k++)
    for (i = 3; i > 0 ; i--)
    {
      temp = Gamma_Value[i - 1] << 2;
      for (j = 0; j < 6; j++)
      {
        if (temp & 0x80)
          LED_SDA(1);
        else
          LED_SDA(0);

        temp = temp << 1;
        LED_SCL(0);
        LED_SCL(1);
      }
    }
  LED_SLB(1);
}
void run(unsigned char k)
{
  unsigned char i = 0;
  unsigned char j = 0;
  unsigned char p = 0;
  unsigned char temp = 0;
  LED_SLB(1);
  LED_LAT(0);
  for (i = 0; i < 8; i++)
  {

    for (j = 0; j < 3; j++)
    {
      temp = dots[Page_Index][k][i][2 - j];
      for (p = 0; p < 8; p++)
      {
        if (temp & 0x80)
          LED_SDA(1);
        else
          LED_SDA(0);

        temp = temp << 1;
        LED_SCL(0);
        LED_SCL(1);
      }
    }
  }
  LED_LAT(1);
  LED_LAT(0);
}
void open_line(unsigned char x)
{
  switch (x)
  {
    case 0 : open_line0;
      break;
    case 1 : open_line1;
      break;
    case 2 : open_line2;
      break;
    case 3 : open_line3;
      break;
    case 4 : open_line4;
      break;
    case 5 : open_line5;
      break;
    case 6 : open_line6;
      break;
    case 7 : open_line7;
      break;
    default: close_all_line;
      break;
  }
}
/********************************************************
  Name:DispShowChar
  Function:Display a English latter in LED matrix
  Parameter:chr :the latter want to show
          R: the value of RED.   Range:RED 0~255
          G: the value of GREEN. Range:RED 0~255
          B: the value of BLUE.  Range:RED 0~255
          bias: the bias of a letter in LED Matrix.Range -7~7
********************************************************/
void DispShowChar(char chr, unsigned char R, unsigned char G, unsigned char B, char bias)
{
  unsigned char i, j, Page_Write, temp;
  unsigned char Char;
  unsigned char chrtemp[24] = {0};

  if ((bias > 8) || (bias < -8))
    return;


  Char = chr - 32;

  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;
  j = 8 - bias;
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = random(255);//原来是=B;
        dots[Page_Write][j][i][1] = random(255);//G;
        dots[Page_Write][j][i][2] = random(255);//R;
      }
      else
      {
        dots[Page_Write][j][i][0] = 0;
        dots[Page_Write][j][i][1] = 0;
        dots[Page_Write][j][i][2] = 0;
      }
      temp = temp << 1;
    }
  }
  Page_Index = Page_Write;
}

void DispShowChar2(char chr, unsigned char R, unsigned char G, unsigned char B, char bias)
{
  unsigned char i, j, Page_Write, temp;
  unsigned char Char;
  unsigned char chrtemp[24] = {0};

  R /= 6;
  G /= 6;
  if ((bias > 8) || (bias < -8))
    return;


  Char = chr - 32;

  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;
  j = 8 - bias;
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = B;//原来是=B;
        dots[Page_Write][j][i][1] = G;//G;
        dots[Page_Write][j][i][2] = R;//R;
      }
      else
      {
        dots[Page_Write][j][i][0] = 0;
        dots[Page_Write][j][i][1] = 0;
        dots[Page_Write][j][i][2] = 0;
      }
      temp = temp << 1;
    }
  }
  Page_Index = Page_Write;
}
void DispShowChar3(char chr, unsigned char R, unsigned char G, unsigned char B, char bias)
{
  unsigned char i, j, Page_Write, temp;
  unsigned char Char1, Char2;
  unsigned char chrtemp[24] = {0};

  R /= 6;
  G /= 6;
  if ((bias > 8) || (bias < -8))
    return;


  Char1 = chr - 32;
  Char2 = chr - 31;
  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;
  j = 8 - bias;
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char1][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = B;//原来是=B;
        dots[Page_Write][j][i][1] = G;//G;
        dots[Page_Write][j][i][2] = R;//R;
      }
      else
      {
        dots[Page_Write][j][i][0] = 0;
        dots[Page_Write][j][i][1] = 0;
        dots[Page_Write][j][i][2] = 0;
      }
      temp = temp << 1;
    }
  }
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char2][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = 255;//原来是=B;
        dots[Page_Write][j][i][1] = 42.5; //G;
        dots[Page_Write][j][i][2] = 42.5;//R;
      }
      temp = temp << 1;
    }
  }
  Page_Index = Page_Write;
}
void DispShowChar4(char chr, unsigned char R, unsigned char G, unsigned char B, char bias)
{
  unsigned char i, j, Page_Write, temp;
  unsigned char Char;
  unsigned char chrtemp[24] = {0};

  R /= 6;
  G /= 6;
  if ((bias > 8) || (bias < -8))
    return;


  Char = chr - 32;

  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;
  j = 8 - bias;
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = B;//原来是=B;
        dots[Page_Write][j][i][1] = G;//G;
        dots[Page_Write][j][i][2] = R;//R;
      }
      else
      {
        dots[Page_Write][j][i][0] = 255;
        dots[Page_Write][j][i][1] = 42.5;
        dots[Page_Write][j][i][2] = 0;
      }
      temp = temp << 1;
    }
  }
  Page_Index = Page_Write;
}
void DispShowChar5(char chr, unsigned char R, unsigned char G, unsigned char B, char bias)//口罩
{
  unsigned char i, j, Page_Write, temp;
  unsigned char Char1,Char2;
  unsigned char chrtemp[24] = {0};

  R/=6;
  G/=6;
  if ((bias > 8) || (bias < -8))
    return;


  Char1 = chr - 32;
  Char2 = chr - 31;
  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;
  j = 8 - bias;
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char1][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = B;//原来是=B;
        dots[Page_Write][j][i][1] = G;//G;
        dots[Page_Write][j][i][2] = R;//R;
      }
      else
      {
        dots[Page_Write][j][i][0] = 0;
        dots[Page_Write][j][i][1] = 0;
        dots[Page_Write][j][i][2] = 0;
      }
      temp = temp << 1;
    }
  }
  for (i = 0; i < 8; i++)
  {
    chrtemp[j] = pgm_read_byte(&(font8_8[Char2][i]));
    j++;
  }
  for (i = 0; i < 8; i++)
  {

    temp = chrtemp[i + 8];
    for (j = 0; j < 8; j++)
    {
      if (temp & 0x80)
      {
        dots[Page_Write][j][i][0] = 0;//原来是=B;
        dots[Page_Write][j][i][1] = 21.3; //G;
        dots[Page_Write][j][i][2] = 21.3;//R;
      }
      temp = temp << 1;
    }
  }
  Page_Index = Page_Write;
}
/********************************************************
  Name:DispShowColor
  Function:Fill a color in LED matrix
  Parameter:R: the value of RED.   Range:RED 0~255
          G: the value of GREEN. Range:RED 0~255
          B: the value of BLUE.  Range:RED 0~255
********************************************************/
void DispShowColor(unsigned char R, unsigned char G, unsigned char B)
{
  unsigned char Page_Write, i, j;

  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;

  for (i = 0; i < 8; i++)
    for (j = 0; j < 8; j++)
    {
      dots[Page_Write][i][j][2] = R;
      dots[Page_Write][i][j][1] = G;
      dots[Page_Write][i][j][0] = B;
    }

  Page_Index = Page_Write;
}
/********************************************************
  Name:DispShowPic
  Function:Fill a picture in LED matrix from FLASH
  Parameter:Index:the index of picture in Flash.
********************************************************/
void DispShowPic(unsigned char Index)
{
  unsigned char Page_Write, i, j;

  if (Page_Index == 0)
    Page_Write = 1;
  if (Page_Index == 1)
    Page_Write = 0;

  for (i = 0; i < 8; i++)
  {

    for (j = 0; j < 8; j++)
    {

      dots[Page_Write][i][j][0] = pgm_read_byte(&(pic[Index][i][j][2]));
      dots[Page_Write][i][j][1] = pgm_read_byte(&(pic[Index][i][j][1]));
      dots[Page_Write][i][j][2] = pgm_read_byte(&(pic[Index][i][j][0]));
    }
  }
  Page_Index = Page_Write;

}

/******************************************
  the other operate functions zone
******************************************/
void LED_Delay(unsigned char i)
{
  unsigned int y;
  y = i * 10;
  while (y--);
}
/*
  ColorduinoPlasma - Plasma demo using Colorduino Library for Arduino
  此函数的功能是，让RGB模块显示出渐变的R、G、B的组合颜色。
  效果是和我们在街上看到的那个RGB全彩显示屏显示的是一样的，只不过是我们现在只做的是8X8的点阵。可以通过74HC595进行扩展达到更大的显示效果！
*/



/****************************************************
  Main Functions zone
****************************************************/
void setup()
{
  _IO_Initial();           //Init IO
  _LED_Init();          //Init LED Hardware
  _TC2_Init();          //Init Timer/Count2
  Serial.begin(9600);
}
void loop()
{
  unsigned int i = 100 ;//停留速度
  int j, k ,l;
  byte c = 0;


  if (Serial.available() > 0)
  {
    c = Serial.read();
    switch (c)
    {
      case 'A':      //方格转圈1秒
          for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('<', 0,255-25*l, 25*l, 0);
            delay(50);
          }
          for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('<', 0, 255-25*l, 25*l, 0); 
            delay(50);
          }
        break;
      case 'B':       //旋风转圈1秒
          for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('=', 255-25*l, 0, 25*l, 0); 
            delay(50);
          }
          for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('=', 255-25*l, 0, 25*l, 0); 
            delay(50);
          }
        break;
      case 'C':     //人1滑雪一秒
      DispShowChar2('@',   255, 0, 0, 1);
      delay(200);
      DispShowChar2('@',   255, 0, 0, 0);
      delay(200);
      DispShowChar2('@',   255, 0, 0, -1);
      delay(200);
      DispShowChar2('@',   255, 0, 0, 0);
      delay(200);
      DispShowChar2('@',   255, 0, 0, 1);
      delay(200);
        break;
      case 'D':      //人2滑雪一秒
      DispShowChar2('A',   255, 0, 0, -1); 
      delay(200);
      DispShowChar2('A',   255, 0, 0, 0);
      delay(200);
      DispShowChar2('A',   255, 0, 0, 1);
      delay(200);
      DispShowChar2('A',   255, 0, 0, 0);
      delay(200);
      DispShowChar2('A',   255, 0, 0, -1);
      delay(200);
        break;
      case 'E':     //动态白实心圆1秒 
      for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('B',   255-25*l,255-25*l, 255-25*l, 0);
            delay(50);
          }
      for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('B',  255-25*l,255-25*l, 255-25*l, 0);
            delay(50);
          }
        break;
      case 'F':      //动态白空心圆1秒
      for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('D',   255-25*l,255-25*l, 255-25*l, 0);
            delay(50);
          }
      for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('D',  255-25*l,255-25*l, 255-25*l, 0);
            delay(50);
          }
        break;
      case 'G':   //动态箭头一秒
          for (l=-7; l <= 7; l++)
          {
            DispShowChar2('+', 255-10*l, 0, 150, l);
            delay(66);
          }
          
        break;
      case 'H':  //转圈1秒
          for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('>', 255-25*l,0, 25*l, 0); 
            delay(50);
          }
          for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('>', 255-25*l,0, 25*l, 0); 
            delay(50);
          }
      
        break;
      case 'I': DispShowChar2(')',   255, 255, 0, 0); 
        break;
      case 'J': 
      DispShowChar2('?',   255, 255, 0, 0); 
      delay(333);
      DispShowChar2('?',   255, 255, 0, -1); 
      delay(333);
      DispShowChar2('?',   255, 255, 0, 0); 
      delay(333);
        break;
      case 'K':  //绿圆一秒
      for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('B',   0, 255-20*j, 0, 0); 
            delay(50);
          }
      for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('B',   0, 255-20*l, 0, 0); 
            delay(50);
          }
        break;
      case 'L':       //雪花转圈1秒
          for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('>', 255-25*l, 100+10*l, 0, 0); 
            delay(50);
          }
          for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('>', 255-25*l, 100+10*l, 0, 0); 
            delay(50);
          }
        break;
      case 'M':         // 推冰球1秒
        DispShowChar2('C',   255, 0, 0, 1);
        delay(200);
        DispShowChar2('C',   255, 0, 0, 0);
        delay(200);
        DispShowChar2('C',   255, 0, 0, -1);
        delay(200);
        DispShowChar2('C',   255, 0, 0, 0);
        delay(200);
        DispShowChar2('C',   255, 0, 0, 1);
        delay(200);
        break;
      case 'N':        //绿空心圆一秒
        for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('D',   0, 255-20*j, 0, 0); 
            delay(50);
          }
        for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('D',   0, 255-20*l, 0, 0); 
            delay(50);
          }
        break;
      case 'O': 
      for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('E',  0 , 255-25*l, 255-25*l, 0); //金 
            delay(50);
          }
      for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('E',   0, 255-25*l, 255-25*l, 0); 
            delay(50);
          }
        break;
      case 'P': DispShowChar2('G',   0, 128,255, 0); //铜
      for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('G',  0 , 128-12*l, 255-25*l, 0); 
            delay(50);
          }
      for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('G',   0, 128-12*l, 255-25*l, 0); 
            delay(50);
          }
        break;
      case 'Q': DispShowChar2('F',   255, 255, 255, 0);   //银
      for (j = 0, l=0; j <= 10; j++,l++)
          {
            DispShowChar2('F',  255-25*l , 255-25*l, 255-25*l, 0); 
            delay(50);
          }
      for (j = 0, l=10; j <= 10; j++,l--)
          {
            DispShowChar2('F',  255-25*l , 255-25*l, 255-25*l, 0); 
            delay(50);
          }
        break;
      case 'R': DispShowChar2('I',   255, 255, 0, 0); //数字5
        break;
      case 'S': DispShowChar2('J',   0,0,255, 0);//八叉
        delay(3000);
        break;
      case 'T':DispShowChar2('i',   0,0,255, 0);//笑脸
        delay(3000);
        break;
      case 'U':DispShowChar5('i',   0,0,255, 0);//笑脸+口罩
        delay(3000);
        break;
      case 'V':for (j = ':'; j <= 'G'; j++)
                 {
                   DispShowChar2(j,   0,255,255, 0);//对应BGR
                   delay(100);
                 }
                 delay(300);//运货
                 break;
      case 'Z': DispShowChar(' ', random(255), random(255), random(255), 0);
        break;//清屏
    }
  }
}
/*void loop()
  {
  unsigned int i = 100 ;//停留速度
  int j, k;
  byte c = 0;
  //  DispShowChar('A',255,0,0,0);
  //  DispShowPic(0);
  if (Serial.available() > 0)
  {
    c = Serial.read();
    switch (c)
    {

      case 'A': //直行动态箭头
        for (k = 0; k < 2; k++)
        {
          for (j = -7; j < 9; j++)
          {
            DispShowChar2('z', 213, 5, 223, j);
            delay(i);
          }
        }
        break;
      case 'B': //左转箭头
        DispShowChar2('y', 213, 5, 223, 0);
        delay(800);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'C'://右转箭头
        DispShowChar2('x', 213, 5, 223, 0);
        delay(800);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'D': //礼花
        for ( k = 0; k < 7; k++)
        {
          for (j = '0'; j < '6'; j++)
          {
            DispShowChar(j, random(255), random(255), random(255), 0);
            delay(200);
          }
          delay(300);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;


      case '1'://集合

        DispShowChar2('6', 123, 55, 12, 0);
        delay(26000);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case '2'://集合
        delay(500);
        DispShowChar2('6' + 1, 123, 55, 12, 0);
        delay(25500);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case '3'://集合
        delay(1000);
        DispShowChar2('6' + 2, 123, 55, 12, 0);
        delay(25000);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case '4'://集合
        delay(1500);
        DispShowChar2('6' + 3, 123, 55, 12, 0);
        delay(24500);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case '5'://集合
        delay(2000);
        DispShowChar2('6' + 4, 123, 55, 12, 0);
        delay(24000);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;


      case 'F': //三角
        for ( k = 0; k < 18; k++)
        {
          for (j = 'A'; j <= 'D'; j++)
          {
            DispShowChar(j, random(255), random(255), random(255), 0);
            delay(i + 100);
          }
          delay(100);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case 'G': //矩阵
        for ( k = 0; k < 8; k++)
        {
          for (j = 'E'; j <= 'L';
               j++)
          {
            DispShowChar(j, random(255), random(255), random(255), 0);
            delay(i + 100);
          }
          //delay(100);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'H': //动态三者出击(短)
        for (k = 0; k < 3; k++)
        {
          for (j = -7; j < 9; j++)
          {
            DispShowChar('w', random(255), random(255), random(255), j);
            delay(i);
          }
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'I': //动态三者出击(长)
        for (k = 0; k < 7; k++)
        {
          for (j = -7; j < 9; j++)
          {
            DispShowChar('w', random(255), random(255), random(255), j);
            delay(i);
          }
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case 'M': //流星
        srand(time(NULL));
        for (k = 0; k < 12; k++)
        {
          int m = random() % ('U' - 'M') + 'M';
          for (j = -7; j < 9; j++)
          {
            DispShowChar(m, random(255), random(255), random(255), j);
            delay(random() % 100);
          }
          DispShowChar(' ', random(20), random(100), random(100), 0);
          delay(random() % 50);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'N'://双花
        for ( k = 0; k < 14; k++)
        {
          for (j = 'U'; j <= '^'; j++)
          {
            DispShowChar(j, random(255), random(255), random(255), 0);
            delay(300);
          }
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'O'://最终
        for (k = 0; k < 5; k++)
        {
          for (i = '_'; i <= 'c'; i++)
          {
            for (j = -7; j < 9; j++)
            {
              DispShowChar(i, random(255), random(255), random(255), j);
              if ( (j == 0) && (i == 'a' - 1 ))
              {
                delay(4000);
              }
              delay(70);
            }
          }
          delay(1500);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case 'P'://对号
        DispShowChar2('e', 0, 255, 0, 0);
        delay(800);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'Q': //问号
        DispShowChar2('d', 0, 0, 255, 0);
        delay(800);
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;
      case 'R'://十字
        for ( k = 0; k < 60; k++)
        {
          for (j = 'f'; j <= 'g'; j++)
          {
            DispShowChar(j, random(255), random(255), random(255), 0);
            delay(200);
          }
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case 'S'://sos  54s
        for (k = 0; k < 15; k++)
        {
          i = 's';
          for (j = -7; j < 8; j++)
          {
            DispShowChar2(i, 0, 0, 255, j);
            delay(70);
          }
          i = 'o';
          for (j = -7; j < 8; j++)
          {
            DispShowChar2(i, 0, 0, 255, j);
            delay(70);
          }
          i = 's';
          for (j = -7; j < 8; j++)
          {
            DispShowChar2(i, 0, 0, 255, j);
            delay(70);
          }
          delay(500);
          DispShowChar(' ', random(255), random(255), random(255), 0);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case 'T'://恐怖
        DispShowChar2('h', 0, 0, 255, 0);
        delay(5000);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'U'://哭脸
        DispShowChar2('i', 0, 0, 255, 0);
        delay(5000);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'V'://笑脸
        DispShowChar2('j', 0, 255, 0, 0);
        delay(5000);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'W'://Wifi
        for ( k = 0; k < 5; k++)
        {
          for (j = 'k'; j <= 'n'; j++)
          {
            DispShowChar2(j, 0, 255, 0, 0);
            delay(300);
          }
          delay(300);
        }
        DispShowChar(' ', random(255), random(255), random(255), 0);
        break;

      case 'X'://蓝盾
        DispShowChar2('p', 255, 0, 0, 0);
        delay(5000);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'Y'://感叹号
        DispShowChar2('q', 0, 0, 255, 0);
        delay(500);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'n':
        DispShowChar2('a' - 1, 106, 0, 95, 0);
        delay(10000);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case 'j':
        DispShowChar2('b' - 1, 106, 0, 95, 0);
        delay(10000);
        DispShowChar(' ', 1, 1, 1, 0);
        break;

      case'u':
          DispShowChar2('c' - 1, 106 ,0, 95, 0);
          delay(10000);
          DispShowChar(' ', 1, 1, 1, 0);
          break;

        }
  }
  }
*/
