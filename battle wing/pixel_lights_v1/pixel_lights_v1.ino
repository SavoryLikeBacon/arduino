#include <Adafruit_NeoPixel.h>

#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN_6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN_7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN_8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, PIN_9, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.




void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  //rainbow(20);
  //rainbowCycle(20);
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
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}



/*
Copyright 2011 Lex Talionis (Lex.V.Talionis at gmail)
This program is free software: you can redistribute it 
and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, 
either version 3 of the License, or (at your option) any 
later version.

This code uses pin change interrupts and timer 1 to mesure the 
time between the rise and fall of 3 channels of PPM 
(Though often called PWM, see http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1253149521/all)
on a typical RC car reciver.  It could be extended to as
many channels as you like.  It uses the PinChangeInt library
to notice when the signal pin goes high and low, and the 
Timer1 library to record the time between.


*/
#include <PinChangeInt.h>    // http://playground.arduino.cc/Main/PinChangeInt
#include <PinChangeIntConfig.h>
#include <TimerOne.h>        // http://playground.arduino.cc/Code/Timer1

#define NO_PORTB_PINCHANGES //PinChangeInt setup
#define NO_PORTC_PINCHANGES    //only port D pinchanges (see: http://playground.arduino.cc/Learning/Pins)
#define PIN_COUNT 3    //number of channels attached to the reciver
#define MAX_PIN_CHANGE_PINS PIN_COUNT

#define RC_TURN 2    //arduino pins attached to the reciver
#define RC_FWD 3
#define RC_FIRE 4
//byte pin[] = {RC_FWD, RC_TURN, RC_FIRE};    //for maximum efficency thise pins should be attached
byte pin[] = {RC_FWD};
unsigned int time[] = {0,0,0};                // to the reciver's channels in the order listed here

byte state=0;
byte burp=0;    // a counter to see how many times the int has executed
byte cmd=0;     // a place to put our serial data
byte i=0;       // global counter for tracking what pin we are on

void setup() {
    Serial.begin(115200);
    Serial.print("PinChangeInt ReciverReading test");
    Serial.println();            //warm up the serial port

    Timer1.initialize(2200);    //longest pulse in PPM is usally 2.1 milliseconds,
                                //pick a period that gives you a little headroom.
    Timer1.stop();                //stop the counter
    Timer1.restart();            //set the clock to zero

    for (byte i=0; i<1; i++)
    {
        pinMode(pin[i], INPUT);     //set the pin to input
        digitalWrite(pin[i], HIGH); //use the internal pullup resistor
        PCintPort::attachInterrupt(pin[i], rise,RISING); // attach a PinChange Interrupt to our first pin
        byte pin[] = {RC_FWD};
    }
}

void loop2() {
    cmd=Serial.read();        //while you got some time gimme a systems report
    if (cmd=='p')
    {
        Serial.print("time:\t");
        for (byte i=0; i<PIN_COUNT;i++)
        {
            Serial.print(i,DEC);
            Serial.print(":");
            Serial.print(time[i],DEC);
            Serial.print("\t");
        }
        Serial.print(burp, DEC);
        Serial.println();
/*      Serial.print("\t");
        Serial.print(clockCyclesToMicroseconds(Timer1.pwmPeriod), DEC);
        Serial.print("\t");
        Serial.print(Timer1.clockSelectBits, BIN);
        Serial.print("\t");
        Serial.println(ICR1, DEC);*/
    }
    cmd=0;
    switch (state)
    {
        case RISING: //we have just seen a rising edge
            PCintPort::detachInterrupt(pin[i]);
            PCintPort::attachInterrupt(pin[i], fall, FALLING); //attach the falling end
            state=255;
            break;
        case FALLING: //we just saw a falling edge
            PCintPort::detachInterrupt(pin[i]);
            i++;                //move to the next pin
            i = i % PIN_COUNT;  //i ranges from 0 to PIN_COUNT
            PCintPort::attachInterrupt(pin[i], rise,RISING);
            state=255;
            break;
        /*default:
            //do nothing
            break;*/
    }
}

void rise()        //on the rising edge of the currently intresting pin
{
    Timer1.restart();        //set our stopwatch to 0
    Timer1.start();            //and start it up
    state=RISING;
//  Serial.print('r');
    burp++;
}

void fall()        //on the falling edge of the signal
{
    state=FALLING;
    time[i]=readTimer1();    // read the time since timer1 was restarted
//  time[i]=Timer1.read();    // The function below has been ported into the
                            // the latest TimerOne class, if you have the
                            // new Timer1 lib you can use this line instead
    Timer1.stop();
//  Serial.print('f');
}

unsigned long readTimer1()        //returns the value of the timer in microseconds
{                                    //rember! phase and freq correct mode counts 
                                    //up to ICR1 then down again
    unsigned int tmp=TCNT1;
    char scale=0;
    switch (Timer1.clockSelectBits)
    {
    case 1:// no prescalse
        scale=0;
        break;
    case 2:// x8 prescale
        scale=3;
        break;
    case 3:// x64
        scale=6;
        break;
    case 4:// x256
        scale=8;
        break;
    case 5:// x1024
        scale=10;
        break;
    }
    while (TCNT1==tmp) //if the timer has not ticked yet
    {
        //do nothing -- max delay here is ~1023 cycles
    }
    tmp = (  (TCNT1>tmp) ? (tmp) : (ICR1-TCNT1)+ICR1  );//if we are counting down add the top value
                                                        //to how far we have counted down
    return ((tmp*1000L)/(F_CPU /1000L))<<scale;
}
