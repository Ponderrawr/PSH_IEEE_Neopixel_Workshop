#include <FastLED.h>

#define DATA_PIN 2 // Pin connected to data line
#define NUM_LEDS 7 // Number of LEDs on your strip
#define LED_TYPE WS2812 // Part Number of the Neopixels
#define BRIGHTNESS 50  // ~25% to keep current modest

CRGB leds[NUM_LEDS];

uint8_t gHue = 0; // Base Color

void setup() {

  delay(2000); // Power-up safety delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS); // If color order seems off, modify GRB (Green, Red, Blue)
  FastLED.setBrightness(BRIGHTNESS);
  //Optional: Cap max power draw
  //FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

// ---------Twinkle Effect---------
void twinkleEffect() {

  fadeToBlackBy(leds,NUM_LEDS, 50);  // Slowly fade old LEDs
  int pos = random16(NUM_LEDS);      // Pick a random LED
  leds[pos] += CHSV(gHue + random8(64), 200, 255); // Bright spark
  FastLED.show();
  delay(50);
}

//---------Fade Through Colors---------
void fadeEffect() {

  fill_rainbow(leds, NUM_LEDS, gHue, 5); // Rainbow across the strip
  FastLED.show();
  gHue++;                                // Slowly cycle the base hue
  delay(20);
}

//---------Lightning Effect---------
void lightningEffect() {
 //Random flashes with variable brightness
  int flashes = random8(1, 2);           // Number of flashes in one strike
  for (int i = 0; i < flashes; i++) {
    int start = random16(NUM_LEDS);     // Random starting position
    int length = random16(3, 4);        // Random strike length
    int end = min(NUM_LEDS - 1, start + length);
    fill_solid(leds + start, end - start, CRGB::White);
    FastLED.show();
    delay(random8(20,100));             // Short flash
    fill_solid(leds + start, end - start, CRGB::Black);
    FastLED.show();
    delay(random8(50, 200));
  }
  delay(random8(1000, 4000));           // Pause before next strike
}

//---------Fire Effect---------
void fireEffect() {

  static byte heat[NUM_LEDS];
  // Step 1: Cool down
  for (int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8(heat[i], random8(0, ((55 * 10) / NUM_LEDS) + 2));
  }
  // Step 2: Heat diffusion upward
  for (int k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  // Step 3: Ignite new sparks near the bottom
  if (random8() < 120) {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255));
  }
  // Step 4: Convert to color
  for (int j = 0; j < NUM_LEDS; j++) {
    CRGB color = HeatColor(heat[j]);
    leds[j] = color;
  }
  FastLED.show();
  delay(30);
}

//---------Shooting Star---------
void shootingStarEffect() {

  static int pos = 0;
  static int speed = 2; // higher = faster
  static bool active = false;

  // Occasionally spawn a shooting star
  if (!active && random8() < 5) {
    pos = 0;
    active = true;
  }

  // Draw star if active
  if (active) {
    fadeToBlackBy(leds, NUM_LEDS, 40);
    leds[pos] = CRGB::White;
    if (pos > 0) leds[pos - 1].fadeToBlackBy(150);
    if (pos > 1) leds[pos - 2].fadeToBlackBy(200);
    FastLED.show();

    pos += speed;
    if (pos >= NUM_LEDS) {
      active = false;
      pos = 0;
    }
  }
  delay(30);
}

//---------Timer Based Pulse (Like a bass beat)---------
void pulseEffect() {

  static uint16_t beatTimer = 0;
  beatTimer += 1;

  // Sine wave brightness oscillation
  uint8_t level = beatsin8(60, 50, 255); // 60 BPM
  fill_solid(leds, NUM_LEDS, CHSV(gHue, 200, level));
  FastLED.show();

  gHue++; // slowly shift color palette
  delay(20);
}

//---------Confetti---------
void confettiEffect() {

  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(gHue + random8(64), 200, 255);
  FastLED.show();

  gHue++;
  delay(30);
}


void loop() {
  
  // Pick the effect you want to run:
  //twinkleEffect();
  //fadeEffect();
  //lightningEffect();
  //fireEffect();
  //shootingStarEffect();
  //pulseEffect();
  //confettiEffect();
}

