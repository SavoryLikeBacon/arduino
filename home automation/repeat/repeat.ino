
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
  mySwitch.enableTransmit(10);
  mySwitch.setPulseLength(170);
  //mySwitch.setRepeatTransmit(4);
  long temp= 0;
}

void loop() {
  if (mySwitch.available()) {
    
   // int temp = mySwitch.getReceivedValue();
   // Serial.println(temp);
    //1406211
    //Serial.println(mySwitch.getReceivedValue());
    mySwitch.send(mySwitch.getReceivedValue(), 24);
    Serial.println("mimicing");
    //Serial.println(temp);
  /*  
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }
    */

    mySwitch.resetAvailable();
  }
}
