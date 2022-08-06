#include <REGX52.H>
#include <stdlib.h>
#include "TIMER0.H"
#include "MATRIX_NUM.H"
#include "DELAY.H"
#include "SHOW_74HC595.H"

unsigned char i;
unsigned char KeyNum,Game_State;  //按键键码，游戏状态
unsigned char code Led[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
unsigned char Snake_head[2];		      //蛇头位置
unsigned char Snake_BodyColumn[30];	  //蛇身位置：列
unsigned char Snake_BodyLine[30];	  //蛇身位置：行
unsigned char Snake_Flag;   //蛇身长度
unsigned char Temp_BodyColumn,Temp_BodyLine;	  //临时存储位置
unsigned char Food_Line,Food_Column;   //食物行列
unsigned char L_KeyNum;   	  //存储每次while中扫描到的不为零的KeyNum

void Snake_Init();
void Food_Update();
void Snake_Show();
void Snake_Update();
void Snake_Move();
void Food_Touch();

void main()
{
	Timer0_Init(); //定时器初始化
	D_Scr_Init();
	while(1)
	{
		KeyNum = Matrix_Num();	  //获取按键

		if((KeyNum == 6) && (Game_State == 0))//在游戏未开始时按下6开始游戏
		{
			Game_State = 1;			//更改游戏状态
			Food_Column = rand()%8;	 //食物初始化
			Food_Line = rand()%8;
			Snake_Init();			 //蛇数据初始化
			while(Game_State)		 //游戏循环
			{
				KeyNum = Matrix_Num();
				if(KeyNum != 0)	//过滤按键空闲时Matrix_Num传回的0
				{
					L_KeyNum = KeyNum;	 //将按键键码赋值给L_KeyNum
				}
				Food_Update();   //食物更新
				Snake_Show();	 //LED显示蛇
				Food_Touch();	 //检测食物碰撞
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0count1,T0count2;  
	TL0 = 0x18;		//设置定时初始值
	TH0 = 0xFC;		//设置定时初始值
	if(T0count1>=10)  //T0count1计时大于10时清零
	{
		T0count1 = 0;
		Matrix_Loop(); //计时10ms后调用一次按键检测
	}
	T0count1++;     //T0count1计时加一
	if(Game_State == 1) 
	{
		if(Snake_Flag<4)
		{
			if(T0count2 >= 700)   //T0count2计时大于700时清零
			{
				T0count2 = 0;
				Snake_Move(); 	 //每700ms蛇移动一次
			}	
	 		T0count2++;	   //T0count1计时加一
		}
		else if((Snake_Flag < 7) && (Snake_Flag >= 4))
		{
			if(T0count2 >= 500)   //T0count2计时大于500时清零
			{
				T0count2 = 0;
				Snake_Move(); 	 //每500ms蛇移动一次
			}	
	 		T0count2++;	   //T0count1计时加一
		}
		else
		{
			if(T0count2 >= 300)   //T0count2计时大于300时清零
			{
				T0count2 = 0;
				Snake_Move(); 	 //每300ms蛇移动一次
			}	
	 		T0count2++;	   //T0count1计时加一
		}
		
	}
}

void Snake_Init()
{
	Snake_head[0] = 2;Snake_head[1] = 0;	 //蛇头初始位置：1行三列
	Snake_BodyColumn[0] = 1;
	Snake_BodyColumn[1] = 0;	  //蛇身初始位置：列
	Snake_BodyLine[0] = 0;
	Snake_BodyLine[1] = 0;	  //蛇身初始位置：行
	Snake_Flag = 2;
	L_KeyNum = 0;
	Temp_BodyColumn,Temp_BodyLine;	  //临时存储位置
}
void Food_Update()
{
	unsigned char j;
	if((Snake_head[0] == Food_Column) && (Snake_head[1] == Food_Line)) 
	{
		Food_Column = rand()%8;	  //判断蛇头与食物重合时，更新食物位置
		Food_Line = rand()%8;

	}
	for(j=0;j<Snake_Flag;j++)
	{
		if((Snake_BodyColumn[j] == Food_Column) 
		&& (Snake_BodyLine[j] == Food_Line))
		{
			Food_Column = rand()%8;	  //判断蛇身与食物重合时，更新食物位置
			Food_Line = rand()%8;
		}
	}
}
void Snake_Show()	  //LED显示蛇的身体与头，食物
{
	for(i=0;i<Snake_Flag;i++)
	{
		D_Scr_Show(Snake_BodyColumn[i],Led[Snake_BodyLine[i]]);
	}
	D_Scr_Show(Snake_head[0],Led[Snake_head[1]]);
	D_Scr_Show(Food_Column,Led[Food_Line]);
}
void Snake_Update()		  
{
	for(i = 0; i < Snake_Flag; i++)		  //检测身体碰撞
	{
		if((Snake_head[0] == Snake_BodyColumn[i]) && (Snake_head[1] == Snake_BodyLine[i]))
		{
			Game_State = 0;			//若头身碰撞，则游戏结束
			break;
		}
	}
	Temp_BodyColumn = Snake_head[0];   //记录蛇头的行列
	Temp_BodyLine = Snake_head[1];
	for(i=0;i<Snake_Flag-1;i++)		   //循环更新蛇身
	{
		Snake_BodyColumn[Snake_Flag-1-i]=Snake_BodyColumn[Snake_Flag-i-2];
		Snake_BodyLine[Snake_Flag-1-i]=Snake_BodyLine[Snake_Flag-i-2];
	}
	Snake_BodyColumn[0] = Temp_BodyColumn;
	Snake_BodyLine[0] = Temp_BodyLine;

}

void Snake_Move()
{
	if(L_KeyNum == 2)       //按键键码为2时，蛇向上走
	{
		Snake_Update();	  //调用蛇更新函数
		if(Snake_head[1] == 0)		//蛇头触顶检测
		{
			Snake_head[1] = 7;	   //若蛇头触顶则从最下方出来
		}
		else
		{
			Snake_head[1] -= 1;	  //若未触顶，蛇头行数据向上移位
		}
	}
	else if(L_KeyNum == 5)  //按键键码为5时，蛇向左走
	{
		Snake_Update();	  //调用蛇更新函数
		if(Snake_head[0] == 0)
		{
			Snake_head[0] = 7;	 //若蛇头在最左方则从最右方出来
		}
		else
		{
			Snake_head[0] -= 1;	  //否则，蛇头列数据向左移位
		}
	}
	else if(L_KeyNum == 7)  //按键键码为7时，蛇向右走
	{
		Snake_Update();	  //调用蛇更新函数
		if(Snake_head[0] == 7)
		{
			Snake_head[0] = 0;	  //若蛇头在最右方则从最左方出来
		}
		else
		{
			Snake_head[0] += 1;	  //否则，蛇头列数据向右移位
		}
	}
	else if(L_KeyNum == 10) //按键键码为10时，蛇向下走
	{
		Snake_Update();
		if(Snake_head[1] == 7)		//蛇头触底检测
		{
			Snake_head[1] = 0;	   //若蛇头触底则从最上方出来
		}
		else
		{
			Snake_head[1] += 1;	   //否则，蛇头行数据向下移位
		}
	}
	else if(L_KeyNum == 1)		 //键码为1时，停止游戏
	{
		Game_State = 0;
	}

}
void Food_Touch()
{						 
	if((Snake_head[0] == Food_Column) && (Snake_head[1] == Food_Line))
	{
		if(Snake_Flag<10)
		{
			Snake_Flag += 1;	   //蛇头触碰到食物时，蛇身长度加1；
			//将蛇尾行列赋值给新增的空白数据
			Snake_BodyColumn[Snake_Flag-1] = Snake_BodyColumn[Snake_Flag-2];
			Snake_BodyLine[Snake_Flag-1] = Snake_BodyLine[Snake_Flag-2];
		}
//		else
//		{
//			D_Scr_Byte(1);
//			Game_State = 0;
//		}
	}
}
