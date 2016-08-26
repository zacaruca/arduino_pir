/*
 * Programa para el cuartito de Papa
 * 
 * Tiempo de 10 minutos sin movimiento
 * se apaga todo, si se mueve se enciende de nuevo
 * 
 * Zacaruca Software 25/08/2016
 * 
 * Version 1 Estable
 */
#include <TimeLib.h>
#include <TimeAlarms.h>

// Declaracion de variables
const byte RELE1Pin = 3;        // pin para el LED
const byte RELE2Pin = 4;        // pin para el LED
const byte RELE3Pin = 5;        // pin para el LED
const byte RELE4Pin = 6;        // pin para el LED
const byte PIRPin = 2;          // pin de entrada (for PIR sensor)
bool Estado_PIR_var = false;

AlarmId id_timer_estado_pir;
AlarmId id_timer_luz;

void setup() {
  // tipo de pin output o input
  pinMode(RELE1Pin, OUTPUT);
  pinMode(RELE2Pin, OUTPUT);
  pinMode(RELE3Pin, OUTPUT);
  pinMode(RELE4Pin, OUTPUT);
  pinMode(PIRPin, INPUT);


  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
    
  // create timers, to trigger relative to when they're created
  id_timer_estado_pir = Alarm.timerRepeat(6, Estado_PIR_leer);           // timer for every 6 seconds
  id_timer_luz = Alarm.timerRepeat(10 * 60, Apaga_Luz);       // timer for every 10 minutos
  Alarm.disable(id_timer_estado_pir);
  Alarm.disable(id_timer_luz);
  //apagamos los reles
  salidas_reles(HIGH);
}


void loop() {
  if  (Estado_PIR() == 1 && Estado_PIR_var == false) {
    Serial.print("PIR activado y variable Estado_PIR_var = ");
    Serial.println(Estado_PIR_var);
    //activamos los reles
    Serial.println("Activamos reles");
    salidas_reles(LOW);
    //la ponemos a true para que entre en el aranque y solo entre cuando el timer de apagado la establezca a false
    Estado_PIR_var = true;
    Serial.println("Activamos alarmas");
    Alarm.enable(id_timer_estado_pir);
    Alarm.enable(id_timer_luz);
  }
  Alarm.delay(1000); // wait one second between clock display
}

void Estado_PIR_leer() {
  Serial.println("TIMER PIR --->  Leyendo estado del PIR");
  if (Estado_PIR() == 1) {

    Serial.println("PIR     M O T I O N");
    Estado_PIR_var = true;
    Alarm.disable(id_timer_luz);
    delay(250);
    Alarm.enable(id_timer_luz);
  } else  {
    Serial.println("PIR    N  O      MOTION");
  }

}

void Apaga_Luz() {
  Serial.println("TIMER APAGADO --->  Se apago todo");
  //apagamos los reles
  salidas_reles(HIGH);
  //marcamos pir en false para iniciar de nuevo
  Estado_PIR_var = false;
  //disable los timer para empezar de nuevo
  Alarm.disable(id_timer_estado_pir);
  Alarm.disable(id_timer_luz);
}
bool Estado_PIR() {
  if (digitalRead(PIRPin) == 1 ) {
    return true;
  } else {
    return false;
  }
}

void salidas_reles(int estado)
{
  digitalWrite(RELE1Pin, estado);  //LED ON
  digitalWrite(RELE2Pin, estado);  //LED ON
  digitalWrite(RELE3Pin, estado);  //LED ON
  digitalWrite(RELE4Pin, estado);  //LED ON
}
