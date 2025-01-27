
#include "clock.h"

int main (void){
	
	/*
	//Activate MCO2
	 PinOutputSet(PC9);
	PinModeAF(PC9);
		RCC->CFGR &= ~ (0x3<<30);
	RCC->CFGR |= (0x3 <<30);
	RCC->CFGR |= (0x7<<27);
	
	RCC->CR |= (1<<16);//enabling HSE
	while(!(RCC->CR & (1<<17)));
	
	RCC->PLLCFGR &= ~(0x3F);//clearing M
	RCC->PLLCFGR |= (0x4);//setting M value =4
	RCC->PLLCFGR &= ~(0x1FF<<6);//clearing N values
	RCC->PLLCFGR |= (0x60<<6);//setting N value
	
	RCC->PLLCFGR &= ~(0x3<<16);
	RCC->PLLCFGR |= 0x3<<16;
	
	RCC->CR |= (1<<24);//enabling PLL
	
	while(!(RCC->CR & (1<<25)));
	
	
	
	
	//Activate MCO1
	PinOutputSet(PA8);
	PinModeAF(PA8);
	RCC->CFGR &= ~ (0x3<<21);
	RCC->CFGR |= (0x2 << 21);
	*/
	
	ClockHseON();
	ClockPllON();
	ClockMCO1(HSE, MCO_DIV_2);

	
}