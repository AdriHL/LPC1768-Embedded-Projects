# 📡 Comunicación UART Bidireccional (Chat)



Breve descripción de 1-2 líneas. Ejemplo: \*Implementación bare-metal de comunicación serie bidireccional entre dos microcontroladores LPC1768 usando el periférico UART0 con interrupciones.\*



## ⚙️ Características Técnicas

\*\*Microcontrolador:\*\* NXP LPC1768 (ARM Cortex-M3)

\*\*Periféricos usados:\*\* UART0, NVIC (Interrupciones)

\*\*Baudrate:\*\* 115200 bps | 8 Data bits | 1 Stop bit | No Parity



## 🔌 Pinout y Conexiones Físicas



| Pin LPC1768 (Placa A) | Pin LPC1768 (Placa B) | Función |

| :--- | :--- | :--- |

| `P0.2` (TXD0) | `P0.3` (RXD0) | Transmisión -> Recepción |

| `P0.3` (RXD0) | `P0.2` (TXD0) | Recepción <- Transmisión |

| `GND` | `GND` | Masa común (¡Obligatorio!) |



## 🧠 Lógica Implementada

1\. \*\*Configuración de Relojes:\*\* Se ajusta el `PCLK` para el periférico UART.

2\. \*\*Cálculo de Baudrate:\*\* Se configuran los registros `DLL` y `DLM` mediante la fórmula: `PCLK / (16 \* Baudrate)`.

3\. \*\*Gestión de Interrupciones:\*\* La recepción de datos no es bloqueante. Se utiliza la interrupción `UART0\_IRQHandler` que salta automáticamente al registro `RBR` al recibir un byte, guardándolo en un buffer circular.



## 🚀 Cómo compilar

1\. Abre el archivo `NombreProyecto.uvprojx` con Keil uVision 5.

2\. Asegúrate de tener referenciada la carpeta de dependencias `../libfiles`.

3\. Presiona `F7` (Build) y `F8` (Download) con la placa conectada vía JTAG/SWD.

