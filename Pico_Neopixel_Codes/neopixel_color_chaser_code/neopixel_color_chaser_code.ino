#include <FastLED.h>

#define LED_PIN 2 // Pin connected to data line
#define NUM_LEDS 7 // Number of LEDs on your strip
#define LED_TYPE WS2812 // Part Number of the Neopixels
#define BRIGHTNESS 50 // ~25% to keep current modest

CRGB leds[NUM_LEDS];

void setup() {
  
  dTime = 75 // Adjust delay (in ms) between color chases
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);                                           
  delay(2000);
}

void loop () {

  for (int i = 0; i < NUM_LEDS; i++) {
   leds[i] = CRGB::Red;
   FastLED.show();
   delay(dTime);
  } 

  for (int i = NUM_LEDS-1; i >= 0; i--) {
   leds[i] = CRGB::Green;
   FastLED.show();
   delay(dTime);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
   leds[i] = CRGB::Blue;
   FastLED.show();
   delay(dTime);
  }

  for (int i = NUM_LEDS-1; i >= 0; i--) {
   leds[i] = CRGB::Cyan;
   FastLED.show();
   delay(dTime);
  }

 }

