/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */


// the setup function runs once when you press reset or power the board
void setup() {
  
  //button inputs and booleans
  int Select_btn_pin = 2;
  int Start_btn_pin = 3;
  int A_btn_pin = 4;
  int B_btn_pin = 5;
  int Up_btn_pin = 6;
  int Down_btn_pin = 7;
  int Left_btn_pin = 8;
  int Right_btn_pin = 9;
  
  boolean Select_btn_bool = false;
  boolean Start_btn_bool = false;
  boolean A_btn_bool = false;
  boolean B_btn_bool = false;
  boolean Up_btn_bool = false;
  boolean Down_btn_bool = false;
  boolean Left_btn_bool = false;
  boolean Right_btn_bool = false;
  
  
  
  //supervisory inputs
  int battery_vol = 2 // analog input for battery
  
  //alert outputs
  int low_voltage = 10; 
  
  
  // initialize digital pin 13 as an output.
  pinMode(Select_btn_pin, INPUT);
  pinMode(Start_btn_pin, INPUT);
  pinMode(A_btn_pin, INPUT);
  pinMode(B_btn_pin, INPUT);
  pinMode(Up_btn_pin, INPUT);;
  pinMode(Down_btn_pin, INPUT);
  pinMode(Left_btn_pin, INPUT);
  pinMode(Right_btn_pin, INPUT);
  
  //initialize keybaord
}

// the loop function runs over and over again forever
void loop() {
  battery_check(low_voltage);
  check_btn(Select_btn_pin, Select_btn_bool); //check the select button
  //check_btn(Start_btn_pin, Start_btn_bool); //check the start button
  //check_btn(A_btn_pin, A_btn_bool); //check the A button
  //check_btn(B_btn_pin, B_btn_bool); //check the B button
  //check_btn(Up_btn_pin, Up_btn_bool); //check the up button
  //check_btn(Down_btn_pin, Down_btn_bool); //check the down button
  //check_btn(Left_btn_pin, Left_btn_bool); //check the left button
  //check_btn(Right_btn_pin, Right_btn_bool); //check the right button
  
  
  
  
  
 // digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(1000);              // wait for a second
  //digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  //delay(1000);              // wait for a second
}


void check_btn(int button, boolean state){
  // if button is not pressed
  if ( !state ){
      if( digitalRead(button) == LOW){
         state = true;
         //keyboard.press("a"); //press the a button
      }
  }else{
      if( digitalRead(button) == HIGH){
         state = false;
         //keyboard.release("a"); //release the a button
      }
  }
}

void battery_check(int pin){
   //Serial.println("in batterycheck");
   int bat_level=750;
   int current_level = analogRead(battery_pin);
  // Serial.print("current battery = ");
   //Serial.println(current_level);
   if( current_level < bat_level ){
         digitalWrite(pin, HIGH);
         delay(500);
         set_sleep_mode(SLEEP_MODE_PWR_DOWN);
         sleep_enable();
         sleep_cpu();
         sleep_mode();            // here the device is actually put to sleep!!
        
      }  
 }
  

