# 🖥️ Interfaz HMI Básica: Pantalla y Teclado

Este proyecto establece y valida las bases de comunicación *bare-metal* entre el LPC1768 y dos periféricos de Interfaz Humano-Máquina (HMI) fundamentales: un display LCD 16x2 (operando en modo 4 bits) y un teclado matricial 4x4.

## ⚙️ Características Técnicas

* **Multiplexación de Entradas:** Escaneo continuo por software de una matriz de 16 botones usando solo 8 pines del microcontrolador.
* **Comunicación de 4-bits:** Ahorro de puertos I/O al enviar comandos y caracteres a la pantalla LCD utilizando medios bytes (nibbles).
* **Control de Cursor Absoluto:** Manipulación directa del registro de direcciones DDRAM del controlador HD44780 para imprimir datos en posiciones exactas de la pantalla.

## 🔌 Pinout y Conexiones (Setup Universal)

| Componente Físico | Pin LPC1768 | Función Lógica |
| :--- | :--- | :--- |
| **LCD Control** | `P2.3`, `P2.4`, `P2.5` | RS, RW, EN |
| **LCD Bus Datos** | `P0.5`, `P0.4`, `P2.1`, `P2.2` | D4 a D7 |
| **Teclado Filas** | `P0.15`, `P0.16`, `P0.23`, `P0.24`| F0 a F3 (Salidas de escaneo) |
| **Teclado Columnas**| `P0.0`, `P0.1`, `P0.18`, `P0.17` | C0 a C3 (Entradas digitales) |

## 🧠 Flujo de Ejecución

1. Tras la inicialización del sistema de relojes a 100MHz, el microcontrolador prepara el bus de datos y envía las secuencias de inicio estándar al controlador del LCD.
2. El sistema entra en un bucle infinito donde se queda bloqueado esperando una pulsación (`KEYPAD_GetKey()`).
3. Una vez detectada la tecla, se aplica una máscara de bits `(key & 0xff)` para garantizar la compatibilidad del carácter ASCII y se envía a la primera posición de la segunda línea de la pantalla.
4. El proceso se repite para la segunda posición, sobrescribiendo continuamente estos dos espacios para demostrar la actualización dinámica de memoria de video (DDRAM).

## 📦 Dependencias (HAL)
* `keypad.c` - Rutinas de escaneo matricial.
* `lcd.c` - Protocolo de comunicación para displays compatibles con HD44780.
* `gpio.c` y `delay.c` - Funciones base del sistema.
