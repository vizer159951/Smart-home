void functionON(int r = 255, int g = 255, int b = 255, int del1 = 1000, int buz = 0) {
  if(buz == 1){
    digitalWrite(buzzersyr, HIGH);
  }else{
    digitalWrite(buzzer, HIGH);
  }
  digitalWrite(blue, b);
  digitalWrite(red, r);
  digitalWrite(green, g);
  delay(del1);
  if(buz == 1){
    digitalWrite(buzzersyr, LOW);
  }else{
    digitalWrite(buzzer, LOW);
  }
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
} // оповещение пищалкой и RGB при включении функции
void functionOFF(int r = 255, int g = 255, int b = 255, int del1 = 500, int del2 = 100) {
  digitalWrite(buzzer, HIGH);
  digitalWrite(blue, b);
  digitalWrite(red, r);
  digitalWrite(green, g);
  delay(del1);
  digitalWrite(buzzer, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(del2);
  digitalWrite(buzzer, HIGH);
  digitalWrite(blue, b);
  digitalWrite(red, r);
  digitalWrite(green, g);
  delay(del1);
  digitalWrite(buzzer, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(del2);
  digitalWrite(buzzer, HIGH);
  digitalWrite(blue, b);
  digitalWrite(red, r);
  digitalWrite(green, g);
  delay(del1);
  digitalWrite(buzzer, LOW);
  digitalWrite(blue, HIGH);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(del2);
}// оповещение пищалкой и RGB при выключении функции
