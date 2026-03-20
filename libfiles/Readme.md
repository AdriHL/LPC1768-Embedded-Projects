# 🧰 Custom HAL (Hardware Abstraction Layer) - LPC1768

Bienvenido al núcleo de este repositorio. Esta carpeta contiene una **Capa de Abstracción de Hardware (HAL)** desarrollada completamente desde cero (*bare-metal*) para el microcontrolador NXP LPC1768 (ARM Cortex-M3).

El objetivo de esta librería modular es encapsular la complejidad de la manipulación directa de registros (CMSIS) y proporcionar interfaces limpias, reutilizables y estandarizadas para todos los proyectos del portfolio.

## 🏗️ Arquitectura de la Librería

La librería está diseñada siguiendo el principio DRY (*Don't Repeat Yourself*), separando la lógica de control de los periféricos de la lógica de aplicación de cada proyecto.

Los módulos se dividen en las siguientes categorías:

### 1. Control del Sistema y Tiempos
| Módulo | Descripción |
| :--- | :--- |
| `gpio.c` / `.h` | Control absoluto de puertos, direcciones y estados lógicos (High/Low/Toggle). |
| `delay.c` / `.h` | Temporización por software y generación de bloqueos precisos en milisegundos/microsegundos. |
| `timer.c` / `.h` | Control del periférico TIMER por hardware (Match registers e Interrupciones). |
| `systick.c` / `.h`| Configuración del System Tick Timer nativo del núcleo ARM Cortex-M3. |
| `rtc.c` / `.h` | Gestión del Real-Time Clock interno. |
| `extintr.c`/ `.h`| Configuración de interrupciones externas (EINT) mediante hardware. |

### 2. Protocolos de Comunicación
| Módulo | Descripción |
| :--- | :--- |
| `uart.c` / `.h` | Driver asíncrono serie (UART) para Tx/Rx con cálculo de baudrates. |
| `spi.c` / `.h` | Bus de comunicación síncrona de alta velocidad. |
| `softi2c.c`/ `.h`| Implementación del protocolo I2C por software (Bit-banging). |

### 3. Señales Analógicas y Control
| Módulo | Descripción |
| :--- | :--- |
| `adc.c` / `.h` | Lectura de canales analógicos y conversión a digital (12-bit). |
| `pwm.c` / `.h` | Generación de señales de Modulación por Ancho de Pulso por hardware. |

### 4. Interfaz Humano-Máquina (HMI)
| Módulo | Descripción |
| :--- | :--- |
| `lcd.c` / `.h` | Controlador completo para pantallas tipo HD44780 (Modo 4-bits) con formateo integrado. |
| `keypad.c` / `.h`| Sistema de escaneo matricial con multiplexación para teclados (ej. 4x4). |
| `stdutils.h` | Macros y utilidades estándar de conversión y mapeo de datos. |

## 🚀 Uso e Integración en Proyectos

Para maximizar la simplicidad y evitar configuraciones complejas en el linker local del IDE Keil uVision de cada proyecto, la integración de estos módulos en los ejecutables se realiza mediante el patrón **Unity Build** (incluyendo el archivo fuente directamente).

**Ejemplo de importación en un `main.c` de cualquier sub-proyecto:**

```c
#include <LPC17xx.h>                // CMSIS Core
#include "..\libfiles\gpio.c"       // Driver GPIO
#include "..\libfiles\delay.c"      // Driver de Tiempos
