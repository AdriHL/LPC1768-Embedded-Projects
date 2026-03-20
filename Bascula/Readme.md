\# ⚖️ Báscula Digital Simulada (0 - 250 Kg)



Este proyecto implementa el firmware \*bare-metal\* para simular una báscula industrial utilizando el microcontrolador \*\*NXP LPC1768\*\*. El sistema adquiere una señal analógica (simulando una celda de carga mediante un potenciómetro), escala el valor matemáticamente y muestra el peso resultante en tiempo real en una pantalla LCD.



\## ⚙️ Características Técnicas



\* \*\*Resolución ADC:\*\* 12 bits (valores crudos de 0 a 4095).

\* \*\*Rango de Medición Simulada:\*\* 0 Kg a 250 Kg.

\* \*\*Interfaz de Usuario (HMI):\*\* Pantalla LCD 16x2 (Modo 4 bits).

\* \*\*Tasa de Refresco:\*\* Actualización de pantalla cada 200 ms.



\## 🔌 Conexiones de Hardware (Setup Universal)



El proyecto está diseñado bajo un esquema de conexiones estandarizado para la placa de desarrollo:



| Componente Físico | Pin Físico | Pin LPC1768 | Función Lógica |

| :--- | :--- | :--- | :--- |

| \*\*Sensor (Potenciómetro)\*\* | PIN 18 | `P0.26` | Canal ADC 3 (Entrada Analógica) |

| \*\*LCD - RS\*\* | PIN 23 | `P2.3` | Selección de Registro |

| \*\*LCD - RW\*\* | PIN 22 | `P2.4` | Lectura/Escritura |

| \*\*LCD - EN\*\* | PIN 21 | `P2.5` | Enable |

| \*\*LCD - D7\*\* | PIN 24 | `P2.2` | Bus de Datos (Bit 7) |

| \*\*LCD - D6\*\* | PIN 25 | `P2.1` | Bus de Datos (Bit 6) |

| \*\*LCD - D5\*\* | PIN 30 | `P0.4` | Bus de Datos (Bit 5) |

| \*\*LCD - D4\*\* | PIN 29 | `P0.5` | Bus de Datos (Bit 4) |



\## 🧠 Lógica de Conversión (Escalado)



El convertidor analógico-digital (ADC) del LPC1768 tiene una resolución de 12 bits, lo que significa que traduce el voltaje de entrada (0 a 3.3V) a un valor digital entero entre `0` y `4095`.



Para convertir este valor crudo del sensor a un peso legible (de 0 a 250 Kg), el firmware aplica la siguiente regla de tres en tiempo real:



$$Peso = \\frac{Valor\_{ADC} \\times 250}{4095}$$



Este cálculo se realiza de forma continua en el bucle principal (`while(1)`), mostrando tanto el peso calculado en kilogramos como el valor crudo del sensor para facilitar la depuración de hardware.



\## 📦 Dependencias del Sistema



El código base importa los módulos directamente desde la capa de abstracción de hardware (HAL) personalizada ubicada en la carpeta raíz `\\libfiles`:

\* `adc.c` - Inicialización y lectura del conversor.

\* `lcd.c` - Controladores del display alfanumérico.

\* `delay.c` - Gestión de bloqueos de tiempo para el refresco de pantalla.

\* `gpio.c` - Configuración de pines.

