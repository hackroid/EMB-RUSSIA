#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//外部中断 驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/01
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//外部中断初始化函数
void EXTIX_Init(void) {

    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

    KEY_Init();//初始化按键对应io模式

    //GPIOC.5 中断线以及中断初始化配置
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

    EXTI_InitStructure.EXTI_Line=EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);     //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.15    中断线以及中断初始化配置
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

    EXTI_InitStructure.EXTI_Line=EXTI_Line15;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);     //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.0     中断线以及中断初始化配置
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);     //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器



    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;          //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;    //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;                   //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                               //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);       //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;          //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04;    //抢占优先级，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                  //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);


    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;            //使能按键所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;    //抢占优先级，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;                   //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);

}
int LED0itr = 0;
void EXTI0_IRQHandler(void) {
    delay_ms(10);    //消抖
    if(WK_UP==1) {
		LED0 = 0;
		TIM_SetCompare1(TIM1, 300);
        printf("KEY WK_UP pressed\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}
int a=-300;
int i;
void EXTI9_5_IRQHandler(void) {
    delay_ms(10);   //消抖
    if(KEY0==0) {
        printf("KEY0 pressed\r\n");
		for(i=0;i<10;i++) {
			TIM_SetCompare1(TIM1, a);
			a=-a;
			delay_ms(100);
		}
    }
    EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位
}

void EXTI15_10_IRQHandler(void) {
    delay_ms(10);    //消抖
    if(KEY1==0) {
		printf("KEY1 pressed\r\n");
        LED1 = 0;
		delay_ms(100);
		LED1 = 1;
		delay_ms(100);
		LED1 = 0;
		delay_ms(100);
		LED1 = 1;
		delay_ms(100);
		LED1 = 0;
		delay_ms(100);
		LED1 = 1;
		delay_ms(100);
		LED1 = 0;
		delay_ms(100);
		LED1 = 1;
		delay_ms(100);
		LED1 = 0;
		delay_ms(100);
		LED1 = 1;
		delay_ms(100);
    }
    EXTI_ClearITPendingBit(EXTI_Line15);  //清除LINE15线路挂起位
}
