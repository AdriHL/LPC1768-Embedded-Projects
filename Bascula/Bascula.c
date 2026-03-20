#include <LPC17xx.h>

// Librerías base del proyecto
#include "..\libfiles\gpio.c" 
#include "..\libfiles\adc.c"
#include "..\libfiles\lcd.c"
#include "..\libfiles\delay.c"

/*
            PROYECTO: BÁSCULA DIGITAL SIMULADA (0 - 250 Kg)
                    Autor: Adrián Hernández Lillo
                    Asignatura: Servicios Electrónicos Digitales
                    
                    DESCRIPCIÓN: Script en C para simular una báscula industrial.
                    Se lee el valor analógico de un potenciómetro (0 a 4095) mediante
                    el ADC (Canal 3) y se escala matemáticamente a un peso de 
                    0 a 250 Kg, mostrándolo en tiempo real en la pantalla LCD.
										
                    El código está adaptado al "Setup Universal" 
                    
                    CONEXIONES FÍSICAS (SETUP UNIVERSAL):
                    - Potenciómetro -> PIN 18 (P0_26 / Canal ADC 3)
                    - LCD RS    --> PIN 23 (P2_3)
                    - LCD RW    --> PIN 22 (P2_4)
                    - LCD E     --> PIN 21 (P2_5)
                    - LCD D7(L7)--> PIN 24 (P2_2)
                    - LCD D6(L6)--> PIN 25 (P2_1)
                    - LCD D5(L5)--> PIN 30 (P0_4)
                    - LCD D4(L4)--> PIN 29 (P0_5)
*/

// Mapeo de pines del LCD
#define RS P2_3
#define RW P2_4
#define E  P2_5
#define L7 P2_2
#define L6 P2_1
#define L5 P0_4
#define L4 P0_5 

int main() {
    uint16_t valorADC = 0; 
    uint32_t pesoCalculado = 0;

    SystemInit();

    // 1. Configuración del LCD
    LCD_SetUp(RS, RW, E, P_NC, P_NC, P_NC, P_NC, L4, L5, L6, L7);
    LCD_Init(2, 16);
    LCD_Clear();
    
    // Mensaje de bienvenida
    LCD_GoToLine(1);
    LCD_Printf("  Iniciando...  ");
    LCD_GoToLine(2);
    LCD_Printf(" Bascula Lillo  ");
    DELAY_ms(1500);
    LCD_Clear();

    // 2. Inicialización del ADC (Convertidor Analógico-Digital)
    ADC_Init();

    // 3. Bucle principal de la Báscula
    while(1) {
        
        valorADC = ADC_GetAdcValue(3); 

        // Regla de tres: El ADC va de 0 a 4095. El peso de 0 a 250 Kg.
        pesoCalculado = (valorADC * 250) / 4095;

        // Imprimimos el resultado en el LCD (Línea 1)
        LCD_GoToLine(1);
        LCD_Printf("Peso: %3d Kg    ", pesoCalculado); 
        
        // Imprimimos el valor crudo del sensor (Línea 2) para depuración
        LCD_GoToLine(2);
        LCD_Printf("Sensor: %4d   ", valorADC);

        // Refresco de pantalla cada 200ms
        DELAY_ms(200); 
    }
}
