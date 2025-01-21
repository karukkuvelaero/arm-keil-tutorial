
#include "gpio.h"

int main(void){
	
	
	PinOutputSet(PD13);
	PinOutputSet(PD14);
	PinInputSet(PA0);
	while(1){
	
	PinW(PD14, ON);
	PinW(PD13,PinR(PA0));
	
	
	
	
	
	
}
	
}