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
  pinMode(ledPin, OUTPUT);   
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
  mySwitch.setPulseLength(320);
  
  // Optional set protocol (default is 1, will work for most outlets)
  mySwitch.setProtocol(1);
  
  // Optional set number of transmission repetitions.
   mySwitch.setRepeatTransmit(15);
  
}

void loop() {

  /* See Example: TypeA_WithDIPSwitches */
 /* mySwitch.switchOn("11111", "00010");
  delay(1000);
  mySwitch.switchOn("11111", "00010");
  delay(1000);*/

  /* Same switch as above, but using decimal code */
 /* mySwitch.send(803701, 24);
  delay(1000);  
  mySwitch.send(5396, 24);
  delay(1000);  */

  /* Same switch as above, but using binary code */
  mySwitch.send(803701, 24);
  //mySwitch.send("000011000100001101110101");
  // delay(1000);  
  //mySwitch.send("000000000001010100010100");
  delay(500);
  digitalWrite(ledPin,HIGH);
  delay(500);
  digitalWrite(ledPin,LOW);
  /* Same switch as above, but tri-state code */ 
 /* mySwitch.sendTriState("00000FFF0F0F");
  delay(1000);  
  mySwitch.sendTriState("00000FFF0FF0");
  delay(1000);*/

 // delay(20000);
}
