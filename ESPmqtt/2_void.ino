void setup_wifi() { //подключение к интернету
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

void callback(char* topic, byte* payload, unsigned int length) {//прием данных с топиков
  String data_pay;
  for (int i = 0; i < length; i++) {
    data_pay += String((char)payload[i]);
  }
  if (String(topic) == "mode") {
    menumqtt = sti(data_pay);
  }
  if (String(topic) == "servoesp") {
    sermqtt = sti(data_pay);
  }
  if (String(topic) == "rfid") {
    rfidr = sti(data_pay);
  }
  if (String(topic) == "rsvet") {
    rsvet = sti(data_pay);
  }
    if (String(topic) == "umsvet") {
    umsvet = sti(data_pay);
  }
      if (String(topic) == "rkot") {
    rkot = sti(data_pay);
  }
      if (String(topic) == "umkot") {
    umkot = sti(data_pay);
  }
      if (String(topic) == "rkon") {
    rkon = sti(data_pay);
  }
      if (String(topic) == "umkon") {
    umkon = sti(data_pay);
  }
        if (String(topic) == "tempkk") {
    tempkontvent = sti(data_pay);
  }
          if (String(topic) == "tempotkl") {
    tempotkl = sti(data_pay);
  }
}

void reconnect() { //подключение к mqtt
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266-" + WiFi.macAddress();
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password) ) {
      Serial.println("connected");

      client.subscribe( (relay_topic + "/#").c_str() );
      client.subscribe( (String("mode") + "/#").c_str() );
      client.subscribe( (String("servoesp") + "/#").c_str() );
      client.subscribe( (String("rfid") + "/#").c_str() );
      client.subscribe( (String("rsvet") + "/#").c_str() );
      client.subscribe( (String("umsvet") + "/#").c_str() );
      client.subscribe( (String("rkot") + "/#").c_str() );
      client.subscribe( (String("umkot") + "/#").c_str() );
      client.subscribe( (String("rkon") + "/#").c_str() );
      client.subscribe( (String("umkon") + "/#").c_str() );
      client.subscribe( (String("tempkk") + "/#").c_str() );
      client.subscribe( (String("tempotkl") + "/#").c_str() );
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
int sti(String St) {
  int i = St.toInt();
  return i;
} //перевод из String в int
void rfidvoid() { //считывание и сравнение данных с rfid
  if (rfid1 == 1) {
    rfid1 = 0;
    if ( ! rfid.PICC_IsNewCardPresent())
      return;
    if ( ! rfid.PICC_ReadCardSerial())
      return;
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
        piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
      return;
    }
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
    if ((rfid.uid.uidByte[0] == b0) && (rfid.uid.uidByte[1] == b1) && (rfid.uid.uidByte[2] == b2) && (rfid.uid.uidByte[3] == b3) && rfidr == 1) {
      if (serd == 1) {
        serd = 0;
        myservo.write(10);
        client.publish("servoesp", "0");
      } else {
        serd = 1;
        myservo.write(70);
        client.publish("servoesp", "1");
      }
    } else {
      myservo.write(70);
      client.publish("servoesp", "1");
    }
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  } else {
    rfid1 = 1;
  }
}
