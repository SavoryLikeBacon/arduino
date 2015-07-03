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
  lcd.init(); // initialize the lcd 
  //lcd.begin(); // initialize the lcd 
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


  //Serial.print("sub menu state ");
  //Serial.println(submain1_menu_state);
//    long second = millis();
//    Serial.print("time is ");
//    Serial.print(second - first);
//    Serial.println(" milliseconds");
//    delay(5000);

}

void button_check(){
  if (digitalRead(encoder_switch_pin) == HIGH){
    //Serial.println("before select_event function");
    select_event(); 
    
    while(digitalRead(encoder_switch_pin) == HIGH){
        delay(1);
    }
    
  }
}


void write_number(){
  lcd.setCursor ( 13, 1 );
  if ((rotary_counter >= 0) && (rotary_counter <= 9)){
    lcd.print("  ");
    lcd.print(rotary_counter);
  }
  if ((rotary_counter >= 10) && (rotary_counter <= 99)){
    lcd.print(" ");
    lcd.print(rotary_counter);
  }
  if (rotary_counter >= 100){
    lcd.print(rotary_counter);
  }
  
  //Serial.println(rotary_counter); 
}

void handle_encoder(){
    
    if (position_delta > 0)
      up_event();
    if (position_delta < 0)      
      down_event();
    
    if (rotary_counter > 255)
      rotary_counter= 255;
    if (rotary_counter < 0)
      rotary_counter= 0;
        
      
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
  newPosition = (int )(myEnc.read()/4);


    position_delta =  (newPosition - oldPosition);
    rotary_counter += position_delta;
    if (position_delta > 0)
      up_event();
    if (position_delta < 0)
      down_event();
    position_delta=0;
    oldPosition = newPosition;
 
  
//  Serial.print("new: ");
//  Serial.print(newPosition);
//  Serial.print("      old: ");
//  Serial.print(oldPosition);
//  Serial.print("      delta: ");
//  Serial.print(position_delta);
  //Serial.print("      counter: ");
  //Serial.println(rotary_counter);
}

void lcd_counter_update(){
//this function shows 0 through 255 when the user is going to select a numeric boolean selector  
  // counter_offset = oldPosition - current_intensity;
  
  
}

void lcd_yesno_update(){
//this function show the yes or no options when the user is going to select a boolean selector
  lcd.setCursor ( 7 , 1 );
  lcd.print("Save? ");
  if (oldPosition & 1){
    lcd.print("Yes");
    current_yesno = true;
    Serial.println("Yes");
  }else{
    lcd.print(" No");
    current_yesno = false;
    Serial.println(" No");
  }
}


void up_event(){
  
//  if (rotary_counter >= 255){
//     rotary_counter = 255;
//  }else{
//     rotary_counter++;
//  }

if (!(numeric_flag || yes_no_flag)){
//do not change sub menu when the above flags are set
    if (menu_flag){
      main_menu_state++;
      if (main_menu_state== (main_menu_size+1) )
         main_menu_state = 1;
    }
  
    if (submenu1_flag){
      submain1_menu_state++;
      if (submain1_menu_state== (submenu1_size+1) )
         submain1_menu_state = 1;
    }  
  
    if (submenu2_flag){
      submain2_menu_state++;
      if (submain2_menu_state== (submenu2_size+1) )
         submain2_menu_state = 1;
    } 
 
    if (submenu3_flag){
      submain3_menu_state++;
      if (submain3_menu_state== (submenu3_size+1) )
         submain3_menu_state = 1;
    }  
  }
  Serial.print("up ");
  Serial.print(millis());
  Serial.print("    ");
  Serial.println(rotary_counter);
}

void down_event(){
//    if (rotary_counter <= 0){
//     rotary_counter = 0;
//  }else{
//     rotary_counter--;
//  }

  
  if (!(numeric_flag || yes_no_flag)){
   //stop changing the sub menu when the y/n flag is set or if the numeric flag is set

  //increment the main menu
    if (menu_flag){
      main_menu_state--;
      if (main_menu_state==0)
         main_menu_state = main_menu_size;
    }  
  
    if (submenu1_flag){
      submain1_menu_state--;
      if (submain1_menu_state==0)
         submain1_menu_state = submenu1_size;
    }  
  
    if (submenu2_flag){
      submain2_menu_state--;
      if (submain2_menu_state==0)
         submain2_menu_state = submenu2_size;
    }  

    if (submenu3_flag){
      submain3_menu_state--;
      if (submain3_menu_state==0)
         submain3_menu_state = submenu3_size;
    }  
  }
    
  Serial.print("down ");
  Serial.print(millis());
  Serial.print("    ");
  Serial.println(rotary_counter);

}

