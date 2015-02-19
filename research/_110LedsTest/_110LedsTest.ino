#include "FastLED.h"
// Define number of leds
#define NUM_LEDS 110
// Define the array of leds
CRGB leds[NUM_LEDS];
// Arduino pin used for Data
#define PIN 6 


void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
}

void loop() {
  // one led at a time
    for(int i= 0; i < NUM_LEDS; i++) 
    {
      // clear all values in array and set to 0
      memset(leds, 0, NUM_LEDS * 3);
      leds[i].r = 64;
      leds[i].g = 0;
      leds[i].b = 0;
      FastLED.show();
      delay(250);
    }
}
