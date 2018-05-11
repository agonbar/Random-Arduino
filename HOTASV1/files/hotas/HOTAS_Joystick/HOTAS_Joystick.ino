/*  Arduino Micro HOTAS Joystick

    This is the programming of the custom joystick,
    made with an Arduino Micro and mostly 3D printed parts.

    Made 06-10-2016
    By Kenny Verhoeven
*/

//This includes the Joystick library into the sketch
#include <Joystick.h>


Joystick_ Joystick;

//The list of numbers and pins that are being defined
int ThrottlePin = A2;
int Button1 = 6;
int Button2 = 4;
int Button3 = 3;
int Button4 = 5;
int Button5 = 2;
int Buttons6_11 = 19;
int Buttons12_14 = 20;
int ThumbXAxis = A0;
int ThumbYAxis = A1;
int ButtonState1 = HIGH;
int ButtonState2 = HIGH;
int ButtonState3 = HIGH;
int ButtonState4 = HIGH;
int ButtonState5 = HIGH;
int ButtonState6_11 = 1023;
int ButtonState12_14 = 1023;
int ButtonState1Last = HIGH;
int ButtonState2Last = HIGH;
int ButtonState3Last = HIGH;
int ButtonState4Last = HIGH;
int ButtonState5Last = HIGH;
int ButtonState6_11Last = 1023;
int ButtonState12_14Last = 1023;
int ThrottleRaw;
int Throttle;
int ThumbXRaw;
int ThumbYRaw;
int ThumbX;
int ThumbY;

void setup() {
//Declaring the initial settings and modes of the pins
  pinMode(ThrottlePin, INPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);
  pinMode(Button5, INPUT_PULLUP);
  pinMode(Buttons6_11, INPUT);
  pinMode(Buttons12_14, INPUT);
  pinMode(ThumbXAxis, INPUT);
  pinMode(ThumbYAxis, INPUT);

//Initialize the Joystick connection to the system
  Joystick.begin();
}

void loop() {
//Reading the raw data from the inputs
  ThrottleRaw = analogRead(ThrottlePin);
  ButtonState1 = !digitalRead(Button1);
  ButtonState2 = !digitalRead(Button2);
  ButtonState3 = !digitalRead(Button3);
  ButtonState4 = !digitalRead(Button4);
  ButtonState5 = !digitalRead(Button5);
  ButtonState6_11 = analogRead(Buttons6_11);
  ButtonState12_14 = analogRead(Buttons12_14);
  ThumbXRaw = analogRead(ThumbXAxis);
  ThumbYRaw = analogRead(ThumbYAxis);

//Calculation/Correction of the input data
  Throttle = (ThrottleRaw / 4);
  ThumbX = (ThumbXRaw / 8);
  ThumbY = (ThumbYRaw / 8);

//Checks if the Joystick buttons are pressed one by one and outputs the value to the system
  if (ButtonState1 != ButtonState1Last)
  {
    Joystick.setButton(0, ButtonState1);
    ButtonState1Last = ButtonState1;
  }
  if (ButtonState2 != ButtonState2Last)
  {
    Joystick.setButton(1, ButtonState2);
    ButtonState2Last = ButtonState2;
  }
  if (ButtonState3 != ButtonState3Last)
  {
    Joystick.setButton(2, ButtonState3);
    ButtonState3Last = ButtonState3;
  }
  if (ButtonState4 != ButtonState4Last)
  {
    Joystick.setButton(3, ButtonState4);
    ButtonState4Last = ButtonState4;
  }
  if (ButtonState5 != ButtonState5Last)
  {
    Joystick.setButton(4, ButtonState5);
    ButtonState5Last = ButtonState5;
  }


//Checks if the bottom buttons are pressed one by one and outputs the value to the system
  if (ButtonState6_11 > 850 && ButtonState6_11 < 870)
  {
    Joystick.setButton(5, HIGH);
    ButtonState6_11Last = ButtonState6_11;
  }
  else if (ButtonState6_11 > 815 && ButtonState6_11 < 835)
  {
    Joystick.setButton(6, HIGH);
    ButtonState6_11Last = ButtonState6_11;
  }
  else if (ButtonState6_11 > 765 && ButtonState6_11 < 785)
  {
    Joystick.setButton(7, HIGH);
    ButtonState6_11Last = ButtonState6_11;
  }
  else if (ButtonState6_11 > 600 && ButtonState6_11 < 750)
  {
    Joystick.setButton(8, HIGH);
    ButtonState6_11Last = ButtonState6_11;
  }
  else if (ButtonState6_11 > 500 && ButtonState6_11 < 550)
  {
    Joystick.setButton(9, HIGH);
    ButtonState6_11Last = ButtonState6_11;
  }
  else if (ButtonState6_11 < 500)
  {
    Joystick.setButton(10, HIGH);
    ButtonState6_11Last = ButtonState6_11;
  }
  else if (ButtonState6_11 > 1000)
  {
    Joystick.setButton(5, LOW);
    Joystick.setButton(6, LOW);
    Joystick.setButton(7, LOW);
    Joystick.setButton(8, LOW);
    Joystick.setButton(9, LOW);
    Joystick.setButton(10, LOW);
  }

//Checks if the right buttons are pressed one by one and outputs the value to the system
  if (ButtonState12_14 > 600 && ButtonState12_14 < 750)
  {
    Joystick.setButton(11, HIGH);
    ButtonState12_14Last = ButtonState12_14;
  }
  else if (ButtonState12_14 > 500 && ButtonState12_14 < 600)
  {
    Joystick.setButton(12, HIGH);
    ButtonState12_14Last = ButtonState12_14;
  }
  else if (ButtonState12_14 < 500)
  {
    Joystick.setButton(13, HIGH);
    ButtonState12_14Last = ButtonState12_14;
  }
  else if (ButtonState12_14 > 1000)
  {
    Joystick.setButton(11, LOW);
    Joystick.setButton(12, LOW);
    Joystick.setButton(13, LOW);

  }

//Output the x-/y-axis and the throttle values to the system
  Joystick.setThrottle(Throttle);
  Joystick.setXAxis(ThumbX);
  Joystick.setYAxis(ThumbY);

//End of loop delay to make sure there are no double values in the inputs
  delay(50);
}
