#include <LPC17xx.h>

#include "..\libfiles\gpio.c"
#include "..\libfiles\lcd.c"
#include "..\libfiles\delay.c"

/*
            EJERCICIO: PARPADEO LED CON RIT Y DOBLE INTERRUPCIÓN POR GPIO
            Autor: Adrián Hernández Lillo
            Asignatura: Servicios Electrónicos Digitales
            
            Descripción: 
            Control de la velocidad de parpadeo del LED1 integrado mediante 
            el temporizador RIT. El ajuste se realiza mediante dos pulsadores 
            configurados como interrupciones externas por GPIO (EINT3). El 
            pulsador E6 incrementa la velocidad (hasta 4/4) y el E7 la decrementa 
            (hasta 1/4). Se implementa rutina anti-rebote por software y 
            reinicio del timer en cada cambio para evitar overflow.
            
            CONEXIONES FÍSICAS (SETUP UNIVERSAL):
            - LED1      --> Integrado en placa (P1_18)
            - PULS_INC  --> PIN 7 (P0_7) (Pulsador E6 - Incrementa)
            - PULS_DEC  --> PIN 8 (P0_6) (Pulsador E7 - Decrementa)
            - LCD RS    --> PIN 23 (P2_3)
            - LCD RW    --> PIN 22 (P2_4)
            - LCD E     --> PIN 21 (P2_5)
            - LCD D7(L7)--> PIN 24 (P2_2)
            - LCD D6(L6)--> PIN 25 (P2_1)
            - LCD D5(L5)--> PIN 30 (P0_4)
            - LCD D4(L4)--> PIN 29 (P0_5)
*/

// --- PINES LCD ---
#define LCD_RS P2_3
#define LCD_RW P2_4
#define LCD_EN P2_5
#define LCD_D7 P2_2
#define LCD_D6 P2_1
#define LCD_D5 P0_4
#define LCD_D4 P0_5

// --- PINES HARDWARE ---
#define LED1 P1_18
#define PULS_INC P0_7 // Pin 7
#define PULS_DEC P0_6 // Pin 8

// Variables globales volátiles (modificadas en las ISR)
volatile uint8_t nivel_velocidad = 1;
volatile uint8_t actualizar_pantalla = 1;

// Prototipos de las ISR
void RIT_IRQHandler(void);
void EINT3_IRQHandler(void);

int main(void) {
    
    // Inicialización del sistema a 100MHz
    SystemInit(); 
    
    // Activación de alimentación del periférico RIT
    LPC_SC->PCONP |= (1 << 16);
    
    // Configuración inicial de la pantalla LCD
    LCD_SetUp(LCD_RS, LCD_RW, LCD_EN, P_NC, P_NC, P_NC, P_NC, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    LCD_Init(2,16);
    LCD_Clear();
    LCD_Printf("Control RIT");
    
    // Configuración del hardware local
    GPIO_PinDirection(LED1, OUTPUT); 
    GPIO_PinWrite(LED1, LOW);
    
    GPIO_PinDirection(PULS_INC, INPUT);
    GPIO_PinDirection(PULS_DEC, INPUT);
    
    // --- Configuración del Timer RIT ---
    LPC_RIT->RICOUNTER = 0x00;           // Reset del contador
    LPC_RIT->RIMASK = 0x00;              // Sin máscara de comparación
    LPC_RIT->RICOMPVAL = 25000000;       // Valor inicial: 1 segundo
    LPC_RIT->RICTRL |= (0x1 << 1);       // Enable clear on match (auto-reset)
    LPC_RIT->RICTRL |= (0x1 << 0);       // Limpieza de flags pendientes
    LPC_RIT->RICTRL |= (0x1 << 3);       // Habilitar Timer
    
    NVIC_EnableIRQ(RIT_IRQn);            
    
    // --- Configuración Interrupciones Externas (GPIO) ---
    LPC_GPIOINT->IO0IntClr = (1 << 6) | (1 << 7);   // Limpiar interrupciones pendientes en P0.6 y P0.7
    LPC_GPIOINT->IO0IntEnF |= (1 << 6) | (1 << 7);  // Habilitar interrupciones por flanco de bajada
    NVIC_EnableIRQ(EINT3_IRQn); 
    
    // Bucle principal
    while(1) {
        
        // Refresco condicional de la pantalla para no saturar el LCD
        if (actualizar_pantalla == 1) {
            LCD_GoToLine(1);
            LCD_Printf("Velocidad: %d/4 ", nivel_velocidad);
            actualizar_pantalla = 0; 
        }
        
        // Retardo para liberar carga del procesador
        DELAY_ms(50);
    }
}

// ------------------------------------------------------------------------
// RUTINAS DE SERVICIO DE INTERRUPCIÓN (ISR)
// ------------------------------------------------------------------------

// ISR del Timer RIT (Controla el toggle del LED)
void RIT_IRQHandler(void) {
    
    // Limpiar flag de interrupción
    LPC_RIT->RICTRL |= (0x1 << 0); 
    GPIO_PinToggle(LED1); 
}

// ISR de Interrupciones GPIO (Comparte el vector EINT3)
void EINT3_IRQHandler(void) {
    uint8_t cambio_realizado = 0;
    
    // Verificar si la interrupción proviene del Pulsador E6 (Incremento - P0.7)
    if (LPC_GPIOINT->IO0IntStatF & (1 << 7)) {
        if (nivel_velocidad < 4) {
            nivel_velocidad++;
            cambio_realizado = 1;
        }
    }
    
    // Verificar si la interrupción proviene del Pulsador E7 (Decremento - P0.6)
    if (LPC_GPIOINT->IO0IntStatF & (1 << 6)) {
        if (nivel_velocidad > 1) {
            nivel_velocidad--;
            cambio_realizado = 1;
        }
    }
    
    // Aplicar los cambios en el temporizador solo si la velocidad ha sido modificada
    if (cambio_realizado == 1) {
        
        // Actualización del registro de comparación según el nivel
        if(nivel_velocidad == 1) LPC_RIT->RICOMPVAL = 25000000; // 1s
        if(nivel_velocidad == 2) LPC_RIT->RICOMPVAL = 12500000; // 0.5s
        if(nivel_velocidad == 3) LPC_RIT->RICOMPVAL = 6250000;  // 0.25s
        if(nivel_velocidad == 4) LPC_RIT->RICOMPVAL = 3000000;  // 0.12s
        
        // Reset del contador para aplicar la nueva velocidad inmediatamente
        LPC_RIT->RICOUNTER = 0x00; 
        
        actualizar_pantalla = 1; 
    }
    
    // Debounce por software (anti-rebotes)
    DELAY_ms(50); 
    
    // Limpiar los flags de ambas interrupciones tras el delay para ignorar rebotes
    LPC_GPIOINT->IO0IntClr = (1 << 6) | (1 << 7);
}
