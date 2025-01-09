#include "stm32f411xe.h"

#include "gpio.h"


int main(void)
{
	//1- Enable IRQ clock 
	RCC->APB2ENR |= (1 <<14);
//2- Enable external interrupt configuration register
	// PD1 & PA8 as setup as interrupt
	PinInputSet(PA0);
	
	
	SYSCFG-> EXTICR[0] &= ~(0x1);
	
	
	EXTI->IMR |= 0x1;
	
	EXTI->RTSR |= 0x1;
	
	__disable_irq();
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	__enable_irq();
	
	
	PinOutputSet(PD12);
	PinOutputSet(PD13);
	
	while(1)
	{
		PinToggle(PD12);
	}
}
void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;
	PinToggle(PD13);
	
}
