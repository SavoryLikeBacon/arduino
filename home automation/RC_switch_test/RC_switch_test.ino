/*
  Example for different sending methods
  
  http://code.google.com/p/rc-switch/
  
  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
 int ledPin = 13;  
void setup() {

  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
   mySwitch.setPulseLength(160);
   // mySwitch.setPulseLength(180);
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
 
  // Optional set number of transmission repetitions.
 //  mySwitch.setRepeatTransmit(15);
pinMode(ledPin, OUTPUT);
}

void loop() {
    
  /* See Example: TypeA_WithDIPSwitches */

 
  
    mySwitch.send(5038035, 24); //on
     digitalWrite(ledPin, HIGH);
     mySwitch.send(5030035, 24);

  delay(1000);  
    
    
    mySwitch.send(5038044, 24); //off
  mySwitch.send(5030044, 24);
   digitalWrite(ledPin,LOW);
  delay(2000);

 
 

}
