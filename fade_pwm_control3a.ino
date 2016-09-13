/*
 Fade this example shows how to fade an LED on pin 9
 using the analogWrite() function.
*/
/* http://playground.arduino.cc/Code/PwmFrequency
 * Divides a given PWM pin frequency by a divisor.
 * 
 * The resulting frequency is equal to the base frequency divided by
 * the given divisor:
 *   - Base frequencies:
 *      o The base frequency for pins 3, 9, 10, and 11 is 31250 Hz.
 *      o The base frequency for pins 5 and 6 is 62500 Hz.
 *   - Divisors:
 *      o The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64,
 *        256, and 1024.
 *      o The divisors available on pins 3 and 11 are: 1, 8, 32, 64,
 *        128, 256, and 1024.
 * 
 * PWM frequencies are tied together in pairs of pins. If one in a
 * pair is changed, the other is also changed to match:
 *   - Pins 5 and 6 are paired on timer0
 *   - Pins 9 and 10 are paired on timer1
 *   - Pins 3 and 11 are paired on timer2
 * 
 * Note that this function will have side effects on anything else
 * that uses timers:
 *   - Changes on pins 3, 5, 6, or 11 may cause the delay() and
 *     millis() functions to stop working. Other timing-related
 *     functions may also be affected.
 *   - Changes on pins 9 or 10 will cause the Servo library to function
 *     incorrectly.
 * 
 * Thanks to macegr of the Arduino forums for his documentation of the
 * PWM frequency divisors. His post can be viewed at:
 *   http://forum.arduino.cc/index.php?topic=16612#msg121031
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led1= 13;

byte led = 9;          // the pin that the LED is attached to
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int intarziere = 1000;
int intarziere2 = 3000;

byte caz = 0;
/* for D9
   caz = 0;   divider = 1     frequency = 31250Hz
   caz = 1    divider = 8     frequency ~ 3910Hz
   caz = 2    divider = 64    frequency ~ 490Hz
   caz = 3    divider = 256   frequency = 122Hz
   caz = 4    divider = 1024  frequency = 30Hz
*/

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
    // initialize the digital pin as an output.
  pinMode(led1, OUTPUT);    
  digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
setPwmFrequency(9, 8); // set base frequency
} 

// the loop routine runs over and over again forever:
void loop()  { 

  // set the brightness of pin 9:
  analogWrite(led, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if ((brightness <= 0) || (brightness >= 255)) {
    fadeAmount = -fadeAmount ; 
     digitalWrite(led1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(intarziere2);
     digitalWrite(led1, LOW);    // turn the LED off by making the voltage LOW
/*
caz = caz + 1;
if (caz >4) caz = 0;   
if (caz == 0) setPwmFrequency(9, 1);
if (caz == 1) setPwmFrequency(9, 8);
if (caz == 2) setPwmFrequency(9, 64);
if (caz == 3) setPwmFrequency(9, 256);
if (caz == 4) setPwmFrequency(9, 1024);
*/
  }     
delay(intarziere);

}

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
