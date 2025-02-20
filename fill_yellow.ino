#include <FastLED.h>

#define LED_PIN_SUN 3
#define LED_PIN 9
#define NUM_LEDS_SUN 133
#define BRIGHTNESS 255
const int sensor = 7;
int val = 0;
int lastValue = 0;
CHSV hsv;

CRGB ledsSun[NUM_LEDS_SUN];

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN_SUN>(ledsSun, NUM_LEDS_SUN);
  pinMode(LED_PIN, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(sensor);

  if (val == HIGH) {

//    digitalWrite(LED_PIN, HIGH);


    if (lastValue == 0) {

      hsv.hue = 18;  //yellow
      hsv.val = 255;
      hsv.sat = 255;

      for (int i = 0; i < NUM_LEDS_SUN; i++)
        ledsSun[i] = hsv;
      for (int i = 0; i < BRIGHTNESS; i++) {
        FastLED.setBrightness(i);
        FastLED.show();
        delay(100);
      }
    }
    lastValue = 1;
  } else {
   // digitalWrite(LED_PIN, LOW);
    lastValue = 0; 
    FastLED.clear();
    FastLED.show();
    //delay(5000);
  }
}