void select_event(){
  
  if (menu_flag){
//    #define st_intensity 1
//    #define st_color 2
//    #define st_program 3
	Serial.println("Handling main menu click");
     switch (main_menu_state){
       case st_intensity:
//       menu_flag =  false;
         numeric_flag = true; // turn on numeric display for user to select
  	 break;
       case st_color:
         menu_flag =  false;
         submenu1_flag = true;
	 break;	
       case st_program:
         menu_flag =  false;
         submenu2_flag = true;    
	 break;
       
       default:   
         delay(1);    
      }      
    }else{
  
      if (submenu1_flag){  
//    #define st_color_red 1
//    #define st_color_green 2
//    #define st_color_blue 3
//    #define st_color_back 4
      // set current color
      Serial.println("Handling submenu 1 menu click");
      switch (submain1_menu_state){
        case st_color_red:
           numeric_flag = true; // turn on numeric display for user to select
		   break;
        case st_color_green:
           numeric_flag = true; // turn on numeric display for user to select
	       break;	
        case st_color_blue:
           numeric_flag = true; // turn on numeric display for user to select
	       break;
        case st_color_back:
           menu_flag =  true;
           submenu1_flag = false;
           main_menu_state = st_color;
           break;          
        default:   
           delay(1);    
       }    
    
    }else{
  
      if (submenu2_flag){    


        
//        #define st_dflt_intensity 1
//        #define st_dflt_color 2
//        #define st_save 3
//        #define st_restore 4
//        #define st_program_back 5
        
        // set default current color
        //submenu2 is a child of submenu3
        Serial.println("Handling submenu 2 menu click");
        switch (submain2_menu_state){
          case st_dflt_intensity:
             numeric_flag = true; // turn on numeric display for user to select
             break;
          case st_dflt_color:
             numeric_flag = true; // turn on numeric display for user to select
	     break;	
          case st_save:
             numeric_flag = true; // turn on numeric display for user to select
	     break;
          case st_restore:
             numeric_flag = true; // turn on numeric display for user to select
	     break;
          case st_program_back:
             Serial.print("submenu2 back:  ");
             Serial.print(submain2_menu_state);
             menu_flag =  true;
             submenu2_flag = false;
             submain2_menu_state = st_program;          
             break;          
          default:   
             Serial.print("submenu2 back in delay   :");
             Serial.print(submain2_menu_state);
 
             delay(1);    
        } 


       }else{
    
        if (submenu3_flag){

        //#define st_dflt_red 1
        //#define st_dflt_green 2
        //#define st_dflt_blue 3
        //#define st_dflt_back 4
          
            Serial.println("Handling submenu 3 menu click");
            switch (submain3_menu_state){
              case st_dflt_red:
                  numeric_flag = true; // turn on numeric display for user to select
                  break;
              case st_dflt_green:
                  numeric_flag = true; // turn on numeric display for user to select
                  break;	
              case st_dflt_blue:
                  numeric_flag = true; // turn on numeric display for user to select
                  break;
              case st_dflt_back:
                  submenu2_flag =  true;
                  submenu3_flag = false;
                  main_menu_state = st_dflt_color;
                  break;          
              default:   
                  delay(1);    
            }
	
        }
      
      }
 
    }
  
  }
 
  //Serial.print("select  ");
  //Serial.println(millis());
//  button_service_waiting = false;
}

void back_event(){
  Serial.println("back");
 // button_service_waiting = false;
}


void print_submenu1(){
 //this function prints the top part of each menu  
  String temp_buffer;
  //submain_menu_state %= 3;
  switch (submain1_menu_state){
      case st_color_red:
	temp_buffer="  Red        ";
	break;
	
      case st_color_green:
	temp_buffer="  Green      ";
	break;
	
      case st_color_blue:
	temp_buffer="  Blue       ";
	break;

      case st_color_back:
	temp_buffer="  back       ";
	break;

      default:
        temp_buffer="Dflt SubMenu1   "; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Color           ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void print_submenu2(){
 //this function prints the top part of each menu  
  String temp_buffer;
  //submain_menu_state %= 3;
  switch (submain2_menu_state){
      case st_dflt_intensity:
	temp_buffer="  Intensity  ";
	break;
	
      case st_dflt_color:
	temp_buffer="  Color      ";
	break;

      case st_save:
	temp_buffer="  Save       ";
	break;
	
      case st_restore:
	temp_buffer="  Restore    ";
	break;
      
      case st_program_back:
	temp_buffer="  back       ";
	break;

      default:
         temp_buffer="Dflt SubMenu2  "; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Program         ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void print_submenu3(){
 //this function prints the top part of each menu  
  String temp_buffer;
  //submain_menu_state %= 3;
  switch (submain3_menu_state){
      case st_dflt_red:
	temp_buffer="  Red     ";
	break;
	
      case st_dflt_green:
	temp_buffer="  Green   ";
	break;
	
      case st_dflt_blue:
	temp_buffer="  Blue    ";
	break;
	     
      case st_dflt_back:
	temp_buffer="  back    ";
	break;
	
      default:
         temp_buffer="Dflt SubMenu3"; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Default Color   ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void print_top_menu(){
 //this function prints the top part of each menu  
  String temp_buffer;
  switch (main_menu_state){
//      case st_main:
//        temp_buffer="Main Menu       ";
//        break;
      
      case st_intensity:
     	temp_buffer="  Intensity  ";
	break;
	
      case st_color:
	temp_buffer="  Color      ";
	break;
	
      case st_program:
	temp_buffer="  Program    ";
	break;
	
      default:
         temp_buffer="Default Menu"; 
  }
    lcd.setCursor ( 0, 0 );
    lcd.print("Main Menu       ");
    lcd.setCursor ( 0, 1 );
    lcd.print(temp_buffer);
    //Serial.println(temp_buffer);
}

void show_number_select(){
 //this function displays the number select and returns with the number between 0 and 255 
  
}

