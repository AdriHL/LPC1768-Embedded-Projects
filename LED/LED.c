#include <LPC17xx.h>

#include "..\libfiles\delay.c"
#include "..\libfiles\gpio.c"

/*
			EJERCICIO DE INTERRUPTORES, PULSADORES Y LEDS
					Autor: Adrián Hernández Lillo
					Asignatura: Servicios Electrónicos Digitales
					
					DESCRIPCIÓN: Script en C para controlar los led de forma progresiva y controlar el el sentido
					mediante la posicion del interruptor (E0) ademas de poder encender todos los leds de la placa
					durante el tiempo que se mantenaga pulsado el pulsador (E4)
					
					CONEXIONES:
					- GND --> GND
					- VIN --> +5 Vcc
					- E0	--> P0_0
					- E4	--> P0_1
*/

 #define LED1 P1_18
 #define LED2 P1_20
 #define LED3 P1_21
 #define LED4 P1_23
 #define InterruptorE0 P1_31
 #define PulsadorE4 P1_30
 

int main(){
	
	// Iniciamos
	SystemInit();
	
	//Declarar el modo entrada/salida
	GPIO_PinDirection(LED1,OUTPUT);
	GPIO_PinDirection(LED2,OUTPUT);
	GPIO_PinDirection(LED3,OUTPUT);
	GPIO_PinDirection(LED4,OUTPUT);
	
	GPIO_PinDirection(InterruptorE0,INPUT);
	GPIO_PinDirection(PulsadorE4,INPUT);
	
	while(1){
		if(GPIO_PinRead(PulsadorE4)==1){
		
			if(GPIO_PinRead(InterruptorE0)==1){
				GPIO_PinWrite(LED1,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED1,LOW);
				
				GPIO_PinWrite(LED2,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED2,LOW);
				
				GPIO_PinWrite(LED3,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED3,LOW);
				
				GPIO_PinWrite(LED4,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED4,LOW);
			}else if (GPIO_PinRead(InterruptorE0)==0){
				
				GPIO_PinWrite(LED4,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED4,LOW);
				
				GPIO_PinWrite(LED3,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED3,LOW);
				
				GPIO_PinWrite(LED2,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED2,LOW);
				
				GPIO_PinWrite(LED1,HIGH);
				DELAY_ms(100);
				GPIO_PinWrite(LED1,LOW);
			}
		}else if(GPIO_PinRead(PulsadorE4)==0){
			GPIO_PinWrite(LED1,HIGH);
			GPIO_PinWrite(LED2,HIGH);
			GPIO_PinWrite(LED3,HIGH);
			GPIO_PinWrite(LED4,HIGH);
		}
	}
}
