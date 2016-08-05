#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);
float intensity[] = {1,.2,.15,.08,.05,0,0,0,0,0,0,0,1,.2,.1,.08,.05,0,0,0,0,0,0,0};
//+float intensity[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int index_led = 0;
long  randNumber;
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  Serial.begin(115200);
  randomSeed(analogRead(0));
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
//colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127, 0, 0), 50); // Red
  //theaterChase(strip.Color(0, 0, 127), 50); // Blue
  //pulse(240,150,200,18);
  circle(0,0,150);
  delay(50);
  lightning(20,0);
  //lightning2(50,0);
  //rainbow(20);
  //rainbowCycle(20);
  //theaterChaseRainbow(50);
  strip.show();
}

void lightning(int bolt, int double_bolt){
  //bolt is the chance of there being a flash put on the ring
  // double_bolt is the chhance of there being 2 flashes
  randNumber = random(bolt);
  
  if (randNumber == 0){
      int randLed = random(strip.numPixels());
      set_pixel(strip.Color(200,200, 0), randLed);
    
  }
  
  randNumber = random(bolt);
  if (randNumber == 0){
      int randLed = random(strip.numPixels());
      set_pixel(strip.Color(255,255,250), randLed);
    
  }
      
  
}
void lightning2(int bolt, int double_bolt){
  //bolt is the chance of there being a flash put on the ring
  // double_bolt is the chhance of there being 2 flashes
  randNumber = random(bolt);
  
  if (randNumber == 0){
    //pulse(150,150,50,8);    
  }
  

  
}



void pulse(int red, int green, int blue, int delay_time){
  int fade = 10;
  while(fade>0){
    colorWipe(strip.Color(red, green, blue), 0); // Red
    delay(delay_time);
    red = red/1.4;
    green = green/1.5;
    blue = blue/1.2;
    fade--;
  }
    //colorWipe(strip.Color(0, 0, 0), 0);
}

void circle(int red, int green, int blue){
    int i0=index_led;
   // Serial.print(index_led);
    int affected_red;
    int affected_green;
    int affected_blue;
    for(uint16_t i=0; i<strip.numPixels(); i++){
       affected_red = red * intensity[i0];
       affected_green = green * intensity[i0];
       affected_blue = blue * intensity[i0];
  /*     Serial.print(millis());
       Serial.print("   ");
       Serial.print(i);
       Serial.print("   ");
       Serial.println(i0);
        Serial.print("   ");
       Serial.print(affected_red);
       Serial.print("   ");
       Serial.print(affected_green);
       Serial.print("   ");
       Serial.println(affected_blue);
    */
       //uint32_t c = strip.Color(affected_red, affected_green, affected_blue);
       
       //set_pixel(uint32_t c, int led)

       if ((i0 == 0) || (i0 == 12)){
          set_pixel(strip.Color(150,150, 150), i);
       }else{
          set_pixel(strip.Color(affected_red, affected_green, affected_blue), i);
       }

       
       //strip.setPixelColor(i0, c);       
       i0++;
       if (i0==24){
         i0=0;
       }
       
    }
    index_led++;
    if (index_led==24){
      index_led=0;
    }
  
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void set_pixel(uint32_t c, int led){
  strip.setPixelColor(led, c);

}

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
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
