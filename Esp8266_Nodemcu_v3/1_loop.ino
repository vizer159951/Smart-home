void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();//подключатся к mqtt

  switch (menumqtt) { //определение режимов
    case 0:
      rmenu = 1;
      otpmenu = 0;
      komfmenu = 0;
      cekonommenu = 0;
      break;
    case 1:
      rmenu = 0;
      otpmenu = 1;
      komfmenu = 0;
      cekonommenu = 0;
      break;
    case 2:
      rmenu = 0;
      otpmenu = 0;
      komfmenu = 1;
      cekonommenu = 0;
      break;
    case 3:
      rmenu = 0;
      otpmenu = 0;
      komfmenu = 0;
      cekonommenu = 1;
      break;
  }
  ser1 = sermqtt;
  if (ser1 != ser2) { //управление серво вручную
    if (sermqtt == 0) {
      myservo.write(10);
      serd = 0;
    } else {
      myservo.write(70);
      serd = 1;
    }
  }
  ser2 = sermqtt;
  switch (raspr) { //отправка данных в mqtt в разное время
    case 0:
      if (millis() - timer > 500) {
        if (!isnan(dht.getTemperature())) {
          temp = dht.getTemperature();
        }
        dht.getStatusString();
        client.publish("temp", String(temp).c_str());
        client.publish("hum", String(dht.getHumidity()).c_str());
        raspr += 1;
        timer = millis();
        break;
      } else {
        break;
      }
    case 1:
      if (millis() - timer > 500) {
        if (analogRead(pir) > 500) {

          pir1 = 1;
        } else {
          pir1 = 0;
        }
        client.publish("pir1", String(pir1).c_str());
        raspr += 1;
        timer = millis();
        break;
      } else {
        break;
      }
    case 2:
      if (millis() - timer > 500 && millis() - timer < 700) {
        rfidvoid();
        raspr += 1;
        timer = millis();
        break;
      } else {
        break;
      }
    case 3:
      if (millis() - timer > 500) {
        client.publish("isvet", String(isvet).c_str());
        client.publish("ikot", String(ikot).c_str());
        client.publish("ikon", String(ikon).c_str()); // оправка данных в индикации состоянийt
        raspr += 1;
        timer = millis();
        break;
      } else {
        break;
      }
      case 4:
      if (millis() - timer > 500) {
  if (komfmenu == 1) { //режим уютный дом
    akomfmenu = 1;
    tempkotvent = 25;
    client.publish("tempkk", "25");
    tempotkl = 1;
    client.publish("tempotkl", "1");
    umkon = 1;
    client.publish("umkon", "1");
    umkot = 1;
    client.publish("umkot", "1");
    umsvet = 1;
    client.publish("umsvet", "1");
  } else {
    if (akomfmenu == 1) {
      akomfmenu = 0;
      client.publish("umkon", "0");
      client.publish("umkot", "0");
      client.publish("umsvet", "0");
    }
  }

  if (otpmenu == 1) { //режим отпуск
    aotpmenu = 1;
    myservo.write(70);
    client.publish("servoesp", "1");
    tempkotvent = 10;
    client.publish("tempkk", "10");
    tempotkl = 0;
    client.publish("tempotkl", "0");
    umkon = 0;
    client.publish("umkon", "0");
    umkot = 1;
    client.publish("umkot", "1");
    umsvet = 0;
    client.publish("umsvet", "0");
    rkon = 0;
    client.publish("rkon", "0");
    rsvet = 0;
    client.publish("rsvet", "0");

  } else {
    if (aotpmenu == 1) {
      aotpmenu = 0;
      client.publish("umkot", "0");
    }
  }
  if (cekonommenu == 1) { // эконом режим
    acekonommenu = 1;
    tempkotvent = 20;
    client.publish("tempkk", "20");
    tempotkl = 0;
    client.publish("tempotkl", "0");
    umkon = 0;
    client.publish("umkon", "0");
    umkot = 1;
    client.publish("umkot", "1");
    umsvet = 0;
    client.publish("umsvet", "0");
    rkon = 0;
    client.publish("rkon", "0");
    rsvet = 0;
    client.publish("rsvet", "0");
  } else {
    if (acekonommenu == 1) {
      acekonommenu = 0;
      client.publish("umkot", "0");
    }
  }

        raspr = 0;
        timer = millis();
        break;
      } else {
        break;
      }
  }
  if (umsvet == 1) { //умный свет
    aumsvet = 1;
    if (pir1 == 1) {
      digitalWrite(svet, HIGH);
      isvet = 1;
    } else {
      digitalWrite(svet, LOW);
      isvet = 0;
    }
  } else {
    if (aumsvet == 1) {
      isvet = 0;
      digitalWrite(svet, LOW);
      aumsvet == 0;
    }
  }
  if (rsvet == 1) {// ручной свет
    arsvet = 1;
    digitalWrite(svet, HIGH);
    isvet = 1;
  } else {
    if (arsvet == 1) {
      isvet = 0;
      digitalWrite(svet, LOW);
      arsvet = 0;
    }
  }

  if (rkot == 1) {//ручной котел
    arkot = 1;
    digitalWrite(kotel, HIGH);
    ikot = 1;
  } else {
    if (arkot == 1) {
      ikot = 0;
      digitalWrite(kotel, LOW);
      arkot = 0;
    }
  }
  if (rkon == 1) { //ручной кондиционер
    arkon = 1;
    digitalWrite(vent, HIGH);
    ikon = 1;
  } else {
    if (arkon == 1) {
      ikon = 0;
      digitalWrite(vent, LOW);
      arkon = 0;
    }
  }
  tempkot = tempkotvent - tempotkl; //температура для котла
  tempkon = tempkotvent + tempotkl; //темп. для кондиционера
  if (umkon == 1) { //умный кондиционер
    aumkon = 1;
    if (temp > tempkon) {
      digitalWrite(vent, HIGH);
      ikon = 1;
    } else {
      digitalWrite(vent, LOW);
      ikon = 0;
    }
  } else {
    if (aumkon == 1) {
      ikon = 0;
      digitalWrite(vent, LOW);
      aumkon = 0;
    }
  }

  if (umkot == 1) {//умный котел
    aumkot = 1;
    if (temp < tempkot) {
      digitalWrite(kotel, HIGH);
      ikot = 1;
    } else {
      digitalWrite(kotel, LOW);
      ikot = 0;
    }
  } else {
    if (aumkot == 1) {
      ikot = 0;
      digitalWrite(kotel, LOW);
      aumkot = 0;
    }
  }

  if (rsvet == 1 && umsvet == 1) { //выкл. ручного света или умного при вкл. обоих
    if (millis() - timrsvet > millis() - timumsvet) {
      client.publish("rsvet", "0");
    } else {
      client.publish("umsvet", "0");
    }
  }

  if (rkot == 1 && umkot == 1) {//выкл. ручного котла или умного при вкл. обоих
    if (millis() - timrkot > millis() - timumkot) {
      client.publish("rkot", "0");
    } else {
      client.publish("umkot", "0");
    }
  }
  if (rkon == 1 && umkon == 1) {//выкл. ручного кондиционера или умного при вкл. обоих
    if (millis() - timrkon > millis() - timumkon) {
      client.publish("rkon", "0");
    } else {
      client.publish("umkon", "0");
    }
  }
  if (rkon == 1 && rkot == 1) {//выкл. ручного котла или руч. кондиционера при вкл. обоих
    if (millis() - timrkon > millis() - timrkot) {
      client.publish("rkon", "0");
    } else {
      client.publish("rkot", "0");
    }
  }
}
