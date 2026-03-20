# 🚥 Control Básico de Entradas y Salidas (GPIO)

Este proyecto es una introducción al manejo *bare-metal* de los puertos de propósito general (GPIO) en el microcontrolador NXP LPC1768. Implementa secuencias visuales de LEDs (animaciones tipo "coche fantástico") controladas mediante el sondeo (*polling*) continuo de un interruptor y un pulsador físico.

## ⚙️ Conceptos Técnicos Destacados

* **Configuración de GPIO:** Definición de direcciones de pines de forma explícita (`GPIO_PinDirection`) para aislar entradas y salidas.
* **Polling (Sondeo):** Lectura cíclica y bloqueante del estado lógico de los pines en el bucle principal.
* **Control de Flujo Lógico:** Uso de estructuras condicionales anidadas para determinar el sentido de la animación (izquierda-derecha o viceversa) y sobrescribir el estado con una acción prioritaria (encender todos los LEDs).
* **Temporización Básica:** Uso de retardos simples (`DELAY_ms`) para hacer las secuencias perceptibles al ojo humano.

## 🔌 Conexiones de Hardware

| Componente Físico | Pin Físico | Pin LPC1768 | Función Lógica |
| :--- | :--- | :--- | :--- |
| **Pulsador (E4)** | Entrada | `P1.30` | Entrada digital (Prioridad: Enciende todos los LEDs) |
| **Interruptor (E0)**| Entrada | `P1.31` | Entrada digital (Define el sentido de la secuencia) |
| **LED 1** | Salida | `P1.18` | Indicador visual |
| **LED 2** | Salida | `P1.20` | Indicador visual |
| **LED 3** | Salida | `P1.21` | Indicador visual |
| **LED 4** | Salida | `P1.23` | Indicador visual |

> **Nota:** Requiere conexión a GND común y alimentación (+5 Vcc) para los pulsadores externos si no se utilizan los integrados en la placa de desarrollo.

## 🧠 Lógica de Funcionamiento

El firmware evalúa en cada ciclo de reloj el estado de los periféricos de entrada. Si el pulsador `E4` no está presionado (`1`), el sistema comprueba la posición del interruptor `E0`:
* Si `E0 == 1`, ejecuta un barrido ascendente (LED1 -> LED4).
* Si `E0 == 0`, ejecuta un barrido descendente (LED4 -> LED1).
* Si el pulsador `E4` se presiona (`0`), la secuencia se interrumpe y los 4 LEDs se encienden simultáneamente hasta que se libere el botón.

## 📦 Dependencias
* `gpio.c` - Funciones de bajo nivel para escritura/lectura de puertos.
* `delay.c` - Generación de bloqueos de tiempo en milisegundos.
