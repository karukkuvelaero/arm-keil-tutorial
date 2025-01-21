#include "stm32f4xx.h"
#include "gpio.h"

void GPIOPortInit(char GPIO_port){
	RCC->AHB1ENR |= (1<<GPIO_port);
}

GPIO_TypeDef *get_GPIO(char GPIO_port){
	GPIO_TypeDef *target_port;
	
	switch (GPIO_port)
	{
		case PortA:
			target_port = GPIOA;
			break;
		case PortB:
			target_port = GPIOB;
			break;
		case PortC:
			target_port = GPIOC;
			break;
		#ifdef GPIOD
		case PortD:
			target_port = GPIOD;
			break;
		#endif
		#ifdef GPIOE
		case PortE:
			target_port = GPIOE;
			break;
		#endif
		#ifdef GPIOF
		case PortF:
			target_port = GPIOF;
			break;
		#endif
		#ifdef GPIOG
		case PortG:
			target_port = GPIOG;
			break;
		#endif
		#ifdef GPIOH
		case PortH:
			target_port = GPIOH;
			break;
		#endif
		#ifdef GPIOI
		case PortI:
			target_port = GPIOI;
			break;
		#endif
		#ifdef GPIOJ
		case PortJ:
			target_port = GPIOJ;
			break;
		#endif
		#ifdef GPIOK
		case PortK:
			target_port = GPIOK;
			break;
		#endif
		
	}
	return target_port;

}

void PinModeSet (int PortPin, char mode){
	
	char Port = PortPin /16;
	char Pin = PortPin % 16;
	
	GPIO_TypeDef *GPIO = get_GPIO(Port);
	
	GPIO->MODER &= ~(0x3<<(Pin*2));
	GPIO->MODER |= (mode<<Pin*2);
}
void PinModeOut (int PortPin){
	PinModeSet(PortPin, OUT);
}

void PinModeIn (int PortPin){
	PinModeSet(PortPin, IN);
}

void PinOutputSet(int PortPin){
	char Port = PortPin /16;
	char Pin = PortPin % 16;
	
	GPIO_TypeDef *GPIO = get_GPIO(Port);
	GPIOPortInit(Port);
	PinModeOut(PortPin);
	
	
	GPIO->OTYPER &= ~(0b1<<Pin); //Set the pin as PP
	
	GPIO->OSPEEDR &= ~(0x3<<(Pin*2));
	GPIO->OSPEEDR |= (HS<<Pin*2);
	
}


void PinInputSet(int PortPin){
	char Port = PortPin /16;
	char Pin = PortPin % 16;
	
	GPIO_TypeDef *GPIO = get_GPIO(Port);
	GPIOPortInit(Port);
	PinModeIn(PortPin);
	
	GPIO->OTYPER &= ~(0b1<<Pin); 
	GPIO->PUPDR &= ~(0x3<<Pin*2);
	GPIO->PUPDR |= (PD<<Pin*2);
	
	
}

void PinW(int PortPin, char state){
	char port = PortPin / 16;
	char pin = PortPin % 16;
	GPIO_TypeDef * GPIO = get_GPIO(port);
	
	if(state){
		GPIO->ODR |= 1<<pin;
	}
	else{
		GPIO->ODR &= ~(1<<pin);
	}

	
}


char PinR(int PortPin){
	char port = PortPin / 16;
	char pin = PortPin % 16;
	GPIO_TypeDef * GPIO = get_GPIO(port);
	
	if (GPIO->IDR & (1<<pin)){
		return 0xff;
	}
	else{
		return 0;
	}
	
}

void PinToggle(int PortPin){
	char port = PortPin / 16;
	char pin = PortPin % 16;
	GPIO_TypeDef * GPIO = get_GPIO(port);
	
	PinR(PortPin) ? PinW(PortPin,OFF): PinW(PortPin, ON);
	
}


void PinsSet(int *PinsList, char pinNumber, char state){
	int i;
	for (i=0; i<pinNumber; i++)
	{
		if (state==IN){
			PinInputSet(PinsList[i]);
		}
		else if (state==OUT){
			PinOutputSet(PinsList[i]);
		}		
	}
}
void PinsInputSet(int * PinsList, char pinNumber){
	PinsSet(PinsList, pinNumber, IN);
}

