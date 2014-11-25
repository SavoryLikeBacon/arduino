/*
  Example for receiving
  
  http://code.google.com/p/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
  
  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int key = 803701;
int ledPin = 13;
int read_key = 0;
void setup() {
  Serial.begin(9600);
   pinMode(ledPin, OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  //Serial.println("looping");
  if (mySwitch.available()) {
    read_key = mySwitch.getReceivedValue();
    //Serial.print("something recieved");
    
    if(key == read_key){
       Serial.print("key correct");
       Serial.println(mySwitch.getReceivedValue());
       digitalWrite(ledPin,HIGH);
       delay(1000);
       digitalWrite(ledPin,LOW);
             
    }
    //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
  }
  //delay(10);
}
