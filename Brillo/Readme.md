# 💡 Control de Brillo LED mediante PWM por Hardware

Este proyecto implementa un control de atenuación (fading) para un LED utilizando el periférico **PWM (Pulse Width Modulation)** del microcontrolador NXP LPC1768. El sistema varía suavemente la intensidad luminosa desde el 100% hasta el 0% de forma cíclica, mostrando el porcentaje exacto de brillo en tiempo real a través de una pantalla LCD.

## ⚙️ Características Técnicas

* **Generación de Señal:** Modulación por ancho de pulso (PWM) generada por hardware (Canal 1), sin bloquear la CPU.
* **Resolución del Duty Cycle:** Configurado en 8 bits (valores de 0 a 255).
* **Interfaz Visual:** Pantalla LCD 16x2 actualizada dinámicamente.
* **Ciclo de Animación:** Fases de encendido y apagado gradual con retardos de 15 ms por paso.

## 🔌 Conexiones de Hardware (Setup Universal)

El proyecto utiliza la siguiente asignación de pines estandarizada:

| Componente Físico | Pin Físico | Pin LPC1768 | Función Lógica |
| :--- | :--- | :--- | :--- |
| **LED Dimmable** | PIN 26 | `P2.0` | Salida PWM (Canal 1) |
| **LCD - RS** | PIN 23 | `P2.3` | Selección de Registro |
| **LCD - RW** | PIN 22 | `P2.4` | Lectura/Escritura |
| **LCD - EN** | PIN 21 | `P2.5` | Enable |
| **LCD - D7** | PIN 24 | `P2.2` | Bus de Datos (Bit 7) |
| **LCD - D6** | PIN 25 | `P2.1` | Bus de Datos (Bit 6) |
| **LCD - D5** | PIN 30 | `P0.4` | Bus de Datos (Bit 5) |
| **LCD - D4** | PIN 29 | `P0.5` | Bus de Datos (Bit 4) |

## 🧠 Lógica de Control y Escalado

El control del brillo se divide en dos fases principales dentro de un bucle infinito: atenuación (de 255 a 0) y encendido (de 0 a 255). 

El hardware del periférico PWM recibe un valor de *Duty Cycle* absoluto entre `0` y `255`. Sin embargo, para mejorar la experiencia de usuario (UX) en la interfaz LCD, este valor crudo se escala matemáticamente a un porcentaje de `0` a `100` utilizando la siguiente fórmula:

$$Porcentaje = \frac{Valor_{PWM} \times 100}{255}$$

Esto permite que el periférico trabaje con su resolución nativa mientras el usuario lee información humanamente comprensible.

## 📦 Dependencias del Sistema

Este ejecutable requiere la compilación conjunta de las siguientes librerías de la HAL personalizada (`\libfiles`):
* `pwm.c` - Configuración de contadores, match registers y habilitación del canal PWM.
* `lcd.c` - Inicialización y escritura formateada en el display alfanumérico.
* `delay.c` - Temporización bloqueante para controlar la velocidad de la animación luminosa.
* `gpio.c` - Mapeo de puertos para la pantalla LCD.
