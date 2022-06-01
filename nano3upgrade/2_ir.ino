void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFF5AA5 && irsr == 0) { светодиод вкл/выкл
      if (led1 == 0) {
        digitalWrite(ledm, HIGH);
        led1 = 1;
        functionON(0, 0, 0, 50);
      } else {
        digitalWrite(ledm, LOW);
        led1 = 0;
        functionOFF(0, 0, 0, 50, 10);
      }
    }
    if (results.value == 0xFF38C7) { // ультразвуковой д. вкл/выкл
      if (sr1 == 1) {
        functionOFF(0, 0, 0);
        irsr = 0;
        sr1 = 0;
        digitalWrite(ledm, LOW);
        led1 = 0;
      } else {
        functionON(0, 0, 0);
        irsr = 1;
        sr1 = 1;
        digitalWrite(ledm, LOW);
        led1 = 0;
      }
    }
    if (results.value == 0xFF10EF) { // пищалка вкл/выкл
      if (buzzer1 == 1) {
        functionOFF();
        buzzer = 20;
        buzzer1 = 0;
      } else {
        functionON(255,255,255,1000,1);
        buzzer = 11;
        buzzer1 = 1;
      }
    }
    if (results.value == 0xFF6897) { // д. воды вкл/выкл
      if (water1 == 1) {
        functionOFF(255, 255, 0);
        b = 0;
        irwater = 0;
        water1 = 0;
        irservo = 0;
      } else {
        functionON(255, 255, 0);
        irwater = 1;
        water1 = 1;
      }
    }
    if (results.value == 0xFF7A85) { // servo вкл/выкл
      if (irwater == 0) {
        if (servo1 == 1) {
          functionOFF(0, 0);
          servo1 = 0;
          irservo = 0;
        } else {
          functionON(0, 0);
          irservo = 1;
          servo1 = 1;
        }
      }
    }
    if (results.value == 0xFF9867) { // д. пламени вкл/выкл
      if (flame1 == 1) {
        functionOFF(0);
        a = 0;
        irflame = 0;
        flame1 = 0;
      } else {
functionON(0);
        irflame = 1;
        flame1 = 1;
      }
    }
    if (results.value == 0xFFB04F) { // д. вибрации вкл/выкл
      if (vibr1 == 1) {
functionOFF(255,0);
        c = 0;
        irvibr = 0;
        vibr1 = 0;
      } else {
functionON(255,0);
        irvibr = 1;
        vibr1 = 1;
      }
    }
    if (results.value == 0xFF30CF) { // д. движения выкл/вкл
      if (pir1 == 1) {
        functionOFF(0,255,0);
        irpir = 0;
        pir1 = 0;
        e = 0;
      } else {
        functionON(0,255,0);
        irpir = 1;
        pir1 = 1;
      }
    }
    if (results.value == 0xFF18E7) { // д. откр. двери вкл/выкл
      if (door1 == 0) {
       functionON(255,0,0);
        irdoor = 1;
        door1 = 1;
      } else {
        functionOFF(255,0,0);
        irdoor = 0;
        d = 0;
        door1 = 0;
      }
    }
    if (results.value == 0xFF02FD) { //проверка какие функции включены
      if (irwater == 1) {
        digitalWrite(blue, LOW);
        delay(1000);
        digitalWrite(blue, HIGH);
        delay(500);
      }
      if (irservo == 0) {
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        delay(1000);
        digitalWrite(red, HIGH);
        digitalWrite(green, HIGH);
        delay(500);
      }
      if (irflame == 1) {
        digitalWrite(red, LOW);
        delay(1000);
        digitalWrite(red, HIGH);
        delay(500);
      }
      if (irvibr == 1) {
        digitalWrite(green, LOW);
        delay(1000);
        digitalWrite(green, HIGH);
        delay(500);
      }
      if (irpir == 1) {
        digitalWrite(red, LOW);
        digitalWrite(blue, LOW);
        delay(1000);
        digitalWrite(blue, HIGH);
        digitalWrite(red, HIGH);
        delay(500);
      }
      if (irdoor == 1) {
        digitalWrite(blue, LOW);
        digitalWrite(green, LOW);
        delay(1000);
        digitalWrite(blue, HIGH);
        digitalWrite(green, HIGH);
        delay(500);
      }
    }
    if (results.value == 0xFF629D) { //отключение сигнализаций
      a = 0;
      b = 0;
      c = 0;
      d = 0;
      e = 0;
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);
      digitalWrite(buzzer, LOW);
    }
    irrecv.resume();
  }
  loop2();
  looptx(); //запуск других циклов
}
