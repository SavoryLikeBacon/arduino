#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(115200);
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe_split1(strip.Color(0, 0, 255), 50); // Blue
   //colorWipe_split2(strip.Color(100, 0, 100), 1000, 3); // Blue
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue
  //colorWipe_split1(strip.Color(0, 0, 0), 0); // Blue
  //rainbow(20);
  //rainbowCycle(20);
  //clear_strip();
  lazy_split(18);
  delay(500);
  //theaterChaseRainbow(50);
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
  
  
  
}

void colorWipe_split1(uint32_t c, double wait) {
  int mid = (strip.numPixels()/2)-1;
  
  for(uint16_t i=0; i<=mid; i++) {
      strip.setPixelColor(mid+1+i, c);
      strip.setPixelColor(mid-i, c);
      strip.show();
      delay(wait);
         
  }
}
  /*
void colorWipe_split2(uint32_t c, double wait, int tail) {
  int mid_low = (strip.numPixels()/2)-1;
  int mid_high = (strip.numPixels()/2);
  int temp = 0;
  int light =0;
  int intensity = 100;
  for(uint16_t i=0; i<mid_low; i++) {
      
    //strip.setPixelColor(mid_high+i, c);
      Serial.print("head - ");
      Serial.print(mid_high+i);
      strip.setPixelColor(mid_high+i, c);
      temp = intensity;
      light = 0;
      Serial.print(" tail - ");
      for (int t=0; t <= tail; t++){
        if(i>0){
            temp = temp/2;
            
            //strip.setPixelColor(mid_high+i-1+t, temp;
            Serial.print(mid_high+i);
            light=mid_high+i-t;
            if(light < mid_high)
               strip.setPixelColor(light, temp);          
         }
         if (t>tail){
             
         }
         //if(i>4){
         //strip.setPixelColor(mid_high+i-5, 0);
         //strip.setPixelColor(mid_low-i+5, 0);          
         //} 
      
      }
      Serial.println("");
      if(i>1){
         strip.setPixelColor(mid_high+i-2, 15);
         strip.setPixelColor(mid_low-i+2, 15);          
             
      }
      
       if(i>2){
         strip.setPixelColor(mid_high+i-3, 8);
         strip.setPixelColor(mid_low-i+3, 8);          
     }
      
       if(i>3){
         strip.setPixelColor(mid_high+i-4, 4);
         strip.setPixelColor(mid_low-i+4, 4);          
             
      }

     
      
      
      strip.show();
      delay(wait);
         
  }
   
   */
   
