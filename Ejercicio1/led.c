#include <LPC17xx.h>

#include "..\libfiles\gpio.c"
#include "..\libfiles\delay.c"

int main(){
	SystemInit(); // inicializa el sistema de acuerdo con los parámetros necesarios
	GPIO_PinDirection(P1_18,OUTPUT);
	
	while (1){
		GPIO_PinWrite(P1_18,HIGH);
		DELAY_ms(1000);
		GPIO_PinWrite(P1_18,LOW);
		DELAY_ms(1000);
	}
}
