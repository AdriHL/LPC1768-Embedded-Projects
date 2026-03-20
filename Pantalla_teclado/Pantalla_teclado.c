#include <LPC17xx.h>

#include "..\libfiles\delay.c"
#include "..\libfiles\gpio.c"
#include "..\libfiles\lcd.c"
#include "..\libfiles\keypad.c"

/*
            EJERCICIO: PRUEBA DE PANTALLA Y TECLADO (SETUP UNIVERSAL)
                    Autor: Adrián Hernández Lillo
                    Asignatura: Servicios Electrónicos Digitales
                    
                    DESCRIPCIÓN: Script en C para imprimir en la pantalla LCD mediante 
                    el uso del teclado matricial 4x4.
                    Adaptado al "Setup Universal"
                    
                    
                    CONEXIONES FÍSICAS (SETUP UNIVERSAL):
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

 // ---PANTALLA (MODO 4 PINES)---
 #define RS P2_3    //PIN 23
 #define RW P2_4    //PIN 22
 #define E  P2_5    //PIN 21
 
 #define L7 P2_2    //PIN 24
 #define L6 P2_1    //PIN 25
 #define L5 P0_4    //PIN 30
 #define L4 P0_5    //PIN 29
 
 // --TECLADO---
 #define C0 P0_0    //PIN 9
 #define C1 P0_1    //PIN 10
 #define C2 P0_18   //PIN 11
 #define C3 P0_17   //PIN 12
 
 #define F0 P0_15   //PIN 13
 #define F1 P0_16   //PIN 14
 #define F2 P0_23   //PIN 15
 #define F3 P0_24   //PIN 16
 

int main(){
    
    // Iniciamos
    uint8_t key;
    char fila, col;
    
    // Es importante iniciar el reloj del sistema a su velocidad normal
    SystemInit(); 
    
    LCD_SetUp(RS, RW, E, P_NC, P_NC, P_NC, P_NC, L4, L5, L6, L7);
    LCD_Init(2,16);
    
    KEYPAD_Init(F0, F1, F2, F3, C0, C1, C2, C3);
    LCD_Printf("Prueba Teclado");
    LCD_GoToLine(1);
    
    // Leer por teclado e imprimir por pantalla 2 digitos en la fila 2 del LCD
    while(1){
        
        fila=1;
        col=1; // Posición 1 de la segunda línea
        key = KEYPAD_GetKey();
        LCD_SetCursor(fila,col);
        LCD_DisplayChar(key & 0xff);
        
        fila=1;
        col=2; // Posición 2 de la segunda línea
        key = KEYPAD_GetKey();
        LCD_SetCursor(fila,col);
        LCD_DisplayChar(key & 0xff);
        
        // Al terminar, el bucle vuelve a empezar sobrescribiendo la posición 1 y luego la 2
    }
}
