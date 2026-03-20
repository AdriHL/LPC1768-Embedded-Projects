# 🚀 ARM Cortex-M3 (LPC1768) Bare-Metal Projects

Bienvenido a mi portfolio de sistemas embebidos. Aquí agrupo una colección de proyectos desarrollados en **C a bajo nivel (bare-metal)** para el microcontrolador **NXP LPC1768** (arquitectura ARM Cortex-M3).

Este repositorio demuestra mi capacidad para interactuar directamente con el hardware, gestionar interrupciones, configurar periféricos mediante registros lógicos y diseñar arquitecturas de software eficientes para sistemas con recursos limitados.

## 🛠️ Entorno de Desarrollo y Hardware

* **Microcontrolador:** NXP LPC1768 (ARM Cortex-M3 a 100MHz)
* **Lenguajes:** C y ARM Assembly (Startups/Core)
* **IDE:** Keil uVision 5
* **Arquitectura de Software:** Modular. Todos los proyectos comparten una librería común creada desde cero para abstraer el hardware (HAL propia).

## 📂 Índice de Proyectos

Haz clic en cualquier proyecto para ver su código fuente y detalles técnicos específicos:

| Proyecto | Descripción | Conceptos y Periféricos Clave |
| :--- | :--- | :--- |
| [⚖️ Báscula](./Bascula) | Sistema de pesaje digital interactivo. | ADC, Interrupciones, Pantalla LCD |
| [💡 Brillo](./Brillo) | Control de intensidad lumínica por hardware. | PWM, Timers, Duty Cycle |
| [🧮 Calculadora](./Calculadora) | Calculadora funcional con interfaz HMI. | Teclado Matricial, LCD, Lógica de estados |
| [📡 Comunicación UART](./Comunicacion_UART) | Chat bidireccional entre dos microcontroladores. | UART0, Baudrate, ISR (Rx/Tx No bloqueante) |
| [🚨 Interrupciones](./Interrupciones) | Gestión avanzada de eventos asíncronos. | EINT3, NVIC, Lógica Anti-rebotes (Debouncing) |
| [🚥 LED / Ejercicio 1](./LED) | Control de periféricos y retardos precisos. | GPIO, SysTick, Bit Masking |
| [🖥️ Pantalla & Teclado](./Pantalla_teclado) | Drivers de comunicación para periféricos externos. | I/O Mapping, Multiplexación |
| [⏱️ Temporizador](./Temporizador) | Reloj digital y ejecución basada en tiempo. | TIMER0/1, Match Registers, RIT |

## 🏗️ Arquitectura de la Librería (`/libfiles`)

Para evitar la duplicación de código y aplicar buenas prácticas de ingeniería de software (Principio DRY), he desarrollado una capa de abstracción de hardware (HAL) personalizada. 

En la carpeta [`libfiles`](./libfiles) se encuentran los drivers centralizados para:
* Interfaces: LCD, Teclado Matricial.
* Protocolos: UART, SPI, SoftI2C.
* Periféricos del Sistema: ADC, PWM, Timers, RTC, SysTick, GPIO.

## 🚀 Cómo compilar localmente

1. Clona este repositorio: `git clone https://github.com/AdriHL/LPC1768-Embedded-Projects.git`
2. Abre la subcarpeta del proyecto que desees explorar.
3. Ejecuta el archivo `.uvprojx` para abrir el entorno en Keil uVision 5.
4. Compila el proyecto (`F7`) y súbelo a la placa (`F8`). *Nota: Asegúrate de que las rutas relativas a la carpeta `libfiles` estén correctamente configuradas en las opciones de Includes (C/C++) de tu entorno local.*

---
*Desarrollado por [Adrián Hernández Lillo](https://github.com/AdriHL)* 👾
