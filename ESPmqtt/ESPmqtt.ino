#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include "DHTesp.h"
#include <Servo.h>
#include <MFRC522.h> // подключение библиотек

const char* ssid = "TP-Link_DC2D";
const char* password = "32384244";
const char* pass = "32384244"; //данные для подключения к интернету

const char* mqtt_server = "m4.wqtt.ru";
const int mqtt_port = 5140;
const char* mqtt_user = "u_50UPHV";
const char* mqtt_password = "DRvhTF7K";//данные для подключения к mqtt

WiFiClient espClient;
PubSubClient client(espClient); //создание клиентов

#define SS_PIN 15
#define RST_PIN 9
#define pir A0
#define svet 16
#define vent 0
#define kotel 4 //оглавление пинов

float temp111;
byte b0 = 183;
byte b1 = 87;
byte b2 = 131;
byte b3 = 181;
int a = 0;
int b = 0;
byte nuidPICC[4];
int umkot = 0;
int umkon = 0;
int pir1;
int rsvet;
int vsvet;
int isvet;
int arsvet;
int umsvet;
int aumsvet;
int apir = 1;
int rkot;
int vkot;
int arkot;
int ikot;
int aumkot;
int aumkon;
int arkon;
int rkon;
int vkon;
int ikon;
int serv;
int sermqtt;
int ser1;
int ser2;
int serd = 0;
int rfid1;
int rfidr;
int rsvet1;
int rsvet2;
int umsvet1;
int umsvet2;
int rkon1;
int rkon2;
int umkon1;
int umkon2;
int rkot1;
int rkot2;
int umkot1;
int umkot2;
float tempkotvent;
float tempkot;
float tempkon;
float tempotkl;
int rmenu;
int komfmenu;
int otpmenu;
int akomfmenu;
int aotpmenu;
int cekonommenu;
int acekonommenu;
int menu1;
int menumqtt;
int raspr;
unsigned long timer;
int as;
unsigned long tim;
unsigned long timrfid;
unsigned long timrsvet;
unsigned long timumsvet;
unsigned long timrkon;
unsigned long timumkon;
unsigned long timrkot;
unsigned long timumkot;
unsigned long timblynk;
unsigned long conblynk;
unsigned long timtemp;
bool l;
float temp; // создание переменных

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key; //rfid
DHTesp dht; //д. температуры
Servo myservo; // серво

void setup()
{
  setup_wifi(); //подключение к интернету
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); //подключение к mqtt
    
  dht.setup(5, DHTesp::DHT11);
  myservo.attach(2);
  pinMode(pir, INPUT);
  pinMode(kotel, OUTPUT);
  pinMode(vent, OUTPUT);
  pinMode(svet, OUTPUT);
  pinMode(12, OUTPUT); // объявление входов и выходов
  
  Serial.begin(9600); //монитор порта
  
  SPI.begin();
  rfid1 = 1;
  rfid.PCD_Init(); // запуск spi и rfid
  
  myservo.write(10); // начальное положение серво
  
  for (byte i = 0; i < 6; i++) { //обнуление массива для rfid
    key.keyByte[i] = 0xFF;
  }
  
  tim = millis();
  timrfid = millis();
  timer = millis(); //запуск секундомеров
}
