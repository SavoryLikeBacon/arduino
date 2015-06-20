
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
#include <Encoder.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
long oldPosition =  0;
int position_delta = 0;
long temp_counter = 0;

//state numbers
#define st_main 1
#define st_intensity 2
#define st_color 3
#define st_color_red 4
#define st_color_green 5
#define st_color_blue 6
#define st_program 7
#define st_dflt_intensity 8
#define st_dflt_color 9
#define st_dflt_red 10
#define st_dflt_green 11
#define st_dflt_blue 12
#define st_save 13
#define st_restore 14


//pin  for the hardware are listed below
const int red_led_pin = 9;
const int green_led_pin = 5;
const int blue_led_pin = 6;
const int encoder_A_pin = 0;
const int encoder_B_pin = 0;
const int encoder_switch_pin = 4;



int menu_state = 6; //this will hold the current state
volatile int rotary_counter = 0;
boolean numeric_flag = false;
boolean yes_no_flag = false;
boolean menu_flag = true;
volatile int button_service_waiting = 0;
String inputString = "";


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(encoder_A_pin, encoder_B_pin);
//   avoid using pins with LEDs attached


void setup() {
  // put your setup code here, to run once:
  prep_IO(); // prepare the inputs and outputs
  Timer1.initialize(1000000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
  lcd.init(); // initialize the lcd 
  lcd.backlight();
  //pinMode(13, OUTPUT);
  //inputString.reserve(200);
  Serial.begin(9600);
     
}


//prepare the inputs and outputs
void prep_IO(){
  pinMode(red_led_pin, OUTPUT); // PWM ready
  pinMode(green_led_pin, OUTPUT); // PWM ready
  pinMode(blue_led_pin, OUTPUT); // PWM ready
  //encoder switch inputs are declared in the library
  pinMode(encoder_switch_pin, INPUT); // signal is highgoing to no need to enable pullup
}


void loop() {
  // put your main code here, to run repeatedly:
  
  delay(2000);
  Serial.print("encoder counter: ");
  Serial.println(rotary_counter);
  
}

//void button_check_loop() {
//  //this will be removed when the encoder is connected
//  while (Serial.available()) {
//    // get the new byte:
//    char inChar = (char)Serial.read(); 
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag
//    // so the main loop can do something about it:  
//    if (inChar == 'u')
//      up_event();
//    if (inChar == 'd')      
//      down_event();
//    if (inChar == 's')
//      select_event();
//    if (inChar ==  'b')        
//      back_event();
//  }
//}

void handle_encoder(){

    if (position_delta > 0)
      up_event();
    if (position_delta < 0)      
      down_event();
      
    //read select and back switch
//    if (inChar == 's')
//      select_event();
//    if (inChar ==  'b')        
//      back_event();
}



void timerIsr()
{
    print_top_menu();
 
    get_position();
    lcd.setCursor ( 0, 1 );
    lcd.print(rotary_counter);
    handle_encoder();
    lcd.setCursor ( 1, 1 );
    lcd.print(position_delta);
//    if (numeric_flag == true)
//       lcd_counter_update();
//    if (yes_no_flag == true)
//       lcd_yesno_update();
    
    //digitalWrite( 13, digitalRead( 13 ) ^ 1 );
    
}

void get_position(){
  long rotary_encoder = myEnc.read()/4;
  position_delta = rotary_encoder - oldPosition;
}

void lcd_counter_update(){
//this function shows 0 through 255 when the user is going to select a numeric boolean selector  
  // counter_offset = oldPosition - current_intensity;
  
  
}

void lcd_yesno_update(){
//this function show the yes or no options when the user is going to select a boolean selector
  if (oldPosition & 1){
    Serial.println("Yes");
  }else{
    Serial.println("No");
  }
}



void up_event(){
  if (rotary_counter >= 255){
     rotary_counter = 255;
  }else{
     rotary_counter++;
  }
  //Serial.print("up ");
  //Serial.println(rotary_counter);
}

void down_event(){
    if (rotary_counter <= 0){
     rotary_counter = 0;
  }else{
     rotary_counter--;
  }
  //Serial.print("down ");
  //Serial.println(rotary_counter);
  
}

void select_event(){
  Serial.println("select");
//  button_service_waiting = false;
}

void back_event(){
  Serial.println("back");
 // button_service_waiting = false;
}


void print_top_menu(){
 //this function prints the top part of each menu  
  String temp_buffer;
  switch (menu_state){
      case st_main:
        temp_buffer="Main Menu";
        break;
      
      case st_intensity:
     	temp_buffer="Intensity";
	break;
	
      case st_color:
	temp_buffer="Color";
	break;
	
      case st_color_red:
	temp_buffer="Red";
	break;
	
      case st_color_green:
	temp_buffer="Green";
	break;
	
      case st_color_blue:
	temp_buffer="Blue";
	break;
	
      case st_program:
	temp_buffer="Program";
	break;
	
      case st_dflt_intensity:
	temp_buffer="Default Inten";
	break;
	
      case st_dflt_color:
	temp_buffer="Default Color";
	break;
	
      case st_dflt_red:
	temp_buffer="Default Red";
	break;
	
      case st_dflt_green:
	temp_buffer="Default Green";
	break;
	
      case st_dflt_blue:
	temp_buffer="Default Blue";
	break;
	
      case st_save:
	temp_buffer="Save";
	break;
	
      case st_restore:
	temp_buffer="Restore";
	break;
        
      default:
         temp_buffer="Default Menu"; 
       
  }
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    Serial.println(temp_buffer);
}

void show_number_select(){
 //this function displays the number select and returns with the number between 0 and 255 
  
}
