void looptx() {
  Ser buf; // создание экземпляра структуры
  
switch(b){ // запись в структуру данные о сигнал.
case 1: buf.sw = 1;
break;
case 0: buf.sw = 2;
break;
}
switch(a){
case 1: buf.sf = 1;
break;
case 0: buf.sf = 2;
break;
}
switch(c){
case 1: buf.sv = 1;
break;
case 0: buf.sv = 2;
break;
}
switch(d){
case 1: buf.sd = 1;
break;
case 0: buf.sd = 2;
break;
}
switch(e){
case 1: buf.sp = 1;
break;
case 0: buf.sp = 2;
break;
}
switch(irservo){
case 1: buf.ss = 1;
break;
case 0: buf.ss= 2;
break;
}
  if(millis() - timtx > 2000){
  mySerial.write((byte*)&buf, sizeof(buf));
  timtx = millis();
  } // каждые 2 сек. отправляются данные со структуры на esp01s
}
