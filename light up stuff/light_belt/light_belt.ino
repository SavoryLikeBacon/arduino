
#include <Adafruit_NeoPixel.h>
#include <avr/sleep.h>
#define STRIP_PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, STRIP_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.



const int toe_pin = A1;  // toe pressure sensor
const int heel_pin = A0;  // toe pressure sensor
const int battery_pin = A4; //voltage divider for battery
const int ledPin = 13;

const int thresh_toe = 700;
const int thresh_heel = 700;

boolean toe_bool = false;
boolean heel_bool = false;
boolean armed = false;

int toe_value = 0;
int heel_value = 0;

int steps = 0;
double counter = 0;


double brightness[] = {100, 30, 15, 10, 8, 6, 2};


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  //rainbowCycle(0);
  //battery_check();
  colorWipe(strip.Color(8,8,0), 20);
  theaterChase(strip.Color(8, 8, 0), 50);
  colorWipe(0, 0);
  
  //analogReference(EXTERNAL); //connect 3.3V to AREF
      
  delay(500);
  
}

void loop(){  
  
  
  //heel_hit();
  back_and_forth();
  battery_check();
  //toe_hit();
  //fireball_belt();
  
  //heel_hit();

  //toe_hit();  
  
 /* read_sensor();
     if (heel_bool==true){
       heel_hit();
     }
     
     if (toe_bool==true){
       //send_ball( 30, 60, 29, 0, 10); // out pulse
       toe_hit();  
   }
     Serial.println(toe_value);
  */
  
  
  //delay(500);  
  
  //delay(500); 
}

void battery_check(){
   //Serial.println("in batterycheck");
   int bat_level=750;
   int no_battery_connected = 400;
   int current_level = analogRead(battery_pin);
   Serial.print("current battery = ");
   Serial.println(current_level);
   if(current_level > no_battery_connected){
     if( current_level < bat_level ){
        colorWipe(0, 0);  // clear strip
        while(1){
           for(int i=0; i<5; i++){
              digitalWrite(ledPin, HIGH);
              strip.setPixelColor(0,strip.Color(10, 0, 0));
              strip.show();
              delay(500);
              digitalWrite(ledPin, LOW);
              strip.setPixelColor(0,strip.Color(0, 0, 0));
              strip.show();
              delay(500);
           }
           
           set_sleep_mode(SLEEP_MODE_PWR_DOWN);
           sleep_enable();
           sleep_cpu();
           sleep_mode();            // here the device is actually put to sleep!!
          
        }  
     }
   }else{
       Serial.print("Battery Bypass\t");
       Serial.println(current_level);
   }
    
}

void read_sensor(){
  int temp_toe = 0;
  int temp_heel = 0;
  toe_value = analogRead(toe_pin);
  heel_value = analogRead(heel_pin);
  
  // add a threshold for disarming
  if (armed == true){
      temp_toe = thresh_toe + 50;
      temp_heel= thresh_heel + 50;
  }else{
      temp_toe = thresh_toe;
      temp_heel = thresh_heel;
  }
  
  if (toe_value >=temp_toe)
     toe_bool = false; // toe press sensed
  else
     toe_bool = true;
          
  if (heel_value >=temp_heel)
     heel_bool = false; // heel press sensed
  else
     heel_bool = true;    
  heel_bool = false; //no heel hooked up
}

void toe_hit(){
    send_ball( 0, 29, 59, 30, 6); // in pulse
    
    strip.setPixelColor(30,strip.Color(0, 0, 0));
    strip.setPixelColor(29,strip.Color(0, 0, 0));
     strip.show();
    //Serial.print("toe hit | ");
    digitalWrite(ledPin, HIGH);
    armed = true;
    rearm();
}

void heel_hit(){
    send_ball( 30, 60, 29, 0, 6); // out pulse
    //Serial.print("heel hit | ");
    digitalWrite(ledPin, HIGH);
    armed = true;
    rearm();
}