void PinsOutputSet(int * PinsList, char pinNumber){
	PinsSet(PinsList, pinNumber, OUT);
}


void PinIrqStart(int PortPin){
	char port = PortPin/16;
	char Pin = PortPin % 16;
	
	//Enable IRQ clock
	RCC->APB2ENR |= (1<<14);
	
	PinInputSet(PortPin);
	
	char exti = Pin/4;
	char extiPin = Pin % 4;
	
	SYSCFG->EXTICR[exti] &= ~(0xF << extiPin*4);
	SYSCFG->EXTICR[exti] |= (port << extiPin*4);
	
	__disable_irq();
	if(Pin==0)
		{
			NVIC_EnableIRQ(EXTI0_IRQn);
		}
		else if(Pin==1)
		{
			NVIC_EnableIRQ(EXTI1_IRQn);
		}
		else if(Pin==2)
		{
			NVIC_EnableIRQ(EXTI2_IRQn);
		}
		else if(Pin==3)
		{
			NVIC_EnableIRQ(EXTI3_IRQn);
		}
		else if(Pin==4)
		{
			NVIC_EnableIRQ(EXTI4_IRQn);
		}
		else if(Pin<10)
		{
			NVIC_EnableIRQ(EXTI9_5_IRQn);
		}
		else
		{
			NVIC_EnableIRQ(EXTI15_10_IRQn);
		}
	__enable_irq();
		
			// 3 Enable the Interrupt Mask register
		EXTI->IMR |= (1 << Pin);
	
}

void IrqEStart(int PortPin, char Edge){
	PinIrqStart(PortPin);
	char pin = PortPin%16;
	
	if (Edge)
	{
		EXTI->RTSR |= (1<<pin);
	}
	else
	{
		EXTI->FTSR |= (1<<pin);
	}
	
}
void PinIrqRE(int PortPin){
	IrqEStart(PortPin, RisingEdge);
}
void PinIrqFE(int PortPin){
	IrqEStart(PortPin, FallingEdge);
}

void PinIrqRFE(int PortPin){
	IrqEStart(PortPin, RisingEdge);
	IrqEStart(PortPin, FallingEdge);
}

void IrqEStop(int PortPin, char Edge){
	
	char pin = PortPin%16;
	
	if (Edge)
	{
		EXTI->RTSR &= ~(1<<pin);
	}
	else
	{
		EXTI->FTSR &= ~(1<<pin);
	}
	
}

void PinIrqFeStop(int PortPin){
	IrqEStop(PortPin, FallingEdge);
}


void PinIrqReStop(int PortPin){
	IrqEStop(PortPin, RisingEdge);
}

void PinIrqFReStop(int PortPin){
	IrqEStop(PortPin, FallingEdge);
	IrqEStop(PortPin, RisingEdge);
}

void PinIrqStop(int PortPin){
	char Port = PortPin/16;
	char Pin = PortPin % 16;
	char exti = Pin /4 ;
	char extiPin = Pin % 4;
	SYSCFG->EXTICR[exti] &= ~(0xF<<extiPin*4);
	
	EXTI->IMR |= (1<<Pin);
	PinIrqFReStop(PortPin);
	
	__disable_irq();
	if(Pin==0)
		{
			NVIC_DisableIRQ(EXTI0_IRQn);
		}
		else if(Pin==1)
		{
			NVIC_DisableIRQ(EXTI1_IRQn);
		}
		else if(Pin==2)
		{
			NVIC_DisableIRQ(EXTI2_IRQn);
		}
		else if(Pin==3)
		{
			NVIC_DisableIRQ(EXTI3_IRQn);
		}
		else if(Pin==4)
		{
			NVIC_DisableIRQ(EXTI4_IRQn);
		}
		else if(Pin<10)
		{
			NVIC_DisableIRQ(EXTI9_5_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(EXTI15_10_IRQn);
		}
	__enable_irq();
}