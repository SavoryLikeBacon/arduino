#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <TimerOne.h>
#include <Encoder.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
long oldPosition =  0;
long newPosition = .5;
int position_delta = 0;
long temp_counter = 0;

//state numbers for main menu

#define main_menu_size 3
#define st_intensity 1
#define st_color 2
#define st_program 3


//state numbers for sub menu 1
#define submenu1_size 4
#define st_color_red 1
#define st_color_green 2
#define st_color_blue 3
#define st_color_back 4

//state numbers for sub menu 2
#define submenu2_size 5
#define st_dflt_intensity 1
#define st_dflt_color 2
#define st_save 3
#define st_restore 4
#define st_program_back 5

//state numbers for sub menu 3
#define submenu3_size 4
#define st_dflt_red 1
#define st_dflt_green 2
#define st_dflt_blue 3
#define st_dflt_back 4



//pin  for the hardware are listed below
const int red_led_pin = 9;
const int green_led_pin = 5;
const int blue_led_pin = 6;
const int encoder_A_pin = 0;
const int encoder_B_pin = 1;
const int encoder_switch_pin = 4;



int menu_state = 1; //this will hold the current state
volatile long rotary_counter = 0;
boolean numeric_flag = false;
boolean yes_no_flag = false;
boolean menu_flag = true;
boolean submenu1_flag = false;
boolean submenu2_flag = false;
boolean submenu3_flag = false;

int main_menu_state = 1;
int submain1_menu_state = 1;
int submain2_menu_state = 1;
int submain3_menu_state = 1;
boolean current_yesno = false;
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
 // Timer1.initialize(1000000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  //Timer1.attachInterrupt( timerIsr ); // attach the service routine here
  //lcd.init(); // initialize the lcd 
  lcd.begin(); // initialize the lcd 
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

  
  delay(100);
//  long first = millis();
  
  get_position();
  handle_encoder();
    
  button_check();
  
  if(menu_flag)
     print_top_menu();
    
  if(submenu1_flag)
     print_submenu1();

  if(submenu2_flag)
     print_submenu2();

  if(submenu3_flag)
     print_submenu3();
 
  if (numeric_flag)
    write_number();
  
  if (yes_no_flag)
    lcd_yesno_update();

}





