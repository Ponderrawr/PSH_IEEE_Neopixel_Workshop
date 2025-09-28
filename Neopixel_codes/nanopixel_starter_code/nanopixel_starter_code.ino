#include <FastLED.h>
#define NUM_LEDS 7 
#define LED_PIN 10 

CRGB leds[NUM_LEDS];

void setup() {
  // Set NUM_LEDS to the total number of LEDs you have, and LED_PIN to which pin you are using
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);                                           
  delay(2000);
}

void loop () {
  for (int i = 0; i < NUM_LEDS; i++) {
   leds[i] = CRGB::Red;
   FastLED.show();
  } 

  for (int i = NUM_LEDS-1; i >= 0; i--) {
   leds[i] = CRGB::Green;
   FastLED.show();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
   leds[i] = CRGB::Blue;
   FastLED.show();
  }

  for (int i = NUM_LEDS-1; i >= 0; i--) {
   leds[i] = CRGB::Cyan;
   FastLED.show();
  }
 }

