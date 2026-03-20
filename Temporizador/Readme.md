# ⏱️ Cronómetro Binario con TIMER0 (Interrupciones)

Implementación de un cronómetro de 4 bits (de 0 a 15 segundos) en C a bajo nivel. El avance del tiempo se gestiona mediante interrupciones precisas por hardware utilizando el periférico `TIMER0`, mientras que la representación visual se realiza mapeando los bits del contador a un banco de 4 LEDs. 

## ⚙️ Conceptos Técnicos Destacados

* **Timer por Hardware (TIMER0):** Configuración de registros de coincidencia (Match Registers) para generar eventos exactos sin depender de bucles de retardo por software.
* **Interrupciones (ISR Callbacks):** Desacoplamiento del flujo principal mediante "hooks", ejecutando la función `actualizarReloj()` de forma asíncrona cada 1.000.000 de microsegundos (1 segundo).
* **Enmascaramiento de Bits (Bit Masking):** Extracción lógica del valor de bits individuales de una variable (`segundos & 0x01`, `0x02`, etc.) para controlar los estados del GPIO de manera eficiente.
* **Máquina de Estados Simple (Pausa/Play):** Detención y reanudación del Timer a través de eventos físicos (Sondeo de botón E4).

## 🔌 Conexiones de Hardware

| Componente Físico | Pin Físico | Pin LPC1768 | Función Lógica |
| :--- | :--- | :--- | :--- |
| **Pulsador (E4)** | Entrada | `P1.30` | Entrada digital (Pausa / Reanuda el Timer) |
| **LED 1 (LSB)** | Salida | `P1.18` | Representa el Bit 0 (Valor: 1 s) |
| **LED 2** | Salida | `P1.20` | Representa el Bit 1 (Valor: 2 s) |
| **LED 3** | Salida | `P1.21` | Representa el Bit 2 (Valor: 4 s) |
| **LED 4 (MSB)** | Salida | `P1.23` | Representa el Bit 3 (Valor: 8 s) |

## 🧠 Arquitectura y Lógica de Funcionamiento

El temporizador `TIMER0` se configura para disparar una interrupción interna cada segundo. Cada vez que esta interrupción ocurre, el procesador pausa su tarea actual, incrementa la variable global volátil `segundos`, actualiza la representación binaria en los 4 LEDs físicos y vuelve a su rutina. Al llegar a 15 (todos los LEDs encendidos), la variable se desborda lógicamente a 0.

El bucle principal (`while(1)`) se dedica en exclusiva a monitorizar el pin `P1.30` (Pulsador E4). Si el usuario lo presiona, el bucle invoca la función `TIMER_Stop()`, congelando el contador a nivel de hardware. El microcontrolador queda atrapado en un bucle `while` interno (actuando como anti-rebote y bloqueo simultáneo) hasta que el usuario suelta el botón, momento en el que se ejecuta `TIMER_Start()` reanudando la cuenta donde se quedó.

## 📦 Dependencias
* `timer.c` - Configuración de pre-escalares, registros de coincidencia y gestión del NVIC para interrupciones del Timer.
* `gpio.c` - Control de pines.
