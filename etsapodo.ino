#include <Wire.h> //para poder comunicarse con los servos (sda y scl)
#include <Adafruit_PWMServoDriver.h> //para la pca
#include <SoftwareSerial.h> //para el blutu
#include "HexapodoGait.h" // libreria propia

//variable del pwm, constructor, (0x40)es el nombre del pwm (pca9685)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Pines asignados para la variable del módulo inalámbrico: 11 (RX) y 10 (TX) se conectan inversamente
SoftwareSerial bluetooth(11, 10); 

// Variable que controla el movimiento
int cicloActivo = 0;  

void setup() {
  //despierta a la pca
  iniciarServos();
  //inicia la comunicacion blutu
  bluetooth.begin(9600); 
  //llama a la funcion para pararse y ya se queda a espera de algun comando 
  pararse();
}

void loop() {
  //verifica constantemente si llega algun mensaje por blutu
  if (bluetooth.available() > 0) {
    //espera la letra "w" o "s"
    char letraCruda = bluetooth.read();

    // USO DEL FACTORY METHOD. convierte la letra en un comando de enum
    // se crea una variable para guardar lo que "factory tranformo"
    // dependiendo si en el cpp es caminar o detener se asigna a comando un 1 o 0
    // cambia el valor de ciclo activo a 1 o 0  
    TipoComando comando = CommandFactory(letraCruda);

    //asigna valor de 1 para empezar a avanzar
    if (comando == COMANDO_CAMINAR) {
       cicloActivo = 1;
    }
    //asigna valor de 0 para detener el movimiento y regresa a la posicion inicial
    else if (comando == COMANDO_DETENER) {
       cicloActivo = 0;
       pararse();
    }
  }

  //segun si ciclo activo tiene valor de 1 comienza a llamar a las funciones de mover
  //para que empieze a moverse pero en cuanto detecta un 0 este se regresa al inicio del loop
  //esto gracias al return;
  if (cicloActivo == 1) {
    moverA();
    
    if (cicloActivo == 0) return; 
    
    moverB();
  }
} 