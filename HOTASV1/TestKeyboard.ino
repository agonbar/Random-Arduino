#include <Joystick.h>

Joystick_ Joystick;

const int pinToButtonMap = 15;
const int X_pin = 0;
const int Y_pin = 1;
const int Slider_pin = 2;

int treatValue(int data) {
  return (data * 9 / 1024) + 48;
}

void setup() {
  pinMode(pinToButtonMap, INPUT_PULLUP);
  //Serial.begin(9600);
  Joystick.begin();
}

//Axis button
int lastButtonState = 0;
int currentButtonState = 0;

//Slider
int lastSliderRead = 0;
int currentSliderRead = 0;

//Y Axis
int lastYRead = 0;
int currentYRead = 0;

//X Axis
int lastXRead = 0;
int currentXRead = 0;

void loop() {

  // Read pin values
  currentButtonState = !digitalRead(pinToButtonMap);
  if (currentButtonState != lastButtonState)
  {
    Joystick.setButton(0, currentButtonState);
    lastButtonState = currentButtonState;
  }

  //Read slider
  currentSliderRead = analogRead(Slider_pin);
  if (currentSliderRead != lastSliderRead) {
    Joystick.setThrottle(currentSliderRead);
    lastSliderRead = currentSliderRead;
  }

  //Read Y Axis
  currentYRead = analogRead(Y_pin);
  if (currentYRead != lastYRead) {
    Joystick.setYAxis(currentYRead);
    lastYRead = currentYRead;
  }

  //Read X Axis
  currentXRead = analogRead(X_pin);
  if (currentXRead != lastXRead) {
    Joystick.setXAxis(currentXRead);
    lastXRead = currentXRead;
  }

  delay(100);
}/*
  void loop() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(pinToButtonMap));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n");
  Serial.print("Slider: ");
  Serial.println(analogRead(Slider_pin));
  Serial.print("\n\n");
  delay(1000);
  }
*/
