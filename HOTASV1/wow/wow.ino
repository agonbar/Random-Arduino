#include <Mouse.h>
#include <Keyboard.h>

const int pinToButtonMap = 15;

void setup(){
  //Mouse.begin();
  Keyboard.begin();
  Serial.begin(9600);
  pinMode(pinToButtonMap, INPUT_PULLUP);
}

void loop(){
  delay(1000);
  
   /*for(int y = 1; y <= 100; y++){
       for(int x = 1; x <= 100; x++){
           delay(100);
           Mouse.move(x, y);
       }
   }*/
  if (digitalRead(pinToButtonMap) == 0)
  {
    Serial.write('1');
    //corrección inicial
    Keyboard.press('d');
    delay(random(50,100));
    Keyboard.release('d');
    //pasillito
    Keyboard.press('w');
    delay(random(4600,5100));
    Keyboard.press('d');
    Serial.write('2');
    delay(random(600,650));
    Keyboard.release('d');
    Serial.write('3');
    delay(random(18000,20000));
    //primer pasillo preboss
    Keyboard.press('a');
    delay(random(50,100));
    Keyboard.release('a');
    Keyboard.press('e');
    delay(random(450,500));
    Keyboard.release('e');
    Serial.write('4');
    delay(random(20000,22000));
    Keyboard.press('d');
    delay(random(550,650));
    Keyboard.release('d');
    Serial.write('5');
    delay(random(5500,6000));
    Keyboard.press('d');
    delay(random(550,650));
    Keyboard.release('d');
    delay(random(5000,5500));
    Keyboard.press('d');
    delay(random(300,350));
    Keyboard.release('d');
    delay(random(5500,6000));
    Keyboard.press('a');
    delay(random(300,350));
    Keyboard.release('a');
    delay(random(15500,16000));
    Keyboard.releaseAll();
  }
}
//a
