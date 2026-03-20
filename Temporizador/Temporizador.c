#include <LPC17xx.h>

#include "..\libfiles\timer.c" 
#include "..\libfiles\gpio.c"

/*
			EJERCICIO DE INTERRUPTORES, PULSADORES Y LEDS
					Autor: Adrián Hernández Lillo
					Asignatura: Servicios Electrónicos Digitales
					
					DESCRIPCIÓN: Script en C que simula un cronómetro digital de 4 bits (0 a 15 segundos). 
					El avance del tiempo se controla mediante interrupciones de hardware (TIMER0) para 
					garantizar una precisión exacta de 1 segundo. El valor actual se representa en formato 
          binario a través de 4 LEDs. La cuenta del temporizador avanza únicamente mientras el 
					Pulsador E4 se mantiene accionado.
					
					- GND  --> GND de la placa
          - VIN  --> +5 Vcc
          - E4   --> P1.30 (Pulsador: Control de Pausa/Reanudación)
          - LED1 --> P1.18 (Representa el Bit 0: 1 seg)
          - LED2 --> P1.20 (Representa el Bit 1: 2 seg)
          - LED3 --> P1.21 (Representa el Bit 2: 4 seg)
          - LED4 --> P1.23 (Representa el Bit 3: 8 seg)
*/


 #define LED1 P1_18
 #define LED2 P1_20
 #define LED3 P1_21
 #define LED4 P1_23
 #define PulsadorE4 P1_30
 
 volatile uint8_t segundos = 0;

void actualizarReloj(void) {
    segundos++; 
    
    if (segundos > 15) {
        segundos = 0;
    }

    if (segundos & 0x01) GPIO_PinWrite(LED1, HIGH); else GPIO_PinWrite(LED1, LOW);
    if (segundos & 0x02) GPIO_PinWrite(LED2, HIGH); else GPIO_PinWrite(LED2, LOW);
    if (segundos & 0x04) GPIO_PinWrite(LED3, HIGH); else GPIO_PinWrite(LED3, LOW);
    if (segundos & 0x08) GPIO_PinWrite(LED4, HIGH); else GPIO_PinWrite(LED4, LOW);
}

int main(){
    
    // 1. Inicialización
    SystemInit();
    
    GPIO_PinDirection(LED1, OUTPUT);
    GPIO_PinDirection(LED2, OUTPUT);
    GPIO_PinDirection(LED3, OUTPUT);
    GPIO_PinDirection(LED4, OUTPUT);
    GPIO_PinDirection(PulsadorE4, INPUT);
    
    // Apagar LEDs al inicio
    GPIO_PinWrite(LED1, LOW);
    GPIO_PinWrite(LED2, LOW);
    GPIO_PinWrite(LED3, LOW);
    GPIO_PinWrite(LED4, LOW);

    // 2. Configurar el TIMER0
    TIMER_Init(TIMER_0, 1000000); // 1.000.000 us = 1 segundo
    TIMER_AttachInterrupt(TIMER_0, actualizarReloj); // Hookear la interrupción
    
    // Arrancar el reloj
    TIMER_Start(TIMER_0);

    // 3. Bucle Principal (Pausa del Reloj)
    while(1){
        // Si el pulsador está activo (imaginemos que un '1' es pulsado)
        if(GPIO_PinRead(PulsadorE4) == 1){
            
            // Pausar el reloj
            TIMER_Stop(TIMER_0);
            
            // Esperamos a que suelte el botón (anti-rebote básico)
            while(GPIO_PinRead(PulsadorE4) == 1){ 
                // Atrapados aquí hasta que suelte el dedo
            }
            
            // Cuando suelta el dedo, el reloj se reanuda
            TIMER_Start(TIMER_0);
        }
    }
}
