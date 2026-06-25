 Hexápodo


PROYECTO HEXÁPODO CONTROLADO POR BLUETOOTH


 1. ¿Qué hace el proyecto?
Este proyecto es un robot hexápodo (de seis patas) que se controla de manera inalámbrica con Bluetooth.  
El robot recibe comandos desde el celular y puede hacer dos cosas principales:

- Avanzar (comando W).  
- Detenerse y regresar a una posición estable (comando S).  

El movimiento se logra coordinando los servomotores de las patas con el módulo PCA9685.



2. Lenguaje del código
El proyecto está hecho en **C++** usando el **Arduino IDE**.  

Archivos principales:
- hexapodo.ino
- HexapodoGait.cpp  
- HexapodoGait.h
- 

 3. Requisitos necesarios
Hardware:
- Arduino UNO, Nano o compatible.  
- Controlador PWM PCA9685.  
- Módulo Bluetooth HC-05 o HC-06.  
- 12 servomotores MG996R.  
- Fuente de alimentación para los servos.  
- Cables de conexión.  

Software:
- Arduino IDE.  
- Librería Adafruit PWM Servo Driver.  
- Librería Wire.h.  
- Librería SoftwareSerial.h.  



4. Diagrama de conexión del hardware
Conexiones principales:

PCA9685:
- SDA → SDA de Arduino  
- SCL → SCL de Arduino  
- VCC → 5V  
- GND → GND  

Bluetooth HC-05:
- TX → Pin 11 de Arduino  
- RX → Pin 10 de Arduino  
- VCC → 5V  
- GND → GND  

Los servos se conectan a los canales del PCA9685 según la pata que controlan.



5. Implementación del código
1. Instalar Arduino IDE.  
2. Instalar la librería Adafruit PWM Servo Driver desde:   
3. Abrir el archivo hexapodo.ino.  
4. Conectar el Arduino por USB.  
5. Seleccionar la placa y el puerto en Arduino IDE.  
6. Compilar y subir el programa.  
7. Emparejar el módulo Bluetooth con el celular.  
8. Enviar comandos:  
   - W = Avanzar  
     -S = Detenerse  



6. Funcionamiento general
1. El Arduino inicializa el PCA9685.  
2. El robot se coloca en posición de reposo.  
3. El módulo Bluetooth espera comandos.  
4. Al recibir **W**, el robot empieza a caminar.  
5. Al recibir **S**, el robot se detiene y vuelve a la posición inicial.  
6. El movimiento se logra con las funciones moverA() y moverB().  


7- Código

#include <Wire.h>                     // Librería para comunicación I2C
#include <Adafruit_PWMServoDriver.h>  // Librería para controlar el PCA9685
#include <SoftwareSerial.h>           // Librería para comunicación serial con Bluetooth

// -------------------- Clase que controla los servos --------------------
class ServoController {
  Adafruit_PWMServoDriver pwm;  // Objeto para manejar el PCA9685
  int SERVOMIN, SERVOMAX;       // Límites de pulso para los servos

public:
  // Constructor: recibe dirección I2C y valores de pulso mínimo y máximo
  ServoController(int address, int minPulse, int maxPulse)
    : pwm(address), SERVOMIN(minPulse), SERVOMAX(maxPulse) {}

  // Inicializa el PCA9685
  void iniciar() {
    pwm.begin();          // Inicia comunicación I2C
    pwm.setPWMFreq(60);   // Frecuencia típica para servos (60 Hz)
  }

  // Función para mover un servo a cierto ángulo
  void mover(int canal, int angulo) {
    int pulso = map(angulo, 0, 180, SERVOMIN, SERVOMAX); // Convierte ángulo a pulso
    pwm.setPWM(canal, 0, pulso);                         // Envía señal al servo
  }
};

