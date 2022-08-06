#include<reg52.h>
#include <stdlib.h> 
 
typedef unsigned int u16;
typedef unsigned char u8;
 
sbit RCLKS = P3^5;
sbit SRCLK = P3^6;
sbit SET = P3^4;
 
//Row为1亮，Col为0亮
u8 Row = 0x08;
u8 Col = 0xF7;
 
//最大长度为5 ,防止过长出现闪烁
u8 Rows[5];
u8 Cols[5];
 
u8 len = 1;
u8 direct = 0;
 
u16 p=0;//每8次中断检测一次
void Init_time_0()
{
    TMOD = 0x01;
    TH0 = 0x0c;
    TL0 = 0x0c;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}
 
 
void delay(u16 i)
{
    while(i--);
}
void  Led(u8 dat,u8 dat2)
{
    u16 i;
    RCLKS = 1;
    SRCLK = 1;
     
     
    for(i=0;i<8;i++)
    {
        SET = dat>>7;
        dat = dat <<1;
        SRCLK = 0;
        SRCLK =1;
    }
     
    RCLKS = 0;
     
    RCLKS = 1;
    P0 = dat2;
}
 
 
u16 KEY()   
{
    u16 key = -1;
    P1 = 0x0f;
     
     
    if(P1 != 0x0f)
    {
        delay(500);
         
        if(P1 != 0x0f)
        {
            P1 = 0x0f;
            switch(P1)
            {
                case (0x07): key = 0;break;
                case (0x0b): key = 1;break;
                case (0x0d): key = 2;break;
                case (0x0e): key = 3;break;
            }
            P1 = 0xf0;
            switch(P1)
            {
                case(0x70): key+=0;break;
                case(0xb0): key+=4;break;
                case(0xd0): key+=8;break;
                case(0xe0): key+=12;break;
            }
        }
         
         
     
     
    }
     
     
    return key;
     
 
}
 
 
 
 
void Up(u8 len)
{
    u8 i;
    u8 tmp = Rows[0];
    u8 rr,cc_1,cc_2;
    if(Rows[0] != 0x80)
        Rows[0] <<=1;
    cc_1 = Cols[0];
        //后一节依次等于前一节的值
    for(i=1;i<len;i++)
    {
         
        rr = Rows[i];
        Rows[i] =tmp;
        tmp = rr;
         
        cc_2 = Cols[i];
        Cols[i] = cc_1;
        cc_1 = cc_2;
    }
 
}
 
 
void Down(u8 len)
{
    u8 i;
    u8 tmp = Rows[0];
    u8 rr,cc_1,cc_2;
    if(Rows[0] != 0x01)
        Rows[0]>>=1;
    cc_1 = Cols[0];
    for(i=1;i<len;i++)
    {
         
        rr = Rows[i];
        Rows[i] =tmp;
        tmp = rr;
         
        cc_2 = Cols[i];
        Cols[i] = cc_1;
        cc_1 = cc_2;
    }
}
 
void Left(u8 len)
{
    u8 i;
    u8 tmp = Cols[0];
    u8 cc,rr_1,rr_2;
    if(Cols[0] != 0x7F)
    {
        Cols[0] <<=1;
        Cols[0] += 1;
    }
    rr_1 = Rows[0];
    for(i=1;i<len;i++)
    {
        cc = Cols[i];
        Cols[i] = tmp;
        tmp = cc;
         
        rr_2 = Rows[i];
        Rows[i] = rr_1;
        rr_1 = rr_2;
     
    }
}
 
void Right(u8 len)
{
    u8 i;
    u8 tmp = Cols[0];
    u8 cc,rr_1,rr_2;
    if(Cols[0] != 0xFE)
    {
        Cols[0] >>=1;
        Cols[0] += 0x80;
    }
    rr_1 = Rows[0];
    for(i=1;i<len;i++)
    {
        cc = Cols[i];
        Cols[i] = tmp;
        tmp = cc;
         
        rr_2 = Rows[i];
        Rows[i] = rr_1;
        rr_1 = rr_2;
     
    }
}
 
void main()
{
    u8 i;
    u16 key;
    //u8 len = 1;
    u8 Food_row = 0x20;
    u8 Food_col = 0xfb;
    //u8 direct = 0;
    Rows[0] = Row;
    Cols[0] = Col;
    Init_time_0();
    while(1)
    {
//      key = KEY();
//      if(key != -1)
//      {
//          if(key == 1)
//          {
//              Up(len);
//          //  direct = 0;
//              delay(20000);
//          }
//          if(key == 9)
//          {
//              Down(len);
//              //direct = 1;
//              delay(20000);
//          }
//          if(key == 4)
//          {
//              Left(len);
//              //direct = 2;
//              delay(20000);
//          }
//          if(key == 6)
//          {
//              Right(len);
//              //direct = 3;
//              delay(20000);
//          }
//      }
//      switch(direct)
//      {
//          case 0: Up(len);break;
//          case 1: Down(len);break;
//          case 2: Left(len);break;
//          case 3: Right(len);break;
//      }
        //判断蛇头是否到达食物的位置
        if((Rows[0] == Food_row) && (Cols[0] == Food_col))
        {
            if(len<5)
            {
                Rows[len] = Rows[len-1];
                Cols[len] = Cols[len-1];
                len++;
 
 
 
            }
                        //随机更新食物的位置
                        Food_col = ~(0x01 << rand()%8);
                        Food_row = 0x01 << rand()%8;
        }
         
        Led(Food_row,Food_col);
        for(i=0;i<len;i++)
            Led(Rows[i],Cols[i]);
         
    }
 
 
}
 
void Time_0() interrupt 1
{
    u8 key;
    key = KEY();
    if(key != -1)
    {
        if(key == 1)
        {
            //Up(len);
            direct = 0;
            delay(10000);
        }
        if(key == 9)
        {
            //Down(len);
            direct = 1;
            delay(10000);
        }
        if(key == 4)
        {
            //Left(len);
            direct = 2;
            delay(10000);
        }
        if(key == 6)
        {
            //Right(len);
            direct = 3;
            delay(10000);
        }
    }
    //防止p过大
    if(p>8*100)
        p = 0;
    p++;
    if(p%8 == 0)
    {
    switch(direct)
    {
        case 0: Up(len);break;
        case 1: Down(len);break;
        case 2: Left(len);break;
        case 3: Right(len);break;
    }
    }
    TH0 = 0x0c;
    TL0 = 0x0c;
}