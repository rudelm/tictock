#include "FastLED.h"
// Number of RGB LEDs in the strand
#define NUM_LEDS 1 

// Define the array of leds
CRGB leds[NUM_LEDS];
// Arduino pin used for Data
#define PIN 6 

#define DELAY 20

void setup()
{
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
}

#define V_MAX 255
#define V_MIN 32

void loop() {
  int16_t h, s, v;
  int8_t dv = 1;
  h = 0;
  s = 255;
  v = V_MIN;

  FastLED.showColor(CHSV(h, s, v));
  delay(3000);
  
  while (1)
  {      
    for (h = 0; h < 256; h++)
    {
      FastLED.showColor(CHSV(h, s, v));
      delay(DELAY);
      
      v += 3 * dv;
      if (v > V_MAX) { v = V_MAX; dv = -1; }
      if (v < V_MIN) { v = V_MIN; dv = 1; }
    }
  }
}
