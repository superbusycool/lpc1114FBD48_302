#include <LPC11xx.h>
#include <stdio.h>
#include "key.h"

#define INT_TIME_1MS SystemCoreClock / 1000   //基础时间 | 1ms
#define BASIC_FREQUENCY 2000                  //基础频率 | 0.5Hz

void GPIO_Clock_Init(void){
	LPC_SYSCON->SYSAHBCLKCTRL |= 
			(1UL << 6)|(1UL << 16);           // 启用GPIO和IO配置时钟
}


// BUTTON按键初始化
void BUTTON_Init(void)
{
    // 使能GPIO时钟
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6);
    
    // 设置P3.5为输入
    LPC_GPIO3->DIR &= ~(1UL << 5);
    
    // 使能滞后模式（防抖功能）
    LPC_IOCON->PIO3_5 |= (1UL << 1);
    
    // 配置GPIO中断
    LPC_GPIO3->IS &= ~(1UL << 5);     // 边沿触发
    LPC_GPIO3->IBE &= ~(1UL << 5);    // 单边沿触发
    LPC_GPIO3->IEV &= ~(1UL << 5);    // 下降沿触发
    LPC_GPIO3->IE |= (1UL << 5);      // 使能中断
    
    // 使能GPIO中断
    NVIC_EnableIRQ(EINT3_IRQn);
}


