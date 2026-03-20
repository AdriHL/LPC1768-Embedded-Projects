#include <LPC17xx.h>

// Librerías base del proyecto
#include "..\libfiles\gpio.c"
#include "..\libfiles\pwm.c"
#include "..\libfiles\lcd.c"
#include "..\libfiles\delay.c"

/*
            EJERCICIO: CONTROL DE BRILLO LED CON PWM Y LCD (En Porcentaje)
                    Autor: Adrián Hernández Lillo
                    Asignatura: Servicios Electrónicos Digitales
                    
                    DESCRIPCIÓN: Script para variar el brillo de un LED usando el 
                    módulo PWM por hardware (Canal 1) desde un valor máximo (100%) 
                    hasta un mínimo (0%). El valor porcentual actual se muestra en 
                    tiempo real en la pantalla LCD.
                    El código está adaptado al "Setup Universal"
                    
                    CONEXIONES FÍSICAS (SETUP UNIVERSAL):
                    - LED (PWM) --> PIN 26 (P2_0 / Canal PWM_1)
                    - LCD RS    --> PIN 23 (P2_3)
                    - LCD RW    --> PIN 22 (P2_4)
                    - LCD E     --> PIN 21 (P2_5)
                    - LCD D7(L7)--> PIN 24 (P2_2)
                    - LCD D6(L6)--> PIN 25 (P2_1)
                    - LCD D5(L5)--> PIN 30 (P0_4)  
                    - LCD D4(L4)--> PIN 29 (P0_5)
*/

#define RS P2_3
#define RW P2_4
#define E  P2_5
#define L7 P2_2
#define L6 P2_1
#define L5 P0_4  
#define L4 P0_5

int main() {
    int i; 
    int porcentaje; // Nueva variable para guardar el cálculo de 0 a 100

    SystemInit();

    LCD_SetUp(RS, RW, E, P_NC, P_NC, P_NC, P_NC, L4, L5, L6, L7);
    LCD_Init(2, 16);
    LCD_Clear();
    LCD_Printf("Control Brillo");
    
    PWM_Init(255);
    PWM_Start(PWM_1);

    while (1) {
        // --- FASE 1: Apagando gradualmente ---
        for (i = 255; i >= 0; i--) {
            // El hardware del PWM sigue necesitando el valor de 0 a 255
            PWM_SetDutyCycle(PWM_1, i);
            
            // Calculamos el porcentaje para el usuario
            porcentaje = (i * 100) / 255;
            
            // Actualizamos la pantalla. Usamos %% para pintar el símbolo '%'
            LCD_GoToLine(1);
            LCD_Printf("Brillo: %3d %%   ", porcentaje); 
            
            DELAY_ms(15); 
        }

        DELAY_ms(500); 

        // --- FASE 2: Encendiendo gradualmente ---
        for (i = 0; i <= 255; i++) {
            // Mandamos el valor crudo al hardware
            PWM_SetDutyCycle(PWM_1, i);
            
            // Calculamos el porcentaje para el usuario
            porcentaje = (i * 100) / 255;
            
            // Actualizamos la pantalla
            LCD_GoToLine(1);
            LCD_Printf("Brillo: %3d %%   ", porcentaje);
            
            DELAY_ms(15);
        }
        
        DELAY_ms(500); 
    }
}
