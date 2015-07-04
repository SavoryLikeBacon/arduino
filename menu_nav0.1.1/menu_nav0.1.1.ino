#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
//#include <TimerOne.h>
#include <Encoder.h>
#include <EEPROM.h>

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
#define submenu2_size 3
#define st_save 1
#define st_restore 2
#define st_program_back 3
#define st_dflt_intensity 4
#define st_dflt_color 5

//state numbers for sub menu 3
#define submenu3_size 4
#define st_dflt_red 1
#define st_dflt_green 2
#define st_dflt_blue 3
#define st_dflt_back 4

//~~~~~~~~~~~~~~~~~~~~~~~~~`
//EEPROM address and default settings
#define intensity_memory 0
#define red_memory 1
#define green_memory 2
#define blue_memory 3

#define default_intensity 100
#define default_red 100
#define default_green 100
#define default_blue 100

// varibales to hold the values of the RGB and intensity
//The initial restore function will load these with default values
int current_red = 0;
int current_blue = 0;
int current_green = 0;
int current_intensity = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//pin  for the hardware are listed below

//pin for the encoder LEDs
const int red_led_pin = 9;
const int green_led_pin = 5;
const int blue_led_pin = 6;

// data out lines for the three neo pixel strips
const int driver_side_pin = 7;
const int passenger_side_pin = 8;
const int cover_pin = 10;

// encoder pins for the A, B, and the switch
const int encoder_A_pin = 0;
const int encoder_B_pin = 1;
const int encoder_switch_pin = 4;

const int battery_monitor_pin = A3;// this pin has a voltage divider. The top resistor is connected to the power input and is a 10k resistor.
//the bottom resisstor is connected to ground and is a 5k resistor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


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


long a = 0;
long b = 0;
 

//Objects
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
Encoder myEnc(encoder_A_pin, encoder_B_pin);
Adafruit_NeoPixel driver_side_strip = Adafruit_NeoPixel(40, driver_side_pin, NEO_GRB + NEO_KHZ800); // driver side strip
Adafruit_NeoPixel passenger_side_strip = Adafruit_NeoPixel(40, passenger_side_pin, NEO_GRB + NEO_KHZ800); // passenger side strip
Adafruit_NeoPixel cover_strip = Adafruit_NeoPixel(60, cover_pin, NEO_GRB + NEO_KHZ800); // cover strip


void setup() {
  prep_IO(); // prepare the inputs and outputs
  //lcd.init(); // initialize the lcd 
  lcd.begin(); // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  
  driver_side_strip.begin();
  passenger_side_strip.begin();
  cover_strip.begin();
  
  driver_side_strip.show();
  passenger_side_strip.show();
  cover_strip.show();
  
  load_from_memory();
  //print_loaded_memory();  
  //load_defaults();
}

void loop() {
//  delay(5000);
//  print_loaded_memory(); 
//  load_defaults();
//  print_loaded_memory(); 
//  while(1){}
  
  //delay(100);

  a = millis();
  update_button_color();
  get_position();
  handle_encoder();
  //print_loaded_memory();
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

  update_lights();
  b = millis();
  Serial.println(b-a);
  
}





