 /*  
  * PowerMeter.ino  
  *  
  * Created: 8/1/2014 2:08:39 PM  
  * Author: Alexandre Schaeffer  
  *  
  * ACS714 current reading based on code from:  
  * http://playground.arduino.cc/Main/CurrentSensing  
  * http://d.hatena.ne.jp/NeoCat/20110219/1298131557  
  */   
 int currentAnalogInputPin = 0;          // Analog input pin reading the current sensor  
 const int sensitivity = 66;               // mV/A, 185 for ASC714 -5A +5A, 66 for ASC714 -30A +30A  
 const int hz = 50;                         // frequency of power line  
 const int voltage = 230;               // Voltage of the current being measured  
 const int rawACTuning = 21;               // fine tuning of 0A AC reading! 512 = 0V  
 void setup()  
 {  
      Serial.begin(9600);  
 }  
 void loop()  
 {  
      readCurrent(true);
      delay(500);
 }  
 // Calculate current read with Allegro ACS714  
 // print: true to print measurement info  
 // Returns the sensed current in A  
 double readCurrent(bool print)  
 {  
      //Short version: mA = ((analogRead * 5000 / 1024) - 2500 ) / 66  
      //Short version: mA = ((analogReadAmplitude/2) * 5000 / 1024) / 66  
      int analogReadAmplitude = 0, min = 512, max = 0, filter = 13.93;  
      unsigned long start = millis();  
      do {  
           int val = 0;  
           for (int i = 0; i < filter; i++)  
                val += analogRead(currentAnalogInputPin);  
           val = (val / filter);     // fine tuning of 0A AC reading! 512 = 0V  
           if (max < val) max = val;  
           if (val < min) min = val;  
      } while (millis() - start <= 1100/hz);     //10% + to ensure p2p is acquired  
      analogReadAmplitude = (max - min) / 2;       
      long internalVcc = analogRead(A0);
      //long internalVcc = readInternalVcc();                         // should be around 5000  
      double sensedVoltage = (analogReadAmplitude * internalVcc) / 1024;     // (analogReadAmplitude/2) * 5000 / 1024               -> 0: 0               1024: 5000  
      double sensedCurrent = sensedVoltage / sensitivity;          // ((analogReadAmplitude/2) * 5000 / 1024) / 66     -> 0: -37,9A     1024: 37,9A  
      if(print){  
           //Serial.print("internalVcc mV: ");  
           //Serial.print(internalVcc);  
           //Serial.print(", AnalogIn: ");  
           //Serial.print(analogReadAmplitude);  
           //Serial.print(", Sensed Voltage mV: ");  
           //Serial.print(doubleToStr(sensedVoltage, 1));  
           //Serial.print(", VariationFromNull A: ");  
           //Serial.print(doubleToStr(sensedCurrent, 2));       // display Current  
           Serial.print(", power W: ");  
           Serial.println(doubleToStr(currentToPower(sensedCurrent), 2));  
      }  
      return sensedCurrent;  
 }  
 // Read 1.1V reference against AVcc  
 // Returns a voltage in mV that will be close to 5000 for the Arduino Yún  
 long readInternalVcc()  
 {  
      // set the reference to Vcc and the measurement to the internal 1.1V reference  
      #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)  
      ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);  
      #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)  
      ADMUX = _BV(MUX5) | _BV(MUX0) ;  
      #else  
//      ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);  
      #endif  
      delay(2); // Wait for Vref to settle  
//      ADCSRA |= _BV(ADSC); // Start conversion  
//      while (bit_is_set(ADCSRA,ADSC)); // measuring  
//      uint8_t low = ADCL; // must read ADCL first - it then locks ADCH  
//      uint8_t high = ADCH; // unlocks both  
//      long result = (high<<8) | low;  
//      result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000  
//      return result; // Vcc in millivolts  
 }  
 // Returns power in Watt (W)  
 // Watt = Ampere * Volt  
 double currentToPower(double current){  
      return current * voltage;  
 }  
 // Converts a double to a string  
 String doubleToStr(double val, byte precision)  
 {  
      String out = String(int(val));                   // Print int part  
      if( precision > 0) {                     // Print decimal part  
           out += ".";  
           unsigned long frac, mult = 1;  
           byte padding = precision -1;  
           while(precision--) mult *=10;  
           if(val >= 0) frac = (val - int(val)) * mult; else frac = (int(val) - val) * mult;  
           unsigned long frac1 = frac;  
           while(frac1 /= 10) padding--;  
           while(padding--) out += "0";  
           out += String(frac,DEC) ;  
      }  
      return out;  
 }  
