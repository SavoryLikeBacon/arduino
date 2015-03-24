
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
//higher level debug code. show the mask with the input states
#ifdef DEBUG3
  #define _DBG3(x) x
#else
  #define _DBG3(x)
#endif

#define DEBOUNCE 20
#include <avr/sleep.h>
// the setup function runs once when you press reset or power the board

typedef struct button_type{
   int pin;
   boolean state;
   int key;
} button_struct;
button_struct button[8];
 
//debug mask
 String temp = "";
  
  //supervisory inputs
int battery_pin = 2; // analog input for battery
  
  //alert outputs
int low_voltage = 10; 

void setup() {
  
  button[0].pin = 6; // Select pin
  button[1].pin = 7; //  Start pin
  button[2].pin = 9; //  A pin
  button[3].pin = 8; //  B pin
  button[4].pin = 3; //  Up pin
  button[5].pin = 4; //  Down pin
  button[6].pin = 2; //  Left pin
  button[7].pin = 5; //  Right pin
  
//  button[0].pin = 2; // Select pin
//  button[1].pin = 3; //  Start pin
//  button[2].pin = 4; //  A pin
//  button[3].pin = 5; //  B pin
//  button[4].pin = 6; //  Up pin
//  button[5].pin = 7; //  Down pin
//  button[6].pin = 8; //  Left pin
//  button[7].pin = 9; //  Right pin
 
  button[0].state = false;
  button[1].state = false;
  button[2].state = false;
  button[3].state = false;
  button[4].state = false;
  button[5].state = false;
  button[6].state = false;
  button[7].state = false;

  button[0].key = KEY_RIGHT_SHIFT; // select key
  button[1].key = KEY_RETURN; // start key
  button[2].key = 'z'; // a key
  button[3].key = 'x'; // s key
  button[4].key = 218; // up key
  button[5].key = 217; // down key
  button[6].key = 216; // left key
  button[7].key = 215; // right key
  
  Keyboard.begin();
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  for (int i = 0; i < 8; i ++){
      pinMode(button[i].pin, INPUT);
      digitalWrite(button[i].pin, HIGH);       // turn on pullup resistors
  }
  //Keyboard.begin();
}

// the loop function runs over and over again forever
void loop() {
  //battery_check(low_voltage);
  
  for (int i = 0; i < 8; i ++){
     check_btn(i);
  }
  
  #ifdef DEBUG3
    temp = "";
    for (int i = 0; i < 8; i ++){
     build_mask(button[i].pin);
    }  
    Serial.println("button key : SSABUDLR");
    Serial.print("button mask: "); 
    Serial.println(temp);
    delay(1000);              // wait for a second
  #endif
  
  _DBG1(   delay(1000)   );              // wait for a second
}


void check_btn(int pin){

 _DBG1(   Serial.print("Check function. State: ") ); // debug code
 _DBG1(   Serial.print(button[pin].state) ); // debug code
 _DBG1(   Serial.print("  Pin: ") ); // debug code
 _DBG1(   Serial.println(button[pin].pin) ); // debug code

  if ( !button[pin].state ){
      //trigger when button is pressed
     _DBG1(   Serial.println("testing press trigger")   ); // debug code
      if( digitalRead(button[pin].pin) == LOW){
         button[pin].state = true;
         //keyboard.press("a"); //press the a button
         Keyboard.press(button[pin].key);
        _DBG1(   Serial.print("input ")   ); // debug code
        _DBG1(   Serial.print(button[pin].pin)   ); // debug code
        _DBG1(   Serial.println(" pressed")   ); // debug code
         delay(DEBOUNCE); // debouce input in ms
      }
  }else{
      //trigger when button is released
     _DBG1(   Serial.println("testing release trigger")   ); // debug code
      if( digitalRead(button[pin].pin) == HIGH){
         button[pin].state = false;
         Keyboard.release(button[pin].key); //release the a button
        _DBG1(   Serial.print("input ")   ); // debug code
        _DBG1(   Serial.print(button[pin].pin)   ); // debug code
        _DBG1(   Serial.println(" released")   ); // debug code
         delay(DEBOUNCE); // debouce input in ms
      }
  }
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