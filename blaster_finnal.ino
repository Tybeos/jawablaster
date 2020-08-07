// Tobias Petruj 06.08.2020
// JAWA blaster

#include <FastLED.h>
FASTLED_USING_NAMESPACE

#define DATA_PIN    3 
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64 
#define BRIGHTNESS         100
#define FRAMES_PER_SECOND  128
CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // 3 second delay for recovery
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // set LED stip configuration
  FastLED.setBrightness(BRIGHTNESS); // set master brightness control
}

uint8_t gHue = 64;
uint8_t gVal = 255;
uint8_t state = 0;

void loop() {
  switch (state) {
  case 0:
    for(int i=0;i<NUM_LEDS;i++) {
      leds[i] = CRGB::White;}
    state++;
    break;
  case 10:
    for(int i=0;i<NUM_LEDS;i++) {
      leds[i] = CHSV(gHue + random8(16),255,gVal);}
    gHue--;
    gVal--;
    if (gHue == 0) {state++;}
    break;
  case 11:
    for(int i=0;i<NUM_LEDS;i++) {
      leds[i] = CHSV(gHue + random8(16),255 - random8(32),gVal);}
    gVal--;
    if( random8() < (gVal+random8(16))) {
      leds[ random16(NUM_LEDS) ] += CHSV(160-random8(16),255,255);
      leds[ random16(NUM_LEDS) ] += CHSV(64-random8(16),255,255-random8(64));}
    if (gVal == 0) {state++;}
    break; 
  case 12:
   fadeToBlackBy( leds, NUM_LEDS, 2);
   break;
  default:
    state++;
    gHue = 64;
    gVal = 255;
    break;
  }
  FastLED.show(); // Show LED animation
  FastLED.delay(1000/FRAMES_PER_SECOND); // Frame rate
}
