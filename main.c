/**************** 头文件调用&&宏定义 ****************/
#include <LPC11xx.h>
#include <stdio.h>
#include "main.h"


/******************* 全局变量定义 *******************/
#define BUFSIZE	  10
extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];	

/********************** 函数声明 ********************/
__STATIC_INLINE void delay_ms(uint32_t a);  // 用__STATIC_INLINE（ARMCC推荐）

/********************** 函数定义 ********************/
/****************************************************
*名  称：	延时函数    							*
*参  数：   延时时间								*
*备  注：	内联函数（ARMCC兼容）    				*
*****************************************************/
__STATIC_INLINE void delay_ms(uint32_t a)    // 1ms延时函数
{                           
    uint32_t i;
    while( --a != 0){
        for(i = 0; i<5500; i++);
    }             
}
/********************** 主函数 **********************/

int main(void)
{
	SER_init();
 	SystemInit();	  			//系统初始化，包括使能时钟
	UARTInit(115200);			//初始化波特率为115200
	#if MODEM_TEST				
  	ModemInit();
	#endif
	while(1)
	{	 
		if ( UARTCount != 0 )	//将发送的数据返回
		{
	  		LPC_UART->IER = IER_THRE | IER_RLS;			// Disable RBR 
	  		UARTSend( (uint8_t *)UARTBuffer, UARTCount );
	  		UARTCount = 0;
	  		LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	// Re-enable RBR 
		}
		UARTSend("贞明电子：http://shop58972409.taobao.com\r\n",42);
		delay_ms(1000);
	}
}