void back_and_forth(){
    send_ball( 30, 60, 29, 0, 30); // out pulse
    //Serial.print("heel hit | ");
    digitalWrite(ledPin, HIGH);
    
    send_ball( 0, 29, 59, 30, 30); // in pulse
    //Serial.print("toe hit | ");
    digitalWrite(ledPin, LOW);   
}
  

void rearm(){
  boolean temp = true;
  //Serial.println("hold for rearm");
  while(temp){
     read_sensor();
     if( heel_bool || toe_bool ){
        temp = true; //stay in loop because foot has not left ground yet
     }
     else{ 
        temp = false;  // foot ready to be rearmed
        digitalWrite(ledPin, LOW);
        armed = false;
     }    
     //Serial.print( heel_bool);
     //Serial.println( toe_bool);
     //delay(500);
  }
  delay(50); // wait for rearm
  counter++;
  //Serial.print("rearmed ");
  //Serial.println(counter);
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }  
}

  
void clear_strip(){
     for(uint16_t i=0; i<strip.numPixels(); i++){
        strip.setPixelColor(i, 0);
     }
     strip.show();
}

//start_bit0 to end_bit0 is accending
//start_bit1 to end_bit1 is decending

void send_ball(int start_bit0, int end_bit0, int start_bit1, int end_bit1, int wait){  // send ball backward (toe step)
    int i=start_bit0;
    int i2=start_bit1;
    
    //each ball and each tain must be calculated
    for(int t = start_bit0; t < end_bit0+7; t++){   
      
      
        if (i <= end_bit0)
          strip.setPixelColor(i,strip.Color(100, 0, 100));  // set initial ball
        if(i <= end_bit0+1)
          strip.setPixelColor( i-1, brightness[1] );  // set first tail
        if(i <= end_bit0+2)
          strip.setPixelColor( i-2, brightness[2] );  // set second tail
        if(i <= end_bit0+3)
          strip.setPixelColor( i-3, brightness[3] );  // set third tail
        if(i <= end_bit0+4)
          strip.setPixelColor( i-4, brightness[4] );  // set fourth tail    
        if(i <= end_bit0+5)
          strip.setPixelColor( i-5, brightness[5] );  // set fourth tail  
        if(i <= end_bit0+6)
          strip.setPixelColor( i-6, brightness[6] );  // set fourth tail  
        if(i <= end_bit0+7)
          strip.setPixelColor( i-7, 0 );  // clear bit after tail
       
      
        if(i2 >= end_bit1)
          strip.setPixelColor(i2,strip.Color(100, 0, 100));  // set initial ball
        if(i2 >= end_bit1-1)
          strip.setPixelColor( i2+1, brightness[1] );  // set first tail
        if(i2 >= end_bit1-2)
          strip.setPixelColor( i2+2, brightness[2] );  // set second tail
        if(i2 >= end_bit1-3)
          strip.setPixelColor( i2+3, brightness[3] );  // set third tail
        if(i2 >= end_bit1-4)
          strip.setPixelColor( i2+4, brightness[4] );  // set fourth tail     
        if(i2 >= end_bit1-5)
          strip.setPixelColor( i2+5, brightness[5] );  // set fourth tail     
        if(i2 >= end_bit1-6)
          strip.setPixelColor( i2+6, brightness[6] );  // set fourth tail     
        if(i2 >= end_bit1-7)
          strip.setPixelColor( i2+7, 0 );  // clear bit after tail
    
        strip.show();
        delay(wait);
        i++;
        i2--;
    }
}


void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*1; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void fireball_belt(){
  if( analogRead(battery_pin) > 750 ){
     //Serial.print("analog is ");
     //Serial.println(analogRead(battery_pin));
     //delay(500);
     heel_hit();
     digitalWrite(ledPin, HIGH);
     Serial.println("ON");
     delay(500); 
     
     toe_hit();
     digitalWrite(ledPin, LOW);
     Serial.println("OFF");  
     delay(500);
  }else{
     Serial.println("LOW BATTERY");  
     delay(1000);  
  }  
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
