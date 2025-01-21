#include "gpio.h"
#include "stm32f4xx.h"
int main(void)
{
	PinIrqRE(PA0);
	
	PinOutputSet(PD12);
	PinOutputSet(PD13);
	
	while(1)
	{
		PinW(PD12, ON);
	}
	
}

void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;
	
	PinToggle(PD13);
	
}
