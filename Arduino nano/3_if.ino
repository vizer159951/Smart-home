void loop2(){
if ((analogRead(flame) < 800 || a == 1) && irflame == 1) { // сигнал. при пожаре
    a = 1;
    digitalWrite(red, LOW);
    digitalWrite(buzzersyr, HIGH);
    delay(10);
    digitalWrite(buzzersyr, LOW);
    digitalWrite(red, HIGH);
    delay(20);
  }
  if (irsr == 1) { // ультразвуковой датчик
    if (sr04.Distance() < 8) { // светодиод вкл
      tim = millis();
      digitalWrite(ledm, HIGH);
      l = true;

    }
    if (millis() - tim > 3000 && l) { // светодиод выкл
      digitalWrite(ledm, LOW);
      l = false;

    }
  }
  if ((digitalRead(water) == 1 ||  b == 1) && irwater == 1) { // сигнал. при протечке
    myservo.write(90);
    digitalWrite(blue, LOW);
    digitalWrite(buzzersyr, HIGH);
    delay(100);
    b = 1;
    digitalWrite(blue, HIGH);
    digitalWrite(buzzersyr, LOW);
    delay(100);
    irservo = 1;

  }
  if ((analogRead(vibr) > 20 || c == 1) && irvibr == 1) { // сигнал. при землетряс.
    digitalWrite(green, LOW);
    digitalWrite(buzzersyr, HIGH);
    delay(500);
    c = 1;
    digitalWrite(green, HIGH);
    digitalWrite(buzzersyr, LOW);
    delay(500);


  }
  if ((digitalRead(door) == 1 || d == 1) && irdoor == 1) { // сигнал. при открытии двери
    d = 1;
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    delay(200);
    digitalWrite(buzzersyr, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
    delay(200);
    digitalWrite(buzzersyr, LOW);

  }
  if ((digitalRead(pir) == 1 || e == 1) && irpir == 1) { // сигнал. при обнар. движения
    e = 1;
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    delay(50);
    digitalWrite(buzzersyr, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(red, HIGH);
    delay(50);
    digitalWrite(buzzersyr, LOW);

  }
  if (irwater == 0 && irservo == 1) { // водопровод закрытие
    myservo.write(90);
  }
  if (irwater == 0 && irservo == 0) { // водопровод открытие
    myservo.write(0);
  }
}
