# 📡 Comunicación Serial UART (Modo Chat Half-Duplex)

Este proyecto implementa una comunicación serie bidireccional por turnos (*Half-Duplex*) entre dos microcontroladores NXP LPC1768 independientes. El sistema utiliza el periférico hardware **UART2**, permitiendo que dos placas se intercambien caracteres ingresados mediante teclados matriciales y visualicen las respuestas en pantallas LCD.

## ⚙️ Características Técnicas y Protocolo

* **Periférico Hardware:** UART2.
* **Baudrate:** Configurado a `19200 bps`.
* **Sincronización:** Flujo de ejecución bloqueante basado en turnos (El programa espera en `UART_RxChar()` hasta que el buffer de recepción recibe un dato válido).
* **Topología:** Conexión directa Punto a Punto (P2P).

## 🔌 Pinout y Conexiones Físicas

Para que la comunicación funcione, es imperativo realizar conexiones cruzadas entre los pines TX/RX de ambas placas y compartir una referencia común de tierra.

### Conexiones de Comunicaciones (Placa a Placa)
| Placa A (LPC1768) | Cableado Físico | Placa B (LPC1768) |
| :---: | :---: | :---: |
| `P0.10` (TXD2) - PIN 28 | ➡️ Transmite a ➡️ | `P0.11` (RXD2) - PIN 27 |
| `P0.11` (RXD2) - PIN 27 | ⬅️ Recibe de ⬅️ | `P0.10` (TXD2) - PIN 28 |
| **`GND`** | ➖ Masa Común ➖ | **`GND`** |

> **⚠️ Crítico:** Si no se conecta el pin GND entre ambas placas, los niveles lógicos de voltaje "flotarán", causando que la comunicación UART reciba basura (ruido) o no funcione en absoluto.

### Conexiones de HMI (Setup Universal)
*(Aplica idénticamente para Placa A y Placa B)*
* **Teclado:** F0-F3 (`P0.15`, `P0.16`, `P0.23`, `P0.24`) y C0-C3 (`P0.0`, `P0.1`, `P0.18`, `P0.17`).
* **LCD 16x2:** RS (`P2.3`), RW (`P2.4`), EN (`P2.5`) y Bus de Datos D4-D7 (`P0.5`, `P0.4`, `P2.1`, `P2.2`).

## 🧠 Arquitectura de la Comunicación

El flujo del firmware (`Placa A`) sigue un ciclo cerrado (Loop):
1. **Petición Local:** Se solicita al usuario ingresar un carácter vía el teclado matricial (`KEYPAD_GetKey()`).
2. **Transmisión (TX):** El carácter pulsado se empuja al registro de transmisión de la UART2 (`UART_TxChar()`), saliendo por el pin físico `TXD2`.
3. **Bloqueo (RX):** El microcontrolador muestra `"Esperando Rx..."` en el LCD y detiene su ejecución principal leyendo constantemente el registro de estado de línea (LSR) de la UART2.
4. **Recepción:** Cuando el bit de "Dato Listo" (RDR) en el LSR se pone a 1 (indicando que la Placa B ha enviado un byte), el sistema lee el registro `RBR`, lo guarda en `dato_recibido` y lo imprime en el LCD local.

*Nota: Para probar este código, la Placa B debe estar ejecutando un código simétrico (espejo), donde primero escucha (RX) y luego transmite (TX).*

## 📦 Dependencias (HAL)

Uso intensivo de la librería propietaria ubicada en `\libfiles`:
* `uart.c` - Configuración de divisores fraccionales de reloj (Baudrate), pines y FIFOs.
* `keypad.c` - Captura de la intención del usuario.
* `lcd.c` - Interfaz visual de depuración y estado.
