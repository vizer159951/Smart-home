#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h> // подключение библиотек

SoftwareSerial mySerial(0, 2); // создание порта для приема
                               // данных с arduino nano

struct Ser {
  int sf;
  int sv;
  int sp;
  int sw;
  int sd;
  int ss;
}; //создание структуры для записи получаемых данных

Ser buf; // создание экземпляра структуры

const char* ssid = "TP-Link_DC2D";
const char* password = "32384244"; // данные для подключения к интернету

const char* mqtt_server = "m4.wqtt.ru";
const int mqtt_port = 5140;
const char* mqtt_user = "u_50UPHV";
const char* mqtt_password = "DRvhTF7K"; // данные для подключения к wqqt

WiFiClient espClient;
PubSubClient client(espClient); // создание клиентов

void setup_wifi() { // подключение к интернету
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String data_pay;
  for (int i = 0; i < length; i++) {
    data_pay += String((char)payload[i]);
  } // прием данных с топика
}

void reconnect() { // подключение к mqtt
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266-" + WiFi.macAddress();
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password) ) {
      Serial.println("connected");

      client.subscribe( (relay_topic + "/#").c_str() );

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); //монитор порта
  setup_wifi(); //подключение к интернету
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // начало работы с mqtt
  mySerial.begin(9600); // настройка порта для получения данных
  for (int k = 0; k < 10; k++) {
    digitalWrite(LED_BUILTIN, 0);
    delay(100);
    digitalWrite(LED_BUILTIN, 1);
    delay(100);
  } // проверка на благополучное подключение
}

void loop() {
  if (!client.connected()) { 
    reconnect();
  } //в случае отсоединения от mqtt: подключатся
  client.loop(); // начать работу с mqtt
  if (mySerial.readBytes((byte*)&buf, sizeof(buf))) { //отправка данных на wqtt сервер
    if (buf.sf == 1) {
      client.publish("flame", "1");
    } else {
      client.publish("flame", "0");
    }
    if (buf.sw == 1 ) {
      client.publish("water", "1");
      Serial.println("water");
    } else {
      client.publish("water", "0");
    }
    if (buf.sv == 1) {
      client.publish("vibr", "1");
    } else {
      client.publish("vibr", "0");
    }
    if (buf.sd == 1) {
      client.publish("door", "1");
    } else {
      client.publish("door", "0");
    }
    if (buf.sp == 1) {
      client.publish("pir", "1");
    } else {
      client.publish("pir", "0");
    }
    if (buf.ss == 1) {
      client.publish("servo", "1");
    } else {
      client.publish("servo", "0");
    }
  }
}