void lazy_split(double wait){
      
    for (int i=0;i<=14;i++){
      clear_strip();
      switch (i){
        case 0:
           strip.setPixelColor(9,strip.Color(100, 0, 100));
           strip.setPixelColor(10,strip.Color(100, 0, 100));
           break;   
        case 1:
           strip.setPixelColor(8,strip.Color(100, 0, 100));
           strip.setPixelColor(9,strip.Color(0, 0, 80));
           
           strip.setPixelColor(11,strip.Color(100, 0, 100));
           strip.setPixelColor(10,strip.Color(0, 0, 80));
           break;         
        case 2:
           strip.setPixelColor(7,strip.Color(100, 0, 100));
           strip.setPixelColor(8,strip.Color(0, 0, 60));
           strip.setPixelColor(9,strip.Color(0, 0, 30));
           
           strip.setPixelColor(12,strip.Color(100, 0, 100));
           strip.setPixelColor(11,strip.Color(0, 0, 60));
           strip.setPixelColor(10,strip.Color(0, 0, 30));
           break;        
        case 3:
           strip.setPixelColor(6,strip.Color(100, 0, 100));
           strip.setPixelColor(7,strip.Color(0, 0, 60));
           strip.setPixelColor(8,strip.Color(0, 0, 30));
           strip.setPixelColor(9,strip.Color(0, 0, 15));
                      
           strip.setPixelColor(13,strip.Color(100, 0, 100));
           strip.setPixelColor(12,strip.Color(0, 0, 60));
           strip.setPixelColor(11,strip.Color(0, 0, 30));
            strip.setPixelColor(10,strip.Color(0, 0, 15));
           break;  
           
        case 4:
           strip.setPixelColor(5,strip.Color(100, 0, 100));
           strip.setPixelColor(6,strip.Color(0, 0, 60));
           strip.setPixelColor(7,strip.Color(0, 0, 30));
           strip.setPixelColor(8,strip.Color(0, 0, 15));
           strip.setPixelColor(9,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(14,strip.Color(100, 0, 100));
           strip.setPixelColor(13,strip.Color(0, 0, 60));
           strip.setPixelColor(12,strip.Color(0, 0, 30));
           strip.setPixelColor(11,strip.Color(0, 0, 15));
           strip.setPixelColor(10,strip.Color(0, 0, 8));
           break;   
       
        case 5:
           strip.setPixelColor(4,strip.Color(100, 0, 100));
           strip.setPixelColor(5,strip.Color(0, 0, 60));
           strip.setPixelColor(6,strip.Color(0, 0, 30));
           strip.setPixelColor(7,strip.Color(0, 0, 15));
           strip.setPixelColor(8,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(15,strip.Color(100, 0, 100));
           strip.setPixelColor(14,strip.Color(0, 0, 60));
           strip.setPixelColor(13,strip.Color(0, 0, 30));
           strip.setPixelColor(12,strip.Color(0, 0, 15));
           strip.setPixelColor(11,strip.Color(0, 0, 8));
           break;            
      
         case 6:
           strip.setPixelColor(3,strip.Color(100, 0, 100));
           strip.setPixelColor(4,strip.Color(0, 0, 60));
           strip.setPixelColor(5,strip.Color(0, 0, 30));
           strip.setPixelColor(6,strip.Color(0, 0, 15));
           strip.setPixelColor(7,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(16,strip.Color(100, 0, 100));
           strip.setPixelColor(15,strip.Color(0, 0, 60));
           strip.setPixelColor(14,strip.Color(0, 0, 30));
           strip.setPixelColor(13,strip.Color(0, 0, 15));
           strip.setPixelColor(12,strip.Color(0, 0, 8));
           break;   
           
        case 7:
           strip.setPixelColor(2,strip.Color(100, 0, 100));
           strip.setPixelColor(3,strip.Color(0, 0, 60));
           strip.setPixelColor(4,strip.Color(0, 0, 30));
           strip.setPixelColor(5,strip.Color(0, 0, 15));
           strip.setPixelColor(6,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(17,strip.Color(100, 0, 100));
           strip.setPixelColor(16,strip.Color(0, 0, 60));
           strip.setPixelColor(15,strip.Color(0, 0, 30));
           strip.setPixelColor(14,strip.Color(0, 0, 15));
           strip.setPixelColor(13,strip.Color(0, 0, 8));
           break;

        case 8:
           strip.setPixelColor(1,strip.Color(100, 0, 100));
           strip.setPixelColor(2,strip.Color(0, 0, 60));
           strip.setPixelColor(3,strip.Color(0, 0, 30));
           strip.setPixelColor(4,strip.Color(0, 0, 15));
           strip.setPixelColor(5,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(18,strip.Color(100, 0, 100));
           strip.setPixelColor(17,strip.Color(0, 0, 60));
           strip.setPixelColor(16,strip.Color(0, 0, 30));
           strip.setPixelColor(15,strip.Color(0, 0, 15));
           strip.setPixelColor(14,strip.Color(0, 0, 8));
           break;
      
        case 9:
           strip.setPixelColor(0,strip.Color(100, 0, 100));
           strip.setPixelColor(1,strip.Color(0, 0, 60));
           strip.setPixelColor(2,strip.Color(0, 0, 30));
           strip.setPixelColor(3,strip.Color(0, 0, 15));
           strip.setPixelColor(4,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(19,strip.Color(100, 0, 100));
           strip.setPixelColor(18,strip.Color(0, 0, 60));
           strip.setPixelColor(17,strip.Color(0, 0, 30));
           strip.setPixelColor(16,strip.Color(0, 0, 15));
           strip.setPixelColor(15,strip.Color(0, 0, 8));
           break;
           
         case 10:
           strip.setPixelColor(0,strip.Color(0, 0, 60));
           strip.setPixelColor(1,strip.Color(0, 0, 30));
           strip.setPixelColor(2,strip.Color(0, 0, 15));
           strip.setPixelColor(3,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(19,strip.Color(0, 0, 60));
           strip.setPixelColor(18,strip.Color(0, 0, 30));
           strip.setPixelColor(17,strip.Color(0, 0, 15));
           strip.setPixelColor(16,strip.Color(0, 0, 8));
           break;
           
         case 11:
           strip.setPixelColor(0,strip.Color(0, 0, 30));
           strip.setPixelColor(1,strip.Color(0, 0, 15));
           strip.setPixelColor(2,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(19,strip.Color(0, 0, 30));
           strip.setPixelColor(18,strip.Color(0, 0, 15));
           strip.setPixelColor(17,strip.Color(0, 0, 8));
           break;
      
         case 12:
           strip.setPixelColor(0,strip.Color(0, 0, 15));
           strip.setPixelColor(1,strip.Color(0, 0, 8));      
                      
           strip.setPixelColor(19,strip.Color(0, 0, 15));
           strip.setPixelColor(18,strip.Color(0, 0, 8));
           break;
           
        case 13:
           strip.setPixelColor(0,strip.Color(0, 0, 8));      
           strip.setPixelColor(19,strip.Color(0, 0, 8));
           break;
      
         case 14:
            break;
      }  
      Serial.println("showing");
      strip.show();
      delay(wait);
    }
        
}
   
void clear_strip(){
     for(uint16_t i=0; i<strip.numPixels(); i++){
        strip.setPixelColor(i, 0);
     }
     //strip.show();
}
   
/*  for(uint16_t i=0; i<mid; i++) {
      strip.setPixelColor(, c);
      strip.setPixelColor(mid-i, c);
      
      Serial.print(mid-i-train);
      Serial.println(mid+i-train);
     // strip.setPixelColor(mid-i-train, strip.Color(0, 0, 0));
      //strip.setPixelColor(mid+i+1-tr, strip.Color(0, 0, 0));
      strip.show();
      delay(wait);         
  }
  */
  
  //strip.setPixelColor(5, strip.Color(0, 0, 0));
  //strip.Color(20, 0, 30)
  



void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
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

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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

