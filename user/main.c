#include "stm32f10x.h"

static void delay(volatile uint32_t n){while(n--);}
int main(void)
{	
	/* 1. 开时钟：不开时钟，后面所有寄存器写入都无效 —— 这是新手第一号坑 */
		//不想看寄存器配置了就跳过了
		//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  /* 2. PA0~PA7 配成通用推挽输出 50MHz：每引脚 4 bit，值为 0x3 */
		GPIOA->CRL = 0x33333333;        /* PA8~PA15 在 CRH，别写错寄存器 */
		for(;;){
			for(uint32_t i=0;i<6;i++){
				GPIOA->BSRR = 0x000000FFu << 16;
				GPIOA->BSRR = 1u << i;
				delay(500000); //上面的延迟函数吧
			}
			/* 反向：PA4 → PA1（两端不重复） */
		for(uint32_t i =4;i>0;i--){
			GPIOA->BSRR = 0x000000FFu << 16;
			GPIOA->BSRR = 1u << i;
			delay(500000);
		}
		}
}