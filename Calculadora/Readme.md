# 🧮 Calculadora LLM (HMI con Teclado Matricial y LCD)

Este proyecto es una simulación interactiva de una calculadora básica desarrollada *bare-metal* para el microcontrolador NXP LPC1768. Implementa una Interfaz Humano-Máquina (HMI) completa, gestionando la entrada de datos a través de un teclado matricial 4x4 y la salida visual mediante una pantalla LCD 16x2.

Con un toque humorístico, la calculadora simula el retraso de procesamiento de un "LLM" (Large Language Model) antes de entregar el resultado.

## ⚙️ Funcionalidades Clave

* **Operaciones Básicas:** Soporte para suma (`+`), resta (`-`), multiplicación (`x`) y división (`/`).
* **Soporte de Signos:** Uso de tipos de datos `int32_t` para permitir y mostrar resultados negativos de forma nativa.
* **Control de Excepciones:** Prevención de cuelgues del procesador por división entre cero, mostrando un mensaje de `" Error"`.
* **Máquina de Estados Finita (FSM):** Lógica implementada con la variable `estado` para transicionar secuencialmente entre la captura del `Operando 1`, `Operador` y `Operando 2`.

## 🔌 Pinout y Conexiones (Setup Universal)

El proyecto requiere el cableado tanto de la pantalla LCD como del teclado matricial 4x4, utilizando técnicas de multiplexación (barrido de filas/columnas) para leer 16 botones con solo 8 pines.

| Componente Físico | Pin Físico | Pin LPC1768 | Función Lógica |
| :--- | :--- | :--- | :--- |
| **Teclado - Fila 0** | PIN 13 | `P0.15` | Salida de barrido (Fila 1) |
| **Teclado - Fila 1** | PIN 14 | `P0.16` | Salida de barrido (Fila 2) |
| **Teclado - Fila 2** | PIN 15 | `P0.23` | Salida de barrido (Fila 3) |
| **Teclado - Fila 3** | PIN 16 | `P0.24` | Salida de barrido (Fila 4) |
| **Teclado - Col 0** | PIN 9 | `P0.0` | Entrada digital (Columna 1) |
| **Teclado - Col 1** | PIN 10 | `P0.1` | Entrada digital (Columna 2) |
| **Teclado - Col 2** | PIN 11 | `P0.18` | Entrada digital (Columna 3) |
| **Teclado - Col 3** | PIN 12 | `P0.17` | Entrada digital (Columna 4) |
| **LCD (Control/Data)** | PINES 21-30 | *Varios* | (Ver Setup Universal en el código fuente) |

## 🧠 Arquitectura del Software

1. **Lectura Multiplexada:** La función `KEYPAD_GetKey()` (ubicada en `libfiles/keypad.c`) se encarga de aplicar un nivel lógico bajo (`0`) secuencialmente a cada fila y leer el estado de las columnas para determinar, mediante una matriz de mapeo interno, qué tecla ha sido presionada.
2. **Concatenación Matemática:** Dado que el teclado devuelve caracteres individuales (ej. `'5'`, `'3'`), el firmware convierte el valor ASCII a un dígito decimal `(key - '0')` y lo concatena matemáticamente a la variable del operando actual mediante la fórmula: `(numero_actual * 10) + nuevo_digito`.
3. **Bloqueo y Reinicio:** Tras presionar `=` (mapeado al símbolo `#`), el sistema calcula el resultado, entra en una rutina bloqueante de "simulación LLM" y espera a que el usuario presione cualquier tecla de nuevo para resetear por completo las variables internas.

## 📦 Dependencias

El ejecutable requiere la compilación conjunta de la capa de abstracción de hardware (HAL) centralizada en la carpeta `\libfiles`:
* `keypad.c` - Driver de barrido matricial de teclado.
* `lcd.c` - Driver del controlador HD44780 (LCD).
* `delay.c` - Bloqueos de retardo para UX (Experiencia de Usuario).
* `gpio.c` - Configuración estándar de puertos de E/S.
