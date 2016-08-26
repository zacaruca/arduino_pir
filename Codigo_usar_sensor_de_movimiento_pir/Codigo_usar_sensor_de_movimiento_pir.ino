#include <Time.h>
#include <TimeAlarms.h>

const byte RELE1Pin = 3;        // pin para el LED
const byte RELE2Pin = 4;        // pin para el LED
const byte RELE3Pin = 5;        // pin para el LED
const byte RELE4Pin = 6;        // pin para el LED
const byte PIRPin = 2;         // pin de entrada (for PIR sensor)

int pirState = LOW;           // de inicio no hay movimiento
int val = 0;                  // estado del pin


int id_timer_pir = 0; // id del timer para activarlo o desactivarlo
int id_timer_estado_pir = 0; // id para ver el estado del pir

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 5 * 1000;           // interval at which to blink (milliseconds)



void setup()
{
  pinMode(RELE1Pin, OUTPUT);
  pinMode(RELE2Pin, OUTPUT);
  pinMode(RELE3Pin, OUTPUT);
  pinMode(RELE4Pin, OUTPUT);
  pinMode(PIRPin, INPUT);
  Serial.begin(9600);
  //setTime(8, 29, 0, 1, 1, 11); // set time to Saturday 8:29:00am Jan 1 2011
  //creamos los timer y los deshablitmaos
  //id_timer_pir = Alarm.timerRepeat(10 * 60, Repeats);          // timer for every 10 minutos
  id_timer_estado_pir = Alarm.timerRepeat(6, Repeats1);            // timer for every 6 segundos
  //Alarm.disable(id_timer_pir);
  //Alarm.disable(id_timer_estado_pir);
  Serial.print("Creado Timer  del pir con id");
  Serial.println(id_timer_pir);
  Serial.print("Creado Timer  del estado del pir con id");
  Serial.println(id_timer_estado_pir);
}

void loop()
{
  val = digitalRead(PIRPin);

  if (val == HIGH)   //si está activado
  {
    if (pirState == LOW)  //si previamente estaba apagado
    {
      salidas_reles(LOW);
      Serial.println("Sensor activado");
      Serial.println("Activando Timer");
      //Alarm.enable(id_timer_pir);// timer for every 10 minutos
      //Alarm.enable(id_timer_estado_pir); // timer for every 6 segundos
      Serial.print("Activado Timer  del pir con id");
      Serial.println(id_timer_pir);
      Serial.print("Activado Timer  del estado del pir con id");
      Serial.println(id_timer_estado_pir);
      pirState = HIGH;
    }
  }
  else   //si esta desactivado
  {


    if (pirState == HIGH)  //si previamente estaba encendido
    {
      salidas_reles(HIGH);
      Serial.println("Sensor parado");
      // Alarm.disable(id_timer_pir);
      //Alarm.disable(id_timer_estado_pir);
      pirState = LOW;
    }
  }
}
void salidas_reles(int estado)
{
  digitalWrite(RELE1Pin, estado);  //LED ON
  digitalWrite(RELE2Pin, estado);  //LED ON
  digitalWrite(RELE3Pin, estado);  //LED ON
  digitalWrite(RELE4Pin, estado);  //LED ON
}
void Repeats1() {
  Serial.println("5 second timer");
  val = digitalRead(PIRPin);
  Serial.print("Valor del PIR ")    ;
  Serial.println(val)    ;
}
