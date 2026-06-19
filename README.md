# Hexapodo

=========================================
PROYECTO HEXÁPODO CONTROLADO POR BLUETOOTH
=========================================

1. ¿QUÉ HACE EL PROYECTO?

Este proyecto consiste en un robot hexápodo (robot de seis patas) controlado de forma inalámbrica mediante Bluetooth. El robot recibe comandos desde un dispositivo externo y puede realizar dos acciones principales:

- Avanzar (comando W).
- Detenerse y regresar a una posición estable (comando S).

El movimiento se realiza mediante una secuencia de marcha que coordina los servomotores de las patas utilizando un controlador PCA9685.

------------------------------------------------

2. LENGUAJE DEL CÓDIGO

El proyecto está programado en lenguaje C++ utilizando el entorno de desarrollo Arduino IDE.

Archivos principales:

- etsapodo.ino
- HexapodoGait.cpp
- HexapodoGait.h

------------------------------------------------

3. REQUISITOS NECESARIOS

Hardware:

- Arduino UNO, Nano o compatible.
- Controlador PWM PCA9685.
- Módulo Bluetooth HC-05 o HC-06.
- 12 servomotores MG996R.
- Fuente de alimentación adecuada para los servomotores.
- Cables de conexión.

Software:

- Arduino IDE.
- Librería Adafruit PWM Servo Driver.
- Librería Wire.h.
- Librería SoftwareSerial.h.

------------------------------------------------

4. DIAGRAMA DE CONEXIÓN DEL HARDWARE

El diagrama de conexión puede encontrarse en la documentación del proyecto o en los archivos anexos entregados junto con el código.

Conexiones principales:

PCA9685:
- SDA → SDA de Arduino.
- SCL → SCL de Arduino.
- VCC → 5V.
- GND → GND.

Bluetooth HC-05:
- TX → Pin 11 de Arduino.
- RX → Pin 10 de Arduino.
- VCC → 5V.
- GND → GND.

Los servomotores se conectan a los canales correspondientes del PCA9685.

------------------------------------------------

5. IMPLEMENTACIÓN DEL CÓDIGO

Paso 1:
Instalar Arduino IDE.

Paso 2:
Instalar la librería:

- Adafruit PWM Servo Driver Library

Desde:
Programa → Incluir Librería → Administrar Bibliotecas.

Paso 3:
Abrir el archivo:

etsapodo.ino

Paso 4:
Conectar el Arduino a la computadora mediante USB.

Paso 5:
Seleccionar la placa y el puerto correspondiente en Arduino IDE.

Paso 6:
Compilar y cargar el programa.

Paso 7:
Emparejar el módulo Bluetooth HC-05 con el dispositivo móvil.

Paso 8:
Enviar los siguientes comandos por Bluetooth:

- W = Avanzar.
- S = Detener.

------------------------------------------------

6. FUNCIONAMIENTO GENERAL

1. El Arduino inicializa el PCA9685.
2. El robot adopta una posición de reposo.
3. El módulo Bluetooth espera comandos.
4. Al recibir "W", el robot inicia la marcha.
5. Al recibir "S", el robot se detiene y vuelve a la posición inicial.
6. El movimiento se genera mediante las funciones moverA() y moverB().
