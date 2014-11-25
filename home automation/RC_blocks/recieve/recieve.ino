/*
  Example for receiving
  
  http://code.google.com/p/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
  
  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>
#include <Servo.h> 

Servo blindServo;
RCSwitch mySwitch = RCSwitch();

int ledPin = 6;
int buttonPin = 5;
int relayPin = 7;
int state = 0;

int key =0;
const int read_key_open = 803711;
const int read_key_closed = 803703;

void setup() {
  blindServo.attach(9);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT); //apply power to  servo
  pinMode(buttonPin, INPUT);
  //pinMode(blindServo,OUTPUT);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 => that is pin #2
}

void loop() {
  //Serial.println("looping");
  
 /* if( digitalRead(buttonPin)){
   
    blindServo.write(45);
    digitalWrite(ledPin, HIGH);
  }else{
    
    
    blindServo.write(135); 
    digitalWrite(ledPin, LOW);
  }
  */
   
  if (mySwitch.available()) {
    key = mySwitch.getReceivedValue();
    Serial.print("something recieved: ");
    Serial.println(mySwitch.getReceivedValue());
    
    if((key == read_key_open) && (state == 0)){
       //Serial.print("key correct");
       //Serial.println(mySwitch.getReceivedValue());
       
       blindServo.write(180); 
       state = 1;
       digitalWrite(ledPin,HIGH);
       digitalWrite(relayPin,HIGH);
       Serial.println("Opening blinds");
       delay(3000);
       digitalWrite(ledPin,LOW);
       digitalWrite(relayPin,LOW);
    }
    
    if((key == read_key_closed) && (state == 1)){
       //Serial.print("key correct");
       //Serial.println(mySwitch.getReceivedValue());
       
       blindServo.write(0); 
       state = 0;
       digitalWrite(ledPin,HIGH);
       digitalWrite(relayPin,HIGH);
       Serial.println("closing blinds");
       delay(3000);
       digitalWrite(ledPin,LOW);
       digitalWrite(relayPin,LOW);
    }
    
    //output(mySwitch.getReceivedValue(), mySwitch.getReceivedBitlength(), mySwitch.getReceivedDelay(), mySwitch.getReceivedRawdata(),mySwitch.getReceivedProtocol());
    mySwitch.resetAvailable();
    key=0;
}
  
  //delay(10);
}
