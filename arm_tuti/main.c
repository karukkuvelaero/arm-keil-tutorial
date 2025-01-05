#include "stm32f4xx.h"


int main(void)
{
	RCC->AHB1ENR |= 0xF;
	
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

	
	GPIOA->OTYPER &= ~0b11;
	GPIOA->OTYPER |= 0b00;
	
	GPIOA->PUPDR &= ~0b11;
	GPIOA->PUPDR |= 0b10;
	
	
	while (1)
	{
	 if (GPIOA->IDR & 0b1)
		 GPIOD->ODR |= (1<<14);
	 else 
		 GPIOD->ODR &= ~(1<<14);
  }
}