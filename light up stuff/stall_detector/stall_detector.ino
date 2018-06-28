#include <TimerOne.h>

//Detect is there is stall in the filiment be measuring the feed of the filiment (encoder) 
//and reading the speed of the stepper. IF these get out of sync, turn on the relay 
//that will stop the system.

//All timers assumg a system clock of 16MHz
int signal_delay = 100; //Milliseconds
double relay_delay  = 15000; //Milliseconds
volatile int temp_global = 0;
volatile int time_delta;
volatile bool armed = false;
bool test_mode_enable = false;
bool one_shot = false;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~ CONFIG ~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~ ENCODER ~~~~~~~~~~~~~~//
float encoder_threshold = 20; //Hz
int encoder_accum = 0; //Accumulator for counts
volatile float encoder_speed; //Current values of speed
volatile float new_encoder_speed = 0;
volatile float cur_encoder_speed = 0;
volatile float encoder_setpoint;
volatile bool encoder_active = false;

//~~~~~~~~~~~~~~ STEPPER ~~~~~~~~~~~~~~//
float step_threshold = 200; //Hz
int step_accum = 0; //Accumulator for counts
volatile float step_speed; //Current values of speed
volatile float new_step_speed = 0;
volatile float cur_step_speed = 0;
volatile float step_setpoint;
volatile bool step_active = false;

//~~~~~~~~~~~~~~ TIMER ~~~~~~~~~~~~~~//
int timer_freq = 20; //Hz
float timer_period; //Global variable placeholder for the period in uS
float filter = 0.5; //Used in a digital low pass filter
//Equation: ( NewFq / filter ) + (OldF * (filter-1) / filter)) = CurrentFq

int timeout_start;
int timeout_cur;
bool toggle;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~ PIN ASSIGNMENTS ~~~~~~~~~~~~~~//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int encoder_pin = 3; //This pin cant change. Pin 3 is ties to interrupt 0
int step_pin = 2; //This pin cant change. Pin 2 is ties to interrupt 1
int test_mode = 4; //Test mode enabled by jumper

int encoder_setpoint_pin = A3; 
int step_setpoint_pin = A2;
int time_delta_pin = A1;

int relay_out = 9; //PWM will be used to lower power to relay after first second (maybe)
int encoder_led = 8;// show if the encoder value has passed the threshold
int step_led = 7;// show if the stepper value has passed the threshold

int ui_led = 10;  //Outputs PWM to show a dimming/brightening LED to show breathing.
                  //Slower duty cycle if the test jumper is in place                 
int test_pwm = 6;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void setup() {  
  Serial.begin(115200);

  //Assign Pins
  pinMode(encoder_pin, INPUT_PULLUP); //Filiment encoder input. Interrupt 0
  pinMode(step_pin, INPUT_PULLUP); //Filiment step input. Interrupt 1
  pinMode(test_mode, INPUT_PULLUP); //Test mode enable. Relay does not move. Feedback LEDs allow for tuning

  pinMode(encoder_led, OUTPUT); 
  pinMode(step_led, OUTPUT); 
  pinMode(ui_led, OUTPUT); 
  pinMode(relay_out, OUTPUT);
  
  pinMode(test_pwm, OUTPUT);
  analogWrite(test_pwm, 125);

  //Assign Interupts
  attachInterrupt(digitalPinToInterrupt(encoder_pin), encoder_input_callback, FALLING);
  attachInterrupt(digitalPinToInterrupt(step_pin),step_input_callback, FALLING);

  //Make Timer

  
  timer_period = 1000000 / float(timer_freq); // microseconds 
  Timer1.initialize(timer_period);
  Timer1.attachInterrupt(calculate_freq);

  armed = true;

}


void loop() {
    test_mode_enable = !digitalRead(test_mode);
   
    

    if(!test_mode_enable){
        if(encoder_active != step_active){    
           //no motion, keep relay off
           if(one_shot == false){
              timeout_start = millis();              
              one_shot = true;
           }
           
           timeout_cur = millis();
         
           if ((timeout_cur - timeout_start) > time_delta){
              digitalWrite(relay_out, true);
              delay(15000);
              digitalWrite(relay_out, false);
              one_shot = false;
           }

        }else{
            one_shot = false;          
         }

      
    }
  

   

    delay(100);
}


void stream(){
  
  Serial.print(millis());
  Serial.print("\tESpd:\t");
  Serial.print(cur_encoder_speed);
  Serial.print("\tESet:\t");
  Serial.print(encoder_setpoint);
  Serial.print("\tSSpd:\t");
  Serial.print(cur_step_speed);
  Serial.print("\tSSet:\t");
  Serial.print(step_setpoint);
  Serial.print("\tWin:\t");
  Serial.print(time_delta);
  
  if(test_mode_enable)
    Serial.print("\tTEST");
  else{
    if(armed)
      Serial.print("\tARMED");
    else
      Serial.print("\tDISARMED");
  }

  if(digitalRead(encoder_led))
    Serial.print("\t1");
  else
    Serial.print("\t0");
    
  if(digitalRead(step_led))
    Serial.print("1");
  else
    Serial.print("0");


  if(digitalRead(relay_out))
    Serial.println("1");
  else
    Serial.println("0");
}


void calculate_freq(){
    int local_encoder = encoder_accum;
    encoder_accum = 0;
    int local_step = step_accum;
    step_accum = 0;
    
    if(local_encoder > 0)
      new_encoder_speed = timer_period / local_encoder;
    else
      new_encoder_speed = 0;

    if(local_step > 0)
      new_step_speed = timer_period / local_step;
    else
      new_step_speed = 0;

    cur_encoder_speed = (new_encoder_speed * (1-filter)) + cur_encoder_speed * filter;
    cur_step_speed = (new_step_speed * (1-filter)) + cur_step_speed * filter;

    if (cur_encoder_speed >= encoder_setpoint)
        encoder_active = true;
    else
        encoder_active = false;

    if (cur_step_speed >= step_setpoint)
        step_active = true;
    else
        step_active = false;


    if(encoder_active)
        digitalWrite(encoder_led, true);
    else
        digitalWrite(encoder_led, false);

    if(step_active)
        digitalWrite(step_led, true);
    else
        digitalWrite(step_led, false);


    time_delta = analogRead(time_delta_pin)*10;
    encoder_setpoint = analogRead(encoder_setpoint_pin)*10;
    step_setpoint = analogRead(step_setpoint_pin)*5;

    if(toggle)
       stream();
    toggle = !toggle;
}

void encoder_input_callback(){
    encoder_accum++;
}

void step_input_callback(){
    step_accum++;
}



