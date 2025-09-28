# FastLED Guide

This document is a guide to the **FastLED Arduino library** for controlling addressable LEDs (like WS2812B / NeoPixels).  
It covers the major functions and capabilities, with explanations and code examples.  

---

## 1. Setup and Initialization

### `#include <FastLED.h>`
Import the FastLED library so you can use its functions.

### `FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);`
Adds an LED strip to your program.  

- **CHIPSET**: e.g. `WS2812B`, `NEOPIXEL`  
- **DATA_PIN**: pin connected to the LED strip  
- **COLOR_ORDER**: e.g. `GRB`, `RGB`  
- **leds**: array holding LED colors  
- **NUM_LEDS**: number of LEDs in the strip  

**Example:**
```cpp
#define DATA_PIN 6
#define NUM_LEDS 60
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}
````

### `FastLED.setBrightness(brightness);`

Sets global brightness (0–255).
Brightness scales all LEDs without changing their base color values.

---

## 2. Updating LEDs

### `FastLED.show();`

Pushes all LED changes to the strip. **Required after modifying `leds[]`.**

**Example:**

```cpp
leds[0] = CRGB::Red;  // Set LED 0 to red
FastLED.show();       // Update the strip
```

### `FastLED.clear();` / `FastLED.clear(true);`

Clears all LEDs.

* `true` immediately shows the cleared state without waiting for `show()`.

---

## 3. Setting LED Colors

### `leds[index] = CRGB::Color;`

Set a specific LED to a predefined color like `CRGB::Red`, `CRGB::Green`, `CRGB::Blue`, `CRGB::Black`.

### `leds[index] = CRGB(r, g, b);`

Set a specific LED using RGB values (0–255 each).

### `fill_solid(leds, NUM_LEDS, CRGB::Color);`

Fill all LEDs with the same color.

### `fill_rainbow(leds, NUM_LEDS, startHue, deltaHue);`

Fill strip with a rainbow gradient.

* `startHue`: starting hue (0–255)
* `deltaHue`: hue step between LEDs

### `fill_gradient_RGB(...)` / `fill_gradient_HSV(...)`

Creates smooth color gradients across the strip.

---

## 4. Color Manipulation

### `CHSV(hue, sat, val);`

Represents a color in **Hue (0–255), Saturation (0–255), Value (0–255)**.
Intuitive for cycling colors.

**Example:**

```cpp
leds[0] = CHSV(96, 255, 255);  // Bright green
```

### `fadeToBlackBy(leds, NUM_LEDS, amount);`

Fades all LEDs toward black by `amount` (0–255).
This makes the LEDs slowly fade out.

### `nblend(color1, color2, amount);`

Blends two colors by `amount` (0–255).

### `blend(color1, color2, amount);`

Returns a color blended between two colors.

---

## 5. Utility Functions

### `beatsin8(bpm, low, high);`

Returns a sinusoidal value oscillating between `low` and `high` at `bpm`.
This oscillates values so LEDs pulse naturally.

**Example:**

```cpp
uint8_t pos = beatsin8(60, 0, NUM_LEDS-1);
leds[pos] = CRGB::White;
```

### `EVERY_N_MILLISECONDS(ms) { ... }`

Runs code every `ms` milliseconds without blocking.

**Example:**

```cpp
EVERY_N_MILLISECONDS(50) {
  leds[random(NUM_LEDS)] += CRGB::White;
}
```

### `random8()` / `random16()`

Generates 8-bit (0–255) or 16-bit (0–65535) random values.

* `random8(max)` returns 0–(max-1)

---

## 6. Math Helpers

* `scale8(value, scale)` → scales a value by 0–255
* `qadd8(a, b)` → add with saturation (never exceeds 255)
* `qsub8(a, b)` → subtract with saturation (never below 0)
* `sin8(x)` / `cos8(x)` → fast sine/cosine approximations (0–255)

---

## 7. Common Effects (Building Blocks)

### Twinkle

Random LEDs sparkle briefly, then fade out.
Uses `random8()` and `fadeToBlackBy()`.

### Confetti

Random colored speckles that fade out slowly.

### Fire

Simulated flames using a heat map and fading.

### Shooting Stars

Bright dot moves across the strip with fading tail.

### Rainbow

Use `fill_rainbow()` or cycle `CHSV` hues.

### Strobe / Lightning

Random flashes of bright white with delay.

### Audio / Timer Pulses

Use `beatsin8()` or `EVERY_N_MILLISECONDS()` for rhythm-based effects.

---

## 8. Advanced Features

### Multiple Strips

Control multiple LED strips by calling `FastLED.addLeds()` multiple times.

### Power Management

`FastLED.setMaxPowerInVoltsAndMilliamps(volts, mA);`
Limits brightness to avoid overloading power supplies.

### Color Correction

`FastLED.setCorrection(TypicalLEDStrip);`
Adjusts LED colors for white balance and color accuracy.

### Dithering

`FastLED.setDither(0 or 1);`
Enables or disables dithering to smooth gradients.

---

## 9. Example Combinations

**Twinkle + Rainbow:**

```cpp
fadeToBlackBy(leds, NUM_LEDS, 20);
leds[random(NUM_LEDS)] = CHSV(random8(), 200, 255);
FastLED.show();
```

**Fire Simulation:**

```cpp
for(int i = 0; i < NUM_LEDS; i++) {
  int heat = qsub8(random8(), 20);
  leds[i] = HeatColor(heat);
}
FastLED.show();
```

**Shooting Star:**

```cpp
fadeToBlackBy(leds, NUM_LEDS, 64);
leds[pos] = CRGB::White;
pos++;
if(pos >= NUM_LEDS) pos = 0;
FastLED.show();
```


