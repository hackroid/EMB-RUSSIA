/**
 *  Embedded System Project -- Тетрис!(俄罗斯方块)
 *  Project name:   EMB-RUSSIA
 *  Collaborators:  陈达寅 xxxxxxxx
 *                  黄万款 xxxxxxxx
 *                  请填上 xxxxxxxx
 *                  赵博弘 xxxxxxxx
 **/

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "tsensor.h"
#include "remote.h"

int main(void) {

	u16 adcx;
	u8 key;
	u8 flg;
	u8 chg;
	u8 x_p;
	float tmp;
	float k;
	float tmp_k;

	delay_init();
	uart_init(9600);
	LED_Init();
	LCD_Init();
	T_Adc_Init();
	Remote_Init();

	flg = 0;
	chg = 0;
	x_p = 60;

	POINT_COLOR = RED;
	LCD_ShowString(60, 50, 200, 16, 16, "Mini STM32");
	LCD_ShowString(60, 70, 200, 16, 16, "Temperature TEST");
	LCD_ShowString(60, 90, 200, 16, 16, "CSE@SUSTech 11612706");
	LCD_ShowString(60, 110, 200, 16, 16, "2018/11/27");
	POINT_COLOR = BLUE;
	LCD_ShowString(60, 150, 200, 16, 16, "TEMPERATE 00.00C");

	while (1) {
		POINT_COLOR = BLUE;
		if (chg == 1 && flg == 0) {
			LCD_ShowString(60, 150, 200, 16, 16, "TEMPERATE 00.00C");
			chg = 0;
			LCD_Fill(30, 200, 200, 320, WHITE);
			x_p = 60;
		} else if (chg == 1 && flg == 1) {
			LCD_ShowString(60, 150, 200, 16, 16, "TEMPERATE 00.00F");
			chg = 0;
			LCD_Fill(30, 200, 200, 320, WHITE);
			x_p = 60;
		}
		key = Remote_Scan();
		if (key && flg == 0) {
			flg = 1;
			chg = 1;
		} else if (key && flg == 1) {
			flg = 0;
			chg = 1;
		}
		adcx = T_Get_Adc_Average(ADC_CH_TEMP, 10);
		tmp = (float)adcx * (3.3 / 4096);
		k = tmp;
		adcx = tmp;
		tmp -= (u8)tmp;
		LCD_DrawLine(60, 290, 60, 200);
		LCD_DrawLine(60, 290, 200, 290);
		LCD_ShowString(200, 270, 200, 16, 16, "T/s");
		if (flg == 0) {
			k = (1.43 - k) / 0.0043 + 25;
			LCD_ShowxNum(140, 150, (u8)k, 2, 16, 0);
			tmp_k = k;
			tmp_k -= (u8)tmp_k;
			LCD_ShowxNum(164, 150, tmp_k * 100, 2, 16, 0X80);
			LCD_ShowString(60, 200, 200, 16, 16, "TEMPTURE/C");
			LCD_ShowString(100, 300, 200, 16, 16, "10");
			LCD_ShowString(140, 300, 200, 16, 16, "20");
			LCD_ShowString(180, 300, 200, 16, 16, "30");
			LCD_ShowString(40, 260, 200, 16, 16, "30");
			LCD_ShowString(40, 220, 200, 16, 16, "40");
			LCD_DrawPoint(x_p, (u16)(260 - 4 * (k - 30)));
		} else {
			k = (1.43 - k) / 0.0043 + 25;
			k = k * 1.8 + 32;
			if (k > 100) {
				k -= 100;
				tmp_k = k;
				LCD_ShowxNum(140, 150, (u8)tmp_k, 2, 16, 0);
				LCD_ShowString(133, 150, 200, 16, 16, "10");
				tmp_k -= (u8)tmp_k;
				LCD_ShowxNum(164, 150, tmp_k * 100, 2, 16, 0X80);
				k += 100;
			} else {
				LCD_ShowString(134, 150, 200, 16, 16, " ");
				tmp_k = k;
				LCD_ShowxNum(140, 150, (u8)tmp_k, 2, 16, 0);
				tmp_k -= (u8)tmp_k;
				LCD_ShowxNum(164, 150, tmp_k * 100, 2, 16, 0X80);
			}
			LCD_ShowString(60, 200, 200, 16, 16, "TEMPTURE/F");
			LCD_ShowString(100, 300, 200, 16, 16, "10");
			LCD_ShowString(140, 300, 200, 16, 16, "20");
			LCD_ShowString(180, 300, 200, 16, 16, "30");
			LCD_ShowString(40, 260, 200, 16, 16, "90");
			LCD_ShowString(40, 220, 200, 16, 16, "110");
			LCD_DrawPoint(x_p, (u16)(260 - 2 * (k - 90)));
		}
		x_p += 1;
		if (x_p >= 200)
			chg = 1;
		LED0 = !LED0;
		delay_ms(250);
	}
}
