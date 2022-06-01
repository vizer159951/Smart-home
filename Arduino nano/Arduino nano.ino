#define vibr A6
#define water A4
#define trig1 4
#define echo1 5
#define ledm 8
#define flame A7
#define red 3
#define green 6
#define blue 7
#define door 9
#define pir 2
#define ir A2 //оглавление пинов для простоты

#include <SoftwareSerial.h>
#include "SR04.h"
#include <Servo.h>
#include <IRremote.h> //подключение библиотек

Servo myservo; // создание серво двигателя

IRrecv irrecv(ir);// создание ir remote

decode_results results; // создание переменной для результатов
// вычислений от ir remote

SoftwareSerial mySerial(12, 13); // создание порта для передачи
// данных на esp01s

struct Ser {
  long sf;
  long sv;
  long sp;
  long sw;
  long sd;
  long ss;
}; //структура хранения данных для передачи на esp01s

SR04 sr04 = SR04(echo1, trig1); // создание ультразвукового датчика

int buzzersyr = 11;
int buzzer = 11;
unsigned long timtx;
unsigned long tim;
bool l = false;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int irwater = 0;
int irservo = 0;
int irflame = 0;
int irvibr = 0;
int irpir = 0;
int irdoor = 0;
int irsr = 1;
int water1;
int servo1;
int flame1;
int vibr1;
int pir1;
int door1;
int buzzer1;
int sr1;
int led1; // создание нужных переменных

void setup() {
  irrecv.enableIRIn();
  
  mySerial.begin(9600);
  Serial.begin(9600); // запускаем порты на 9600

  pinMode(vibr, INPUT);
  pinMode(water, INPUT);
  pinMode(flame, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // обявление выходов и входов
  
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH); // выключение RGB

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
  digitalWrite(buzzer, LOW);// проверка светодиодов, пищалки и servo

  water1 = 0;
  pir1 = 0;
  flame1 = 0;
  door1 = 0;
  vibr1 = 0;
  servo1 = 0;
  buzzer1 = 1;
  sr1 = 1;
  led1 = 0; //выключение всех датчиков
  
  timtx = millis(); // запуск времени для отправки данных по порту
}
