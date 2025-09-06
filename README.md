# IEEE NeoPixel Workshop (Penn State)

Build a 7‑LED NeoPixel project driven by an Arduino Nano (or ESP32) and powered safely from a USB charger. This repo includes starter code, wiring/power notes, a step‑by‑step process, and troubleshooting.

## Quick Start
- Install the Arduino IDE.
- Install the “Adafruit NeoPixel” library (Library Manager).
- Open `code/starter_nano/starter_nano.ino`, set `NUM_LEDS` to 7, choose your data pin, and upload.
- Power the LED strip from a USB wall charger; power the microcontroller from your laptop.

## Repository Structure
README.md
LICENSE
assets/
wiring-diagram.png
bom/
BOM.md
code/
starter_nano/
starter_nano.ino
starter_esp32/
starter_esp32.ino
docs/
PROCESS.md
WIRING.md
POWER.md
TROUBLESHOOT.md

## Wiring (summary)
![Wiring diagram](assets/wiring-diagram.png)

- USB charger 5V -> LED strip 5V  
- USB charger GND -> LED strip GND  
- MCU GND -> LED strip GND (common ground)  
- MCU D6 (example) -> 330–470 Ω -> LED DIN  
- 1000 µF electrolytic across LED 5V/GND near the first LED

Notes:
- Do not power the strip from the Nano’s 5V pin.
- If using a 3.3 V MCU (ESP32/ESP8266/RP2040), use a 74AHCT125/74HCT14 level shifter on the data line or lower LED V+ to ~4.3–4.5 V with a diode in series.

## Power Notes
- One 7‑LED strip worst case ≈ 7 × 60 mA = 0.42 A at 5 V (full white, full brightness).
- Multi‑port USB‑A chargers are easy and safe for a classroom.
- Cap brightness in code (e.g., 25–40%) for comfort and headroom.

## Starter Code (Nano, 5V logic)
See `code/starter_nano/starter_nano.ino`. Paste into the Arduino IDE.

```cpp
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 7
#define BRIGHTNESS 64  // ~25% to keep current modest

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 30);
  colorWipe(strip.Color(0, 255, 0), 30);
  colorWipe(strip.Color(0, 0, 255), 30);
  rainbow(10);
}

void colorWipe(uint32_t color, uint8_t waitMs) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(waitMs);
  }
}

void rainbow(uint8_t waitMs) {
  for (uint16_t j = 0; j < 256; j++) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, wheel((i + j) & 255));
    }
    strip.show();
    delay(waitMs);
  }
}

uint32_t wheel(byte pos) {
  if (pos < 85) {
    return strip.Color(pos * 3, 255 - pos * 3, 0);
  } else if (pos < 170) {
    pos -= 85;
    return strip.Color(255 - pos * 3, 0, pos * 3);
  } else {
    pos -= 170;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
}
ESP32/RP2040 Option
If you use 3.3 V boards, add a level shifter (SN74AHCT125/74HCT14) or drop LED V+ to ~4.3–4.5 V with a diode. See code/starter_esp32/starter_esp32.ino.

Docs
Wiring: docs/WIRING.md
Power: docs/POWER.md
Step-by-step process: docs/PROCESS.md
Troubleshooting: docs/TROUBLESHOOT.md
Bill of Materials: bom/BOM.md
