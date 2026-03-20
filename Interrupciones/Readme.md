# 🚨 Control de Temporizador (RIT) mediante Interrupciones Externas

Este proyecto implementa un sistema reactivo *bare-metal* para el microcontrolador NXP LPC1768. Utiliza el **Temporizador de Interrupción Repetitiva (RIT)** para controlar el parpadeo de un LED, y una **Interrupción Externa por GPIO (EINT3)** para modificar dinámicamente la frecuencia de dicho parpadeo mediante un pulsador físico.

## ⚙️ Conceptos Técnicos Destacados

* **Manipulación Directa de Registros:** Configuración a bajo nivel del periférico RIT (`RICTRL`, `RICOMPVAL`, `RICOUNTER`) y del controlador de interrupciones de puertos (`LPC_GPIOINT`).
* **NVIC (Nested Vectored Interrupt Controller):** Habilitación y gestión de vectores de interrupción hardware (`RIT_IRQn` y `EINT3_IRQn`).
* **Rutinas de Servicio de Interrupción (ISR):** Separación de la lógica de temporización (`RIT_IRQHandler`) y la lógica de eventos de usuario (`EINT3_IRQHandler`).
* **Variables Volátiles:** Uso seguro de memoria entre las ISR y el bucle principal (`volatile uint8_t`).
* **Anti-rebote por Software (Debouncing):** Filtrado de ruido electromecánico del pulsador directamente en el flag de limpieza de la interrupción.

## 🔌 Conexiones de Hardware

| Componente Físico | Pin Físico | Pin LPC1768 | Función Lógica |
| :--- | :--- | :--- | :--- |
| **Pulsador (E7)** | PIN 8 | `P0.6` | Entrada (Dispara interrupción por flanco de bajada) |
| **LED1** | Integrado | `P1.18` | Salida digital (Toggle controlado por RIT) |
| **LCD (Control/Data)**| PINES 21-30 | *Varios* | Visualización de la velocidad actual |

## 🧠 Arquitectura del Software

La arquitectura de este proyecto es orientada a eventos, liberando al procesador de bloqueos continuos (`polling`):

1. **Bucle Principal (`while(1)`):** Permanece prácticamente inactivo. Solo actualiza la pantalla LCD si la bandera `actualizar_pantalla` ha sido levantada por una interrupción, minimizando el tráfico en el bus de datos de la pantalla.
2. **ISR del Temporizador (RIT):** Se dispara automáticamente cada vez que el contador alcanza el valor del registro de comparación (`RICOMPVAL`). Su única tarea es conmutar (Toggle) el estado del LED y limpiar su propia bandera de interrupción.
3. **ISR del Pulsador (EINT3):** Al detectar un flanco de bajada en el pin `P0.6`, esta rutina:
   * Incrementa cíclicamente el nivel de velocidad (1 a 4).
   * Sobrescribe el registro de comparación del RIT (`RICOMPVAL`) alterando la frecuencia al instante.
   * Resetea el contador del RIT para evitar un estado de *overflow* o desincronización.
   * Aplica un retardo de 50ms antes de limpiar el flag de interrupción (`IO0IntClr`) para ignorar los rebotes mecánicos del botón.

## 📦 Dependencias

Requiere la compilación conjunta de la capa de abstracción de hardware (HAL) centralizada en la carpeta `\libfiles`:
* `gpio.c` - Inicialización de pines y operaciones de Toggle.
* `lcd.c` - Interfaz visual de depuración.
* `delay.c` - Retardos bloqueantes utilizados para el debouncing.
