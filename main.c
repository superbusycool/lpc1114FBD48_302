#include <LPC11xx.h>
#include <stdio.h>
/* Import external functions from Serial.c file */
extern void SER_init (void);
void LED_Init()
{
    LPC_SYSCON->SYSAHBCLKCTRL |= (1UL << 6);
    LPC_GPIO1->DIR |= (1UL << 9);
    LPC_GPIO1->DATA &= -(1UL << 9);
}
void LED_Toggle(void)
{
    LPC_GPIO1->DATA ^= (1 << 9);
}

void SysTick_Handler(void)
{
    LED_Toggle();
}

int main()
{
		/* UART#1 Initialization  */
    SER_init();
	
    SysTick_Config(SystemCoreClock / 10);
    LED_Init();
    while(1)
    {  
       printf ("hello \n");
    };
}
