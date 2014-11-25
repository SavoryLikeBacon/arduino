/*
  Example for different sending methods
  
  http://code.google.com/p/rc-switch/
  
  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

int outlet_1 = 1398067;
int outlet_2 = 1398211;
int outlet_3 = 1398531;
int outlet_4 = 1408067;
int outlet_5 = 1406211;
int outlet_6 = 5527299;
int outlet_7 = 5526979;
const int ledPin =  13;  
void setup() {
   pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
  
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  // Optional set pulse length.
   mySwitch.setPulseLength(160);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  
  // Optional set number of transmission repetitions.
   mySwitch.setRepeatTransmit(15);
  
}

void loop() {



  /* Same switch as above, but using decimal code */
  digitalWrite(ledPin, HIGH);
  mySwitch.send(outlet_7, 24);
  delay(1000);  
  digitalWrite(ledPin, LOW);
  mySwitch.send((outlet_7 + 9), 24);



  delay(2000);
}
