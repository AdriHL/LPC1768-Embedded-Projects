#include <LPC17xx.h>
#include "..\libfiles\gpio.c"
#include "..\libfiles\delay.c"
#include "..\libfiles\lcd.c"
#include "..\libfiles\uart.c"
#include "..\libfiles\keypad.c"

/*
            EJERCICIO: COMUNICACIÓN UART ENTRE DOS PLACAS (MODO CHAT - PLACA A)
            Autor: Adrián Hernández Lillo
            Asignatura: Servicios Electrónicos Digitales
            
            Descripción: 
            Implementación de un sistema de comunicación bidireccional por 
            turnos (half-duplex) entre dos microcontroladores LPC1768 a través 
            del periférico UART2. El sistema emplea lectura de teclado y recepción 
            de puerto serie mediante funciones bloqueantes para sincronizar el 
            intercambio de caracteres.
            
            CONEXIONES FÍSICAS (SETUP UNIVERSAL):
            - PLACA A (TX2 - Pin 28) <---> PLACA B (RX2 - Pin 27)
            - PLACA A (RX2 - Pin 27) <---> PLACA B (TX2 - Pin 28)
            - PLACA A (GND)          <---> PLACA B (GND)
            - LCD RS    --> PIN 23 (P2_3)
            - LCD RW    --> PIN 22 (P2_4)
            - LCD E     --> PIN 21 (P2_5)
            - LCD D7(L7)--> PIN 24 (P2_2)
            - LCD D6(L6)--> PIN 25 (P2_1)
            - LCD D5(L5)--> PIN 30 (P0_4)
            - LCD D4(L4)--> PIN 29 (P0_5)
            - TECL F0   --> PIN 13 (P0_15)
            - TECL F1   --> PIN 14 (P0_16)
            - TECL F2   --> PIN 15 (P0_23)
            - TECL F3   --> PIN 16 (P0_24)
            - TECL C0   --> PIN 9  (P0_0)
            - TECL C1   --> PIN 10 (P0_1)
            - TECL C2   --> PIN 11 (P0_18)
            - TECL C3   --> PIN 12 (P0_17)
*/

// --- PINES LCD ---
#define LCD_RS P2_3
#define LCD_RW P2_4
#define LCD_EN P2_5
#define LCD_D7 P2_2
#define LCD_D6 P2_1
#define LCD_D5 P0_4
#define LCD_D4 P0_5

// --- PINES TECLADO ---
#define C0 P0_0
#define C1 P0_1
#define C2 P0_18
#define C3 P0_17
#define F0 P0_15
#define F1 P0_16
#define F2 P0_23
#define F3 P0_24

int main()
{
    char tecla_pulsada;
    char dato_recibido;
    
    // Inicialización del sistema a 100MHz
    SystemInit();
    
    // Configuración de periféricos
    LCD_SetUp(LCD_RS, LCD_RW, LCD_EN, P_NC, P_NC, P_NC, P_NC, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    LCD_Init(2,16);
    KEYPAD_Init(F0, F1, F2, F3, C0, C1, C2, C3);
    
    // Inicialización de UART2 a 19200 baudios
    UART_Init(2, 19200); 
    
    // Mensaje de inicio
    LCD_Clear();
    LCD_Printf("Chat: Placa A");
    DELAY_ms(2000);
    
    while(1)
    {
        // 1. Espera de entrada local por teclado
        LCD_Clear();
        LCD_Printf("Tu turno. Escribe");
        tecla_pulsada = KEYPAD_GetKey();
        
        // Visualización del dato a transmitir
        LCD_Clear();
        LCD_Printf("Tx -> %c", tecla_pulsada);
        
        // 2. Transmisión del carácter por puerto serie (TX2)
        UART_TxChar(2, tecla_pulsada); 
        
        // 3. Espera de respuesta de la placa remota
        LCD_GoToLine(1);
        LCD_Printf("Esperando Rx...");
        
        // La ejecución se bloquea hasta recibir un dato por RX2
        dato_recibido = UART_RxChar(2); 
        
        // 4. Visualización del dato recibido
        LCD_GoToLine(1);
        LCD_Printf("Rx <- %c         ", dato_recibido);
        
        // Retardo para visualización en pantalla
        DELAY_ms(2000); 
    }   
}
