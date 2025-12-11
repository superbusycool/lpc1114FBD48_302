#include <LPC11xx.h>
#include <stdio.h>
#include "main.h"

// 系统时钟频率（48MHz）
#define SYSTEM_CLOCK 48000000

// 全局变量
static uint32_t led_mode = 1;          // LED模式：0-0.5Hz闪烁，1-常亮（初始常亮）
static uint32_t button_pressed = 0;    // 按键按下标志
static uint32_t debounce_counter = 0;  // 防抖计数器
static uint32_t systick_counter = 0;   // SysTick计数器


int main(void)
{
    // 初始化LED
    LED_Init();
    
    // 初始化按键
    BUTTON_Init();
    
    // 配置SysTick定时器为10ms中断
    // SystemCoreClock应该为48000000
    SysTick_Config(SystemCoreClock / 100); // 10ms中断
    
    // 初始状态：常亮
    led_mode = 1;  // 常亮模式
    LED_On();      // 确保LED常亮（输出低电平）<--- 修改部分4：调用LED_On()

    while(1)
    {

			if(!(LPC_GPIO3->DATA & (1UL << 5))){
				while(--debounce_counter);
				if(!(LPC_GPIO3->DATA & (1UL << 5))){
						// 防抖时间到，确认按键按下
						// 读取按键当前状态（确认仍然是按下状态）
						if (!(LPC_GPIO3->DATA & (1UL << 5)))
						{
								// 按键处理：切换LED模式
								if (led_mode == 1) // 当前为常亮模式
								{
										// 切换到0.5Hz闪烁模式
										led_mode = 0;
										systick_counter = 0;  // 重置计数器
										LED_Off();           // 确保从熄灭状态（高电平）开始闪烁 <--- 修改部分5
								}
								else // 当前为0.5Hz闪烁模式
								{
										// 切换到常亮模式
										led_mode = 1;
										LED_On();  // 打开LED常亮（输出低电平）<--- 修改部分6
								}
						}
						

				
				}

			}
                

    }
}

// GPIO3中断处理函数（按键中断）
void PIOINT3_IRQHandler(void)
{
    // 检查是否是P3.5中断
    if (LPC_GPIO3->MIS & (1UL << 5))
    {
        // 清除中断标志
        LPC_GPIO3->IC = (1UL << 5);
        
        // 设置按键按下标志（防抖在主循环中处理）
        button_pressed = 1;
        debounce_counter = 5; // 设置防抖时间约20ms
    }
}

// SysTick中断处理函数
void SysTick_Handler(void)
{
    // 只有在0.5Hz闪烁模式下才需要处理
    if (led_mode == 0) // 0.5Hz闪烁模式
    {
        systick_counter++;
        
        // 0.5Hz：周期2秒，每1秒翻转一次LED
        // SysTick为10ms中断，100次为1秒
        if (systick_counter >= 100) // 1秒
        {
            LED_Toggle();  // 这个函数会自动翻转高低电平
            systick_counter = 0;
        }
    }
}


