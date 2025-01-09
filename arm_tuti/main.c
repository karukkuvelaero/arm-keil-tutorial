#include "stm32f4xx.h"


int main(void)
{
	RCC->AHB1ENR |= 0xF;
	
	//Enabling IRQ clock
	RCC->APB2ENR |= (1<<14);
	
	//Pin PD12
	
	GPIOD->MODER |= 0b01<<(12*2);
	
	GPIOD->OTYPER &= ~(1<<12);
	GPIOD->OTYPER |= (0b0<<12);
	
	GPIOD->ODR |= (1<<12);
	
	//Pin PD13
	GPIOD->MODER |= 0b01<<(13*2);
	
	GPIOD->OTYPER &= ~(1<<13);
	GPIOD->OTYPER |= (0b0<<13);
	
	GPIOD->ODR |= (1<<13);
	
	//PinPD14
	
	GPIOD->MODER |= 0b01<<(14*2);
	
	GPIOD->OTYPER &= ~(1<<14);
	GPIOD->OTYPER |= (0b0<<14);
	
	
	
	//Pin PA0
	
	GPIOA->MODER &= ~0b1;

	

	
	GPIOA->PUPDR &= ~0b11;
	GPIOA->PUPDR |= 0b10 << (0*2);
	
	
	//Enable interrupt configuration register
	SYSCFG->EXTICR[0] &= ~(0x1);
	
	//enable interrupt configuration register
	EXTI->IMR |= 0x1;
	
	//select the interrupt trigger
	EXTI-> RTSR |= 0x1;
	
	//NVIC Enable
	__disable_irq();
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	__enable_irq();
	
	
	while (1)
	{
		
		 GPIOD->ODR &= ~(1<<14);
		
  }
}

void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;
	GPIOD->ODR |= (1<<14);
}