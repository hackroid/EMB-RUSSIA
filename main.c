/**
 *  Embedded System Project -- Тетрис!(俄罗斯方块)
 *  Project name:   EMB-RUSSIA
 *  Collaborators:  陈达寅 11612512
 *                  黄万款 11612501
 *                  曾政然 11612527
 *                  赵博弘 11612706
**/

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "tsensor.h"
#include "remote.h"
#include "key.h"
#include "24cxx.h"
#include "myiic.h"
#include "touch.h"

u16 col[6] = {RED, YELLOW, GREEN, BLUE, BROWN, LIGHTBLUE};
// 打印方块
void print_block(u16 x, u16 y, u16 color) {
	u8 i;
	POINT_COLOR = color;
	for(i = y; i < y + 16; i++) {
		LCD_DrawLine(x, i, x+15, i);
	}
}
// 结束界面
void gameover(void) {
	u16 i;
	
	POINT_COLOR = WHITE;
	for(i = 0; i < 112; i++)
		LCD_DrawLine(64 + i, 64, 64 + i, 256);
	
	POINT_COLOR = BLACK;
	LCD_DrawLine(64, 64, 64, 256);
	LCD_DrawLine(64, 256, 176, 256);
	LCD_DrawLine(176, 256, 176, 64);
	LCD_DrawLine(176, 64, 64, 64);
	
	POINT_COLOR = GRAY;
	for(i = 1; i < 4; i++) {
		LCD_DrawLine(64 + i, 256 + i, 176 + i, 256 + i);
		LCD_DrawLine(176 + i, 64 + i, 176 + i, 256 + i);
	}
	
	POINT_COLOR = BLACK;
	BACK_COLOR = WHITE;
	LCD_ShowString(80, 80, 200, 16, 16, "Good Game!");
	LCD_ShowString(92, 224, 200, 16, 16, "Restart");
	LCD_ShowString(72, 240, 200, 16, 16, "Back to menu");
	LCD_DrawLine(64, 224, 176, 224);
	LCD_DrawLine(64, 240, 176, 240);
	LCD_ShowString(96, 150, 200, 16, 16, "Score:");
	LCD_ShowString(96, 170, 200, 24, 24, "6666"); // 分数位置
	
	POINT_COLOR = RED;
	BACK_COLOR = BLACK;
	
	while(1) {
		u8 quit = 0;
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN) {
			if(tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height) {
				if(tp_dev.x[0] > 64 && tp_dev.x[0] < 176 && tp_dev.y[0] > 240 && tp_dev.y[0] < 256) {
					quit = 1;
				}
			}
		}
		if(quit == 1) {
			break;
		}
	}
}
// 组员界面
void collaborators(void) {
	LCD_Clear(BLACK);
	POINT_COLOR = WHITE;
	
	LCD_DrawLine(1, 1, 1, 319);
	LCD_DrawLine(1, 319, 239, 319);
	LCD_DrawLine(239, 319, 239, 1);
	LCD_DrawLine(239, 1, 1, 1);
	
	LCD_ShowString(86, 5, 200, 24, 24, "Tetris!");
	LCD_ShowString(70, 40, 200, 16, 16, "Collaborators");
	LCD_ShowString(36, 70, 200, 16, 16, "Zhengran Zeng 11612527");
	LCD_ShowString(36, 90, 200, 16, 16, "Dayin Chen    11612512");
	LCD_ShowString(36, 110, 200, 16, 16, "Wankuan Huang 11612501");
	LCD_ShowString(36, 130, 200, 16, 16, "Bohong Zhao   11612706");
	LCD_ShowString(190, 303, 200, 16, 16, "RETURN");
	LCD_DrawLine(188, 303, 188, 319);
	LCD_DrawLine(188, 303, 239, 303);
	POINT_COLOR = RED;
	BACK_COLOR = BLACK;
	
	while(1) {
		u8 quit = 0;
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN) {
			if(tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height) {
				if(tp_dev.x[0] > 190 && tp_dev.y[0] > 304) {
					quit = 1;
				}
			}
		}
		if(quit == 1) {
			break;
		}
	}
}
// 主界面（菜单））
void menu(void) {
	u16 i = 86;
	u16 j;
	LCD_Clear(BLACK);
	POINT_COLOR = col[0];
	BACK_COLOR = BLACK;
	LCD_ShowString(i, i, 200, 24, 24, "T     !");
	POINT_COLOR = col[1];
	LCD_ShowString(i+12, i, 200, 24, 24, "e");
	POINT_COLOR = col[2];
	LCD_ShowString(i+24, i, 200, 24, 24, "t");
	POINT_COLOR = col[3];
	LCD_ShowString(i+36, i, 200, 24, 24, "r");
	POINT_COLOR = col[4];
	LCD_ShowString(i+48, i, 200, 24, 24, "i");
	POINT_COLOR = col[5];
	LCD_ShowString(i+60, i, 200, 24, 24, "s");
	
	LCD_ShowString(88, 180, 200, 16, 16, "Start Game");
	LCD_ShowString(74, 240, 200, 16, 16, "Collaborators");
	
	for(i = 0; i < 4; i++)
		print_block(16, 16 + i*16, col[5]);
		
	print_block(48, 32, col[2]);
	print_block(64, 32, col[2]);
	print_block(64, 48, col[2]);
	print_block(80, 48, col[2]);
	
	for(i = 0; i < 3; i++)
		print_block(112, 32 + i*16, col[1]);
	print_block(128, 48, col[1]);
	
	for(i = 0; i < 2; i++)
		for(j = 0; j < 2; j++)
			print_block(160 + 16 * i, 32 + j*16, col[0]);
	
	for(i = 0; i < 3; i++)
		print_block(208, 16 + i*16, col[3]);
	print_block(224, 16, col[3]);
	
}
//主进程
void main_prog(void) {
	u8 key;
    u8 i = 0;
	u8 mod = 0;
	menu();
	while(1) {
		tp_dev.scan(0);
		if(tp_dev.sta & TP_PRES_DOWN) {
			if(tp_dev.x[0] < lcddev.width && tp_dev.y[0] < lcddev.height) {
				if(tp_dev.x[0] > 74 && tp_dev.x[0] < 178 && tp_dev.y[0] > 240 && tp_dev.y[0] < 256) {
					collaborators();
					menu();
				} else if(tp_dev.x[0] > 88 && tp_dev.x[0] < 168 && tp_dev.y[0] > 180 && tp_dev.y[0] < 196) {
					gameover();
					menu();
				}
			}
		}
	}
}
int main(void) {
	delay_init();            //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart_init(9600);        //串口初始化为9600
    LED_Init();             //初始化与LED连接的硬件接口
    LCD_Init();             //初始化LCD
    KEY_Init();             //按键初始化
    tp_dev.init();          //触摸屏初始化
	LCD_Clear(WHITE);
	main_prog();
}
