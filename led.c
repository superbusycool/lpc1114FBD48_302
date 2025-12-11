#include "LPC11xx.h" 
#include "led.h" 


//// 点亮LED
void LED_On(void)
{
    LPC_GPIO1->DATA &= ~(1 << 9);
}
//// 熄灭LED
void LED_Off(void)
{
    LPC_GPIO1->DATA |= (1 << 9);
}

//// 延时函数
//void Delay_1s(void) {
//    int i = SystemCoreClock / 10;  
//    while (--i);                  
//}

// LED初始化
void LED_Init(void)
{
    // 使能GPIO时钟
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6);
    
    // 设置P1.9为输出
    LPC_GPIO1->DIR |= (1UL << 9);
    
    // 初始状态：常亮（输出低电平）<--- 修改部分1：初始输出低电平
    LPC_GPIO1->DATA &= ~(1UL << 9);
}
// LED翻转
void LED_Toggle(void)
{
    LPC_GPIO1->DATA ^= (1 << 9);
}
