/*
 Fade
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
  This example code is in the public domain.

changed & tested by Nicu FLORICA (niq_ro) from http://www.tehnic.go.ro
http://nicuflorica.blogspot.ro
http://arduinotehniq.blogspot.com/
http://www.arduinotehniq.com/
*/

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1= 13;

int led = 9;           // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int intarziere = 1000;

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
    // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);    
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of pin 9:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
     digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(5000);
     digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
  }     
//  // wait for 30 milliseconds to see the dimming effect    
//  delay(30);                            
delay(intarziere);
}
