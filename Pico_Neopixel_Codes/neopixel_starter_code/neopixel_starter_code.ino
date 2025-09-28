#include <FastLED.h>

#define DATA_PIN 2 // Pin connected to data line
#define NUM_LEDS 7 // Number of LEDs on your strip
#define LED_TYPE WS2812 // Part Number of the Neopixels
#define BRIGHTNESS 50  // ~25% to keep current modest

CRGB leds[NUM_LEDS];

void setup() {

  delay(2000); // Power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS); // If color order seems off, modify GRB (Green, Red, Blue)
  FastLED.setBrightness(BRIGHTNESS);
  //Optional: Cap max power draw
  //FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

void loop() {

  fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear all
  leds[0] = CRGB::Red; // First LED red
  leds[1] = CRGB::Blue; // Second LED blue
  leds[2] = CRGB::Green; // Third LED green
  FastLED.show();
  delay(100);
}

