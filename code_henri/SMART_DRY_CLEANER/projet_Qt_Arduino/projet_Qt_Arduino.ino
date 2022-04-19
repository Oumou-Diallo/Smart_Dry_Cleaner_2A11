#include <HCSR04.h>
/* Inclut la lib Servo pour manipuler le servomoteur */
#include <Servo.h>
/* Créer un objet Servo pour contrôler le servomoteur */
Servo monServomoteur;
const int servoPin=9;
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
UltraSonicDistanceSensor distanceSensor2(trig2Pin, echo2Pin);

//#define pas 9
char data;
//int x;

void setup() {
  // put your setup code here, to run once:
  monServomoteur.attach(servoPin);
  pinMode(LEDrouge,OUTPUT); //règle la borne numérique numéro 7 de la carte Arduino en mode sortie
  pinMode(LEDvert,OUTPUT); //règle la borne numérique numéro 8 de la carte Arduino en mode sortie
  /*digitalWrite(LEDrouge,HIGH); // La LED s'allume en rouge
  digitalWrite(LEDvert,LOW);*/
  
  /*pinMode(LEDrouge,OUTPUT); 
  pinMode(LEDvert,OUTPUT);*/
  
  /*pinMode(pin_led2,OUTPUT);
  digitalWrite(pin_led2,LOW);
  pinMode(pin_led1,OUTPUT);
  analogWrite(pin_led1,0);
  Serial.begin(9600);
  x=0;*/
}

void loop() {
  // put your main code here, to run repeatedly:
 //monServomoteur.write(90);
 //digitalWrite(LEDrouge,HIGH);
  if(Serial.available())
  {
    data=Serial.read();
      if(((((distanceSensor1.measureDistanceCm()+1)<6)&&(distanceSensor1.measureDistanceCm()+1)>0))&&(state==false)||((distanceSensor2.measureDistanceCm()+1<6)&&(distanceSensor2.measureDistanceCm()+1)>0))
      {
        Serial.write('1');
        digitalWrite(LEDrouge,LOW);
        digitalWrite(LEDvert,HIGH); // La LED s'allume en vert
        state=true;
      }
      else if((((distanceSensor1.measureDistanceCm()+1)<6)&&(distanceSensor1.measureDistanceCm()+1)>0)&&(state==true))
      {
        Serial.write('0');
        digitalWrite(LEDrouge,HIGH); // La LED s'allume en rouge
        digitalWrite(LEDvert,LOW);
        state=false;
      }
    else if(data=='1')
    {
      digitalWrite(LEDrouge,HIGH);
      monServomoteur.write(90); // la barrière s'ouvre
    }
    else if(data=='0')
    {
      monServomoteur.write(180); // la barrière se ferme
    }
   /* else if(data=='2')
    {
      if(x+pas<255)
      {
        x=x+pas;
        analogWrite(pin_led1,x);
        Serial.write(x);
      }
      else if(data=='3')
      {
        if(x>pas)
        x=x+pas;
        else
        x=0;
        analogWrite(pin_led1,x);
      }
    }*/
  }
}
