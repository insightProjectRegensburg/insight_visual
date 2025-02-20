#include <FastLED.h>

#define LED_PIN_WINDOW 3
#define LED_PIN 8
#define NUM_LEDS_WINDOW 136
#define BRIGHTNESS 255
const int sensor = 5;
int val = 0;
int lastValue = 0;
CHSV hsv;

CRGB ledsWindow[NUM_LEDS_WINDOW];

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN_WINDOW>(ledsWindow, NUM_LEDS_WINDOW);
  pinMode(LED_PIN, OUTPUT);
  pinMode(sensor, INPUT);  // PIR motion sensor is determined is an input here.
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sensor);

  if (val == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    if (lastValue == 0) {
      hsv.hue = 75;  //green
      hsv.val = 255;
      hsv.sat = 255;
      for (int i = 0; i < NUM_LEDS_WINDOW; i++)
        ledsWindow[i] = hsv;
      for (int i = 0; i < BRIGHTNESS; i++) {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(100);
      }
    }
    lastValue = 1;
  } else {
    digitalWrite(LED_PIN, LOW);
    lastValue = 0;
    for (int i = 0; i < NUM_LEDS_WINDOW; i++)
      fill_blue(ledsWindow, i);
    FastLED.show();
  }
}

void fill_blue(struct CRGB *pFirstLED, int numToFill) {
  CHSV hsv;
  uint8_t hue = beatsin8(5, 128, 170);  //beat8(speed, 10);
  hsv.hue = hue;
  hsv.val = 255;
  hsv.sat = 240;
  for (int i = 0; i < numToFill; i++) {
    pFirstLED[i] = hsv;
  }
}
