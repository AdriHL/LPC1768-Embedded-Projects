#include <LPC17xx.h>

#include "..\libfiles\delay.c"
#include "..\libfiles\gpio.c"
#include "..\libfiles\lcd.c"
#include "..\libfiles\keypad.c"

/*
            EJERCICIO: CALCULADORA LLM (SETUP UNIVERSAL)
                    Autor: Adrián Hernández Lillo
                    Asignatura: Servicios Electrónicos Digitales
                    
                    DESCRIPCIÓN: Script en C que simula una calculadora básica 
                    utilizando un teclado matricial 4x4 y una pantalla LCD. 
                    Permite sumar, restar, multiplicar y dividir (con control de 
                    error por división entre cero).
                    
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
 
 // --TECLADO--- (Se mantienen intactos, no hay conflicto)
 #define C0 P0_0    //PIN 9
 #define C1 P0_1    //PIN 10
 #define C2 P0_18   //PIN 11
 #define C3 P0_17   //PIN 12
 
 #define F0 P0_15   //PIN 13
 #define F1 P0_16   //PIN 14
 #define F2 P0_23   //PIN 15
 #define F3 P0_24   //PIN 16
 
void mostrarResultado(int32_t valor);

int main(){
    
    // Iniciamos
    uint8_t key;
    SystemInit();
    
    // Usamos int32_t (entero CON signo) para poder tener resultados negativos
    int32_t num1 = 0;
    int32_t num2 = 0;
    int32_t resultado = 0;
    char operador = 0;
    int estado = 0; // 0 = leyendo num1, 1 leyendo num2
    
    LCD_SetUp(RS, RW, E, P_NC, P_NC, P_NC, P_NC, L4, L5, L6, L7);
    LCD_Init(2,16);
    KEYPAD_Init(F0, F1, F2, F3, C0, C1, C2, C3);
    
    LCD_Printf("CalculadoraLLM");  
    LCD_GoToLine(1);            
    
    // Leer por teclado e imprimir por pantalla
    while(1){
        key = KEYPAD_GetKey();

        //Lectura de digitos
        if (key >= '0' && key <= '9'){
            LCD_DisplayChar(key); 
            
            if (estado == 0){
                num1 = (num1 * 10) + (key - '0');
            } else {
                num2 = (num2 * 10) + (key - '0');
            }
            
        } else if (key == '+' || key == '-' || key == 'x' || key == '/') { 
            LCD_DisplayChar(key); 
            operador = key;       
            estado = 1;            

        } else if (key == '#') { 
                LCD_DisplayChar('='); 
                
                // Hacemos el cálculo
                if (operador == '+') {
                    resultado = num1 + num2;
                    mostrarResultado(resultado); 
                } else if (operador == '-'){
                    resultado = num1 - num2;
                    mostrarResultado(resultado);  
                } else if (operador == 'x'){
                    resultado = num1 * num2;
                    mostrarResultado(resultado);  
                } else if (operador == '/'){

                    if (num2 != 0) {
                        resultado = num1 / num2;
                        mostrarResultado(resultado);
                    } else {
                        LCD_Printf(" Error"); 
                    }
                }
                
                // --- REINICIO DE LA CALCULADORA ---
                KEYPAD_GetKey();
                LCD_Clear();     
                LCD_Printf("CalculadoraLLM");
                LCD_GoToLine(1); 
                
                // Reseteamos variables para la siguiente cuenta
                num1 = 0;
                num2 = 0;
                resultado = 0;
                estado = 0;
        }
    }
}

void mostrarResultado(int32_t valor) {

    LCD_Clear(); 
    LCD_Printf("Datos capturados"); 
    LCD_GoToLine(1); 
    LCD_Printf("Por favor espere"); 
    
    DELAY_ms(1500); 
    

    LCD_Clear(); 
    LCD_Printf("Ejecutando LLM.."); 
    LCD_GoToLine(1); 
    LCD_Printf("Pensando...     "); 
    
    DELAY_ms(2000);
    
    LCD_Clear(); 
    LCD_Printf("El resultado es:"); 
    LCD_GoToLine(1); 
   
    LCD_Printf("%d", valor); 
}
