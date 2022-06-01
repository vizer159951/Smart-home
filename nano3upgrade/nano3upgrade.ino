#define vibr A6
#define water A4
#define trig1 4
#define echo1 5
#define ledm 8
#define flame A7
#define red 3
#define green 6
#define blue 7
int buzzersyr = 11;
int buzzer = 11;

#define door 9
#define pir 2
#define ir A2
#include <IRremote.h>
IRrecv irrecv(ir);
decode_results results;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(12, 13); // RX, TX
unsigned long timtx;
struct Ser{
  long sf;
  long sv;
  long sp;
  long sw;
  long sd;
  long ss;
};

#include <Servo.h>
Servo myservo;


unsigned long tim;
bool l;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
#include "SR04.h"

int irwater = 0;
int irservo = 0;
int irflame = 0;
int irvibr = 0;
int irpir = 0;
int irdoor = 0;
int irsr = 1;
SR04 sr04 = SR04(echo1, trig1);

int water1;
int servo1;
int flame1;
int vibr1;
int pir1;
int door1;
int buzzer1;
int sr1;
int led1;

void setup() {
  irrecv.enableIRIn();

  pinMode(vibr, INPUT);
  pinMode(water, INPUT);
  pinMode(flame, INPUT); // объявляем порт датчика как вход
  Serial.begin(9600); // запускаем монитор порта на 9600
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
  l = false;

  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  digitalWrite(red, LOW);
  delay(200);
  digitalWrite(red, HIGH);
  digitalWrite(blue, LOW);
  delay(200);
  digitalWrite(blue, HIGH);
  digitalWrite(green, LOW);
  delay(200);
  digitalWrite(green, HIGH);
  digitalWrite(ledm, HIGH);
  delay(200);
  digitalWrite(ledm, LOW);

  myservo.attach(A5);
  myservo.write(90);
  delay(500);
  myservo.write(0);

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);

  water1 = 0;
  pir1 = 0;
  flame1 = 0;
  door1 = 0;
  vibr1 = 0;
  servo1 = 0;
  buzzer1 = 1;
  sr1 = 1;
  led1 = 0;
  mySerial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    timtx = millis();

  //Serial.begin(9600);



}
  ////////////////////////////////////////////////////////////////////////////////////////////////
