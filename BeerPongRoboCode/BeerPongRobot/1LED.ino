
#define NUM_LEDS    1
CRGB leds[NUM_LEDS];

int LedMode = 2;
int LedR = 0;
int LedG = 0;
int LedB = 0;

long long LedNextStep = 0;
int LedStep = 0;
void SetColor(int r, int g, int b) {
   // Serial.print("ClearColor");
    for (int a = 0; a < NUM_LEDS; a++) {
      leds[a] = CRGB(r, g, b);
    }
    FastLED.show();
    LedR = r;
    LedG = g;
    LedB = b;
}

void LEDSetup() {
  pinMode(LEDPin,OUTPUT);
  FastLED.addLeds<WS2812, LEDPinNodeMCU, GRB>(leds, NUM_LEDS);
  SetColor(0,0,0);
  LedNextStep = 1000 + millis();
}

void LEDLoop() {
  switch (LedMode) {
    case 0:  // Off

  SetColor(0,0,0);
  LedMode = -1;
    break;
  case 1: // set Color
      LedMode = -1;
      SetColor(LedR,LedG,LedB);
    break;
    case 2: // Random Party Colors 
      if (millis() > LedNextStep) {
        SetColor(255,255,255);
        LedNextStep = millis() + 3000 * random(1);
      }
    break;
  }
}
