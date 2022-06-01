void loop2(){
if ((analogRead(flame) < 800 || a == 1) && irflame == 1) { // flame
    a = 1;
    digitalWrite(red, LOW);
    digitalWrite(buzzersyr, HIGH);
    delay(10);
    digitalWrite(buzzersyr, LOW);
    digitalWrite(red, HIGH);
    delay(20);
  }
  if (irsr == 1) {
    if (sr04.Distance() < 8) { // sr вкл
      tim = millis();
      digitalWrite(ledm, HIGH);
      l = true;

    }
    if (millis() - tim > 3000 && l) { // sr выкл
      digitalWrite(ledm, LOW);
      l = false;

    }
  }
  if ((digitalRead(water) == 1 ||  b == 1) && irwater == 1) { // water
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
  if ((analogRead(vibr) > 20 || c == 1) && irvibr == 1) { // vibr
    digitalWrite(green, LOW);
    digitalWrite(buzzersyr, HIGH);
    delay(500);
    c = 1;
    digitalWrite(green, HIGH);
    digitalWrite(buzzersyr, LOW);
    delay(500);


  }
  if ((digitalRead(door) == 1 || d == 1) && irdoor == 1) { // door
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
  if ((digitalRead(pir) == 1 || e == 1) && irpir == 1) { //   pir
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
  if (irwater == 0 && irservo == 1) { // серво закрытие
    myservo.write(90);
  }
  if (irwater == 0 && irservo == 0) { // серво откурытие
    myservo.write(0);
  }
  //кажую половину секунды в монитор порта выводятся показания с датчика
}
