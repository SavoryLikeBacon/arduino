
//a#define DEBUG1  //show button logic messages
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
#define NUMBER_OF_BUTTONS 12
#define DIGITAL_ANALOG_THRESHOLD 500
#include <avr/sleep.h>
// the setup function runs once when you press reset or power the board

typedef struct button_type{
   int pin;
   boolean state;
   int key;
} button_struct;
button_struct button[NUMBER_OF_BUTTONS];
int red_led = 15;
 
//debug mask
 String temp = "";
  
  //supervisory inputs
int battery_pin = 2; // analog input for battery
  
  //alert outputs
int low_voltage = 14; 
int please_shutdown = 15; 


void setup() {
  
  button[0].pin = 6; // Select pin
  button[1].pin = 7; //  Start pin
  button[2].pin = 9; //  A pin
  button[3].pin = 8; //  B pin
  button[4].pin = 3; //  Up pin
  button[5].pin = 4; //  Down pin
  button[6].pin = 2; //  Left pin
  button[7].pin = 5; //  Right pin
  
  button[8].pin = 10; //  right shoulder 1
  button[9].pin = 16; //  right shoulder 2

  

  button[0].state = false;
  button[1].state = false;
  button[2].state = false;
  button[3].state = false;
  button[4].state = false;
  button[5].state = false;
  button[6].state = false;
  button[7].state = false;
  
  button[8].state = false;
  button[9].state = false;



  button[0].key = KEY_RIGHT_SHIFT; // select key
  button[1].key = KEY_RETURN; // start key
  button[2].key = 'z'; // a key
  button[3].key = 'x'; // s key
  button[4].key = 218; // up key
  button[5].key = 217; // down key
  button[6].key = 216; // left key
  button[7].key = 215; // right key
  
  button[8].key = 'L'; // 
  button[9].key = 's'; // 

  button[10].pin = 1; //  right shoulder 1. Analog input 1
  button[11].pin = 2; //  right shoulder 2. Analog inuput 2
  button[10].state = false;
  button[11].state = false;
  button[10].key = 'R'; // 
  button[11].key = 'a'; // 

  
  
  Keyboard.begin();
  Serial.begin(9600);
  // initialize digital pin 13 as an output.
  for (int i = 0; i < NUMBER_OF_BUTTONS-2; i ++){
      pinMode(button[i].pin, INPUT);
      digitalWrite(button[i].pin, HIGH);       // turn on pullup resistors
  }
  digitalWrite(A1, HIGH); //set pullups for analog inputs
  digitalWrite(A2, HIGH);
  
  pinMode(red_led, OUTPUT);
  digitalWrite(red_led, HIGH);
  
  //Keyboard.begin();
}

// the loop function runs over and over again forever
void loop() {
  //battery_check(low_voltage);
  
  for (int i = 0; i < NUMBER_OF_BUTTONS; i ++){
     check_btn(i);
  }
  
  special_char();
  
  #ifdef DEBUG3
    temp = "";
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
     build_mask(button[i].pin);
    }  
    Serial.println("button key : SSABUDLRLlRr");
    Serial.print("button mask: "); 
    Serial.println(temp);
    Serial.println("");
    delay(100);              // wait for a second
  #endif
  
  _DBG1(   delay(1000)   );              // wait for a second
}

void special_char(){
  //this is the section that will compare the boolean flags and trigger special characters
  // such as the ESC, F4, or the trigger to trigger the pi to shut down from battery or request
   
   
  if ((button[8].state == true) && (button[9].state == true) && (button[10].state == true) && (button[11].state == true)){
      //special command 1
      //issue escape to return to main menu
      Keyboard.write(KEY_ESC);
      Serial.println("escape key");
      Keyboard.releaseAll();
      delay(1000);
      
  }
  
  if ((button[8].state == true) && (button[0].state == true) && (button[10].state == true) && (button[1].state == true)){
      //special command 2
      // issue F4 to return to the terminal
     
      Keyboard.write(KEY_ESC);
      Serial.println("escape key");
      Keyboard.releaseAll();
      delay(5000);
      
      Keyboard.write(KEY_F4);
      Serial.println("F4 key");
      Keyboard.releaseAll();
      delay(5000);
      Keyboard.write(KEY_RETURN);
      delay(200);
      Keyboard.write(KEY_RETURN);
  }

  if ((button[8].state == true) && (button[3].state == true) && (button[10].state == true) && (button[3].state == true)){
      //special command 3
      // issue the shutdown command and toggle the red_led
      Keyboard.write(KEY_ESC);
      Serial.println("escape key");
      Keyboard.releaseAll();
      
      for (int i=0; i<5; i++){
        digitalWrite(red_led, LOW);
        delay(500);
        digitalWrite(red_led, HIGH);
        delay(500);
      }
      
      Keyboard.write(KEY_F4);
      Serial.println("F4 key");
      Keyboard.releaseAll();
      for (int i=0; i<5; i++){
        digitalWrite(red_led, LOW);
        delay(500);
        digitalWrite(red_led, HIGH);
        delay(500);
      }
      Keyboard.write(KEY_RETURN);
      delay(2000);
           
      
      //Keyboard.press(KEY_LEFT_CTRL);
      //delay(50);
      //Keyboard.press('z');
      //delay(200);
      //Keyboard.write(KEY_RETURN);
      //delay(200);
      Keyboard.write('s');
      Keyboard.write('u');
      Keyboard.write('d');
      Keyboard.write('o');
      Keyboard.write(' ');
      Keyboard.write('p');
      Keyboard.write('o');
      Keyboard.write('w');
      Keyboard.write('e');
      Keyboard.write('r');
      Keyboard.write('o');
      Keyboard.write('f');
      Keyboard.write('f');
      Keyboard.write(KEY_RETURN);
      digitalWrite(red_led, LOW);
      delay(500);
      digitalWrite(red_led, HIGH);
      delay(10000);
      digitalWrite(red_led, HIGH);
      
       set_sleep_mode(SLEEP_MODE_PWR_DOWN);
       sleep_enable();
       sleep_cpu();
       sleep_mode();
}
  
}


void check_btn(int index){

  if ( !button[index].state ){
      //trigger when button is pressed
      if( pseudo_digital_read(index) == LOW){
         button[index].state = true;
         //keyboard.press("a"); //press the a button
         Keyboard.press(button[index].key);
         delay(DEBOUNCE); // debouce input in ms
      }
  }else{
      //trigger when button is released
       if( pseudo_digital_read(index) == HIGH){
         button[index].state = false;
         Keyboard.release(button[index].key); //release the a button
         delay(DEBOUNCE); // debouce input in ms
      }
  }
}

boolean pseudo_digital_read(int index){
   //indexs between 0 and 9 are digital inputs
   //indexes between 10 and 11 are analog inputs being used as digital 
   boolean temp_state = HIGH;
   if ( (index >= 0 ) && ( index <= 9 ) )
      temp_state = digitalRead(button[index].pin);
   else{
     if ( analogRead(button[index].pin) < DIGITAL_ANALOG_THRESHOLD )
          temp_state = LOW;
   }
  
   return temp_state;
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
