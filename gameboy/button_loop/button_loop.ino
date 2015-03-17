
//#define DEBUG1  //show button logic messages
//#define DEBUG2 //show analof read messages
//#define DEBUG3 // output a mask of the buttons

//button check debug
#ifdef DEBUG1
  #define _DBG1(x) x
#else
  #define _DBG1(x)
#endif

//debug for analog input for battery
#ifdef DEBUG2
  #define _DBG2(x) x
#else
  #define _DBG2(x)
#endif

#ifdef DEBUG3
  #define _DBG3(x) x
#else
  #define _DBG3(x)
#endif

#define DEBOUNCE 20
#include <avr/sleep.h>
// the setup function runs once when you press reset or power the board


 //button inputs and booleans
 



button_type button[8];


button[0].pin = 2; // Select pin
button[1].pin = 3; //  Start pin
button[2].pin = 4; //  A pin
button[3].pin = 5; //  B pin
button[4].pin = 6; //  Up pin
button[5].pin = 7; //  Down pin
button[6].pin = 8; //  Left pin
button[7].pin = 9; //  Right pin
 
button[0].state = false;
button[1].state = false;
button[2].state = false;
button[3].state = false;
button[4].state = false;
button[5].state = false;
button[6].state = false;
button[7].state = false;

button[0].key = 0; // select key
button[1].key = 0; // start key
button[2].key = 65; // a key
button[3].key = 83; // s key
button[4].key = 38; // up key
button[5].key = 40; // down key
button[6].key = 37; // left key
button[7].key = 39; // right key
 
//boolean Select_btn_bool = false;
//boolean Start_btn_bool = false;
//boolean A_btn_bool = false;
//boolean B_btn_bool = false;
//boolean Up_btn_bool = false;
//boolean Down_btn_bool = false;
//boolean Left_btn_bool = false;
//boolean Right_btn_bool = false;
  
//debug mask
 String temp = "";
  
  //supervisory inputs
int battery_pin = 2; // analog input for battery
  
  //alert outputs
int low_voltage = 10; 

void setup() {
  
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  for (int i = 0; i < 8; i ++){
      pinMode(button[i].pin, INPUT);
      digitalWrite(button[i].pin, HIGH);       // turn on pullup resistors
  }
//  pinMode(bu, INPUT);
//  digitalWrite(Select_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(Start_btn_pin, INPUT);
//  digitalWrite(Start_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(A_btn_pin, INPUT);
//  digitalWrite(A_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(B_btn_pin, INPUT);
//  digitalWrite(B_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(Up_btn_pin, INPUT);;
//  digitalWrite(Up_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(Down_btn_pin, INPUT);
//  digitalWrite(Down_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(Left_btn_pin, INPUT);
//  digitalWrite(Left_btn_pin, HIGH);       // turn on pullup resistors
//  pinMode(Right_btn_pin, INPUT);
//  digitalWrite(Right_btn_pin, HIGH);       // turn on pullup resistors
//  
  //initialize keybaord
  Keyboard.begin();
}

// the loop function runs over and over again forever
void loop() {
  //battery_check(low_voltage);
  
  for (int i = 0; i < 8; i ++){
     check_btn(button[i].pin, button[i].state);
  }
  
  //check_btn(Select_btn_pin, Select_btn_bool); //check the select button
  //check_btn(Start_btn_pin, Start_btn_bool); //check the start button
  //check_btn(A_btn_pin, A_btn_bool); //check the A button
  //check_btn(B_btn_pin, B_btn_bool); //check the B button
  //check_btn(Up_btn_pin, Up_btn_bool); //check the up button
  //check_btn(Down_btn_pin, Down_btn_bool); //check the down button
  //check_btn(Left_btn_pin, Left_btn_bool); //check the left button
  //check_btn(Right_btn_pin, Right_btn_bool); //check the right button
  
  
  #ifdef DEBUG3
    temp = "";
    for (int i = 0; i < 8; i ++){
     build_mask(button[i].pin);
    }
//    build_mask(Select_btn_pin);
//    build_mask(Start_btn_pin);
//    build_mask(A_btn_pin);
//    build_mask(B_btn_pin);
//    build_mask(Up_btn_pin);
//    build_mask(Down_btn_pin);
//    build_mask(Left_btn_pin);
//    build_mask(Right_btn_pin);
    Serial.println("button key : SSABUDLR");
    Serial.print("button mask: "); 
    Serial.println(temp);
    delay(1000);              // wait for a second
  #endif
  
}


void check_btn(int button, boolean &state){
  
 _DBG1( Serial.print("Check function. State: ") ); // debug code
 _DBG1( Serial.print(state) ); // debug code
 _DBG1( Serial.print("  Pin: ") ); // debug code
 _DBG1( Serial.println(button) ); // debug code

  if ( !state ){
      //trigger when button is pressed
     _DBG1(   Serial.println("testing press trigger")   ); // debug code
      if( digitalRead(button) == LOW){
         state = true;
         //keyboard.press("a"); //press the a button
         Keyboard.press('n')
        _DBG1(   Serial.print("input ")   ); // debug code
        _DBG1(   Serial.print(button)   ); // debug code
        _DBG1(   Serial.println(" pressed")   ); // debug code
         delay(DEBOUNCE); // debouce input in ms
      }
  }else{
      //trigger when button is released
     _DBG1(   Serial.println("testing release trigger")   ); // debug code
      if( digitalRead(button) == HIGH){
         state = false;
         //keyboard.release("a"); //release the a button
        _DBG1(   Serial.print("input ")   ); // debug code
        _DBG1(   Serial.print(button)   ); // debug code
        _DBG1(   Serial.println(" released")   ); // debug code
         delay(DEBOUNCE); // debouce input in ms
      }
  }
  _DBG1(   delay(1000)   ); //debug only
}
void battery_check(int pin){
  _DBG2(   Serial.println("in batterycheck")   );
   int bat_level=750;
   int current_level = analogRead(battery_pin);
  _DBG2(   Serial.print("current battery = ")   );
  _DBG2(   Serial.println(current_level)   );
   if( current_level < bat_level ){
         digitalWrite(pin, HIGH);
         delay(500);
         set_sleep_mode(SLEEP_MODE_PWR_DOWN);
         sleep_enable();
         sleep_cpu();
         sleep_mode();            // here the device is actually put to sleep!!
        
   }  
 }
 
 void build_mask(int button){
   if (digitalRead(button))
     temp = temp + "0";
   else
     temp = temp + "1";
 }
