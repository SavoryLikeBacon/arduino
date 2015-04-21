
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
int led_total=240;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(led_total, STRIP_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
int i = 0;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  colorWipe(0, 0);

}

void loop(){
   //walk(); 
  pin_point();
}



void walk(){  
   
  strip.setPixelColor(i,strip.Color(100, 100, 100));
  strip.show();
  Serial.println(i);
  i=i+1;
  delay(100);
  colorWipe(0, 0);
  if (i > led_total)
      i=0;
}

void pin_point(){  
  int led=239;
  strip.setPixelColor(led,strip.Color(100, 100, 100));
  strip.show();
  delay(500);
  strip.setPixelColor(led,strip.Color(0, 0, 0));
  strip.show();
  delay(500);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
     // strip.show();
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


