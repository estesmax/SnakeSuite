#include "FastLED.h"

#define NUM_LEDS 194
#define DATA_PIN 5

CRGB leds[NUM_LEDS];

static uint8_t huea = 0;
//CRGB rgb;
//#define NUM_COLORS 5

//CRGB colors[NUM_COLORS] = {(115,174,211), (62,71,91), (116,217,166), (245,145,97), (217,116,167)};

void setup() {
  // put your setup code here, to run once:
   // put your setup code here, to run once:
    LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
    LEDS.setBrightness(200);
    for(int i = 0; i < NUM_LEDS; i+=7) { 
      leds[i] = CRGB::Black;
    }
    FastLED.show();
}

void loop() {
  // put your main code here, to run repeatedly:
//
//  leds[random8(NUM_LEDS)] = CRGB::Red;
//  fadeall();
//  FastLED.show();
//  delay(50);
  fadeall();
  leds[random8(NUM_LEDS)] = CHSV(huea,255,255);
  huea+=33;
  FastLED.show();
  delay(15);
//  leds[random8(NUM_LEDS)] = CHSV(69, 87, 28);
//  fadeall();
//  FastLED.show();
//  delay(50);
//  leds[random8(NUM_LEDS)] = CHSV(100, 67, 85);
//  fadeall();
//  FastLED.show();
//  delay(50);
//  leds[random8(NUM_LEDS)] = CHSV(19, 60, 96);
//  fadeall();
//  FastLED.show();
//  delay(50);
//  leds[random8(NUM_LEDS)] = CHSV(30, 93, 85);
//  FastLED.show();
//  delay(50);
}

void fadeall() {
  for(int i = 0; i < NUM_LEDS; i++) { 
//      leds[i].nscale8(240); 
      leds[i].fadeToBlackBy( 8 );
   }
}