// -------------------- Clase para cada pata --------------------
class Pata {
  int servoHorizontal;        // Servo que mueve la pata hacia adelante/atrás
  int servoVertical;          // Servo que levanta o baja la pata
  ServoController* servoCtrl; // Controlador que maneja los servos

public:
  // Constructor: recibe los canales de los servos y el controlador
  Pata(int h, int v, ServoController* sc)
    : servoHorizontal(h), servoVertical(v), servoCtrl(sc) {}

  // Levanta o baja la pata
  void levantar(int angulo) { servoCtrl->mover(servoVertical, angulo); }

  // Mueve la pata hacia adelante o atrás
  void moverHorizontal(int angulo) { servoCtrl->mover(servoHorizontal, angulo); }
};

// -------------------- Clase del robot hexápodo --------------------
class Hexapodo {
  Pata* patas[6];             // Arreglo con las 6 patas
  ServoController* servoCtrl; // Controlador de servos

public:
  Hexapodo(ServoController* sc) : servoCtrl(sc) {}

  // Asigna una pata al robot
  void asignarPata(int index, Pata* pata) { patas[index] = pata; }

  // Coloca al robot en posición de reposo
  void pararse() {
    patas[0]->levantar(145); patas[0]->moverHorizontal(110);
    patas[1]->levantar(145); patas[1]->moverHorizontal(100);
    patas[2]->levantar(140); patas[2]->moverHorizontal(120);
    patas[3]->levantar(145); patas[3]->moverHorizontal(75);
    patas[4]->levantar(145); patas[4]->moverHorizontal(100);
    patas[5]->levantar(145); patas[5]->moverHorizontal(75);
    delay(500); // Pausa para que los servos lleguen a la posición
  }

  // Movimiento del grupo A de patas
  void moverA() {
    patas[0]->levantar(145); patas[0]->moverHorizontal(80);
    patas[1]->levantar(165); patas[1]->moverHorizontal(150);
    patas[2]->levantar(135); patas[2]->moverHorizontal(100);
    delay(500);
  }

  // Movimiento del grupo B de patas
  void moverB() {
    patas[3]->levantar(175); patas[3]->moverHorizontal(105);
    patas[4]->levantar(135); patas[4]->moverHorizontal(50);
    patas[5]->levantar(175); patas[5]->moverHorizontal(40);
    delay(500);
  }
};

// -------------------- Configuración de Bluetooth --------------------
SoftwareSerial bluetooth(11, 10); // RX=10, TX=11
int cicloActivo = 0;              // Variable para saber si el robot está caminando

// -------------------- Objetos principales --------------------
ServoController servoCtrl(0x40, 125, 625); // Dirección I2C del PCA9685 y pulsos
Hexapodo robot(&servoCtrl);                // Robot hexápodo

// -------------------- Setup --------------------
void setup() {
  servoCtrl.iniciar();     // Inicializa el controlador PCA9685
  bluetooth.begin(9600);   // Inicializa comunicación Bluetooth

  // Asignación de patas (cada una con sus servos)
  robot.asignarPata(0, new Pata(5, 4, &servoCtrl));
  robot.asignarPata(1, new Pata(15, 14, &servoCtrl));
  robot.asignarPata(2, new Pata(8, 9, &servoCtrl));
  robot.asignarPata(3, new Pata(10, 11, &servoCtrl));
  robot.asignarPata(4, new Pata(7, 6, &servoCtrl));
  robot.asignarPata(5, new Pata(13, 12, &servoCtrl));

  robot.pararse(); // El robot inicia en posición estable
}

// -------------------- Loop principal --------------------
void loop() {
  // Revisa si hay datos recibidos por Bluetooth
  if (bluetooth.available() > 0) {
    char comando = bluetooth.read(); // Lee el comando
    if (comando == 'W' || comando == 'w') {
      cicloActivo = 1; // Activa caminata
    } else if (comando == 'S' || comando == 's') {
      cicloActivo = 0; // Detiene caminata
      robot.pararse(); // Regresa a posición estable
    }
  }

  // Si el ciclo está activo, alterna movimientos de patas
  if (cicloActivo == 1) {
    robot.moverA();
    delay(300);
    robot.moverB();
    delay(300);
  }
}
