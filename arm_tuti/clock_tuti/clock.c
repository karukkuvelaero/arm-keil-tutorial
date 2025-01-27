#include "stm32f4xx.h"
#include "gpio.h"
#include "clock.h"

void ClockHseON(void){
	RCC->CR |= (1<<16);
	while(!(RCC->CR & (1<<17)));
}

void ClockHseOFF(void){
	RCC->CR &= ~(1<<16);
}

void ClockPllON(void){
	RCC->CR |= (1<<24);
	while(!(RCC->CR & (1<<25)));
}

void ClockPllOFF(void){
	RCC->CR |= ~(1<<24);
}

void ClockMCO1 (char clk, char div){
	//Activate MCO1
	PinOutputSet(PA8);
	PinModeAF(PA8);
	
	//Reading clk
	RCC->CFGR &= ~(0x3<<21);
	RCC->CFGR |= (clk<<21);
	
	//Select Div
		RCC->CFGR &= ~(0x7<<24);
	RCC->CFGR |= (div<<24);
	
}

void ClockMCO2 (char clk, char div){
	//Activate MCO1
	PinOutputSet(PC9);
	PinModeAF(PC9);
	
	//Reading clk
	RCC->CFGR &= ~(0x3<<30);
	RCC->CFGR |= (clk<<30);
	
	//Select Div
		RCC->CFGR &= ~(0x7<<27);
	RCC->CFGR |= (div<<27);
	
}