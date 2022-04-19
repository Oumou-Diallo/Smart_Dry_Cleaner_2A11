#include <HCSR04.h>
/* Inclut la lib Servo pour manipuler le servomoteur */
#include <Servo.h>
#include <SoftwareSerial.h>
/* Créer un objet Servo pour contrôler le servomoteur */
Servo monServomoteur;
const int servoPin=2;
const int trig1Pin = 3;
const int echo1Pin = 4;
const int trig2Pin = 5;
const int echo2Pin = 6;
const int LEDrouge=7;
const int LEDvert=8;
int position = 180;
bool state=false;

// initialisation du 1er capteur avec les broches utilisees.
UltraSonicDistanceSensor distanceSensor1(trig1Pin, echo1Pin);
// initialisation du 2eme capteur avec les broches utilisees.
UltraSonicDistanceSensor distanceSensor2(trig2Pin, echo2Pin);

char data;

void setup(){
  Serial.begin(9600);
monServomoteur.attach(servoPin);
pinMode(LEDrouge,OUTPUT); //règle la borne numérique numéro 7 de la carte Arduino en mode sortie
pinMode(LEDvert,OUTPUT); //règle la borne numérique numéro 8 de la carte Arduino en mode sortie
}

void loop(){
  /*if(Serial.available())
  { */
    data=Serial.read();
    if(((((distanceSensor1.measureDistanceCm()+1)<6)&&(distanceSensor1.measureDistanceCm()+1)>0))||((distanceSensor2.measureDistanceCm()+1<6)&&(distanceSensor2.measureDistanceCm()+1)>0)) 
    {// Si l'un des deux capteurs HC-SR04 détecte un véhicule
        Serial.write('1');
        //monServomoteur.write(90); // la barrière s'ouvre
        digitalWrite(LEDrouge,HIGH);
        digitalWrite(LEDvert,LOW); // La LED s'allume en vert
        state=true;
        //delay(5000);
    }
    else if(((((distanceSensor1.measureDistanceCm()+1)<6)&&(distanceSensor1.measureDistanceCm()+1)>0))||((distanceSensor2.measureDistanceCm()+1<6)&&(distanceSensor2.measureDistanceCm()+1)>0)) 
    {// Si l'un des deux capteurs HC-SR04 détecte un véhicule
        Serial.write('0');
        //monServomoteur.write(90); // la barrière s'ouvre
        digitalWrite(LEDrouge,HIGH);
        digitalWrite(LEDvert,LOW); // La LED s'allume en vert
        state=false;
        //delay(5000);
    }
    else if(data=='1')
    {
      digitalWrite(LEDvert,HIGH);
      digitalWrite(LEDrouge,LOW);
      monServomoteur.write(90); // la barrière s'ouvre
    }
    else if(data=='0')
    {
      digitalWrite(LEDvert,LOW);
      digitalWrite(LEDrouge,HIGH);
      monServomoteur.write(180); // la barrière se ferme
    }

/*}*/
}
