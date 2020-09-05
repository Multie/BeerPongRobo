
#define NUM_LEDS    1
CRGB leds[NUM_LEDS];

int LedMode = 0;

void SetColor(int r, int g, int b) {
   // Serial.print("ClearColor");
    for (int a = 0; a < NUM_LEDS; a++) {
      leds[a] = CRGB(r, g, b);
    }
    FastLED.show();
}

void LEDSetup() {
  FastLED.addLeds<WS2812, LEDPin, GRB>(leds, NUM_LEDS);
  SetColor(0,0,0);
}

void LEDLoop() {
  
}
