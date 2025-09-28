#include <FastLED.h>

#define DATA_PIN 2 // Pin connected to data line
#define NUM_LEDS 7 // Number of LEDs on your strip
#define LED_TYPE WS2812 // Part Number of the Neopixels
#define BRIGHTNESS 50  // ~25% to keep current modest

CRGB leds[NUM_LEDS];

void setup() {

  delay(2000); // Power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS); //If color order seems off, modify GRB (Green, Red, Blue)
  FastLED.setBrightness(BRIGHTNESS);
  //Optional: Cap max power draw
  //FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
}

void loop() {

  for(int i = 0; i < NUM_LEDS; i++) {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear all
    leds[i] = CRGB::White; // Light one LED
    FastLED.show();
    delay(100);
    leds[i] = CRGB::Black; // Turn it off an move to the next
  }
}

