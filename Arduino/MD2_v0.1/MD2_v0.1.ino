#include <FastLED.h>
#include <math.h>

#define LED_PIN     2
#define ROTA1_PIN   14
#define ROTA2_PIN   16
#define ROTAB_PIN   12
#define ROTB1_PIN   4
#define ROTB2_PIN   5
#define ROTBB_PIN   0
#define NUM_LEDS    45
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

unsigned long   currentTime;
unsigned long   loopTime;

unsigned long   currentTime2;
unsigned long   loopTime2;

int             valueA              = 0;
int             buttonA             = 0;
unsigned char   btnA;
unsigned char   btnA_prev           = 0;
unsigned char   rotA_1;
unsigned char   rotA_2;
unsigned char   rotA_1_prev         = 0;
unsigned int    rotA_resolution     = 1;

int             valueB              = 0;
int             buttonB             = 0;
unsigned char   btnB;
unsigned char   btnB_prev           = 0;
unsigned char   rotB_1;
unsigned char   rotB_2;
unsigned char   rotB_1_prev         = 0;
unsigned int    rotB_resolution     = 1;

int             brightness          = 64;

CRGB            persistent_color    = CRGB::White;

CRGB leds[NUM_LEDS];

void setup() 
{
  Serial.begin (115200);
  Serial.println("start Setup");   
  delay( 3000 ); // power-up safety delay
  pinMode(ROTA1_PIN, INPUT);
  pinMode(ROTA2_PIN, INPUT);
  pinMode(ROTAB_PIN, INPUT);
  pinMode(ROTB1_PIN, INPUT);
  pinMode(ROTB2_PIN, INPUT);
  pinMode(ROTBB_PIN, INPUT);
  currentTime = millis();
  loopTime = currentTime;
  currentTime2 = millis();
  loopTime2 = currentTime;
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( brightness );
  color(persistent_color);
  FastLED.show();
  Serial.println("finish Setup");  
}

void color(CRGB color)
{
  if(color == CHSV(0, 255, 255)){
    color = CRGB::White;
  }
  for(int i = 0;i < NUM_LEDS;i++){
    leds[i] = color;
  }
}

void readRot() 
{
  currentTime = millis();
  if(currentTime >= (loopTime + 1)) {  // 5ms since last check of encoder = 200Hz 
    
    loopTime = currentTime;           // Updates loopTime
     
    rotA_1_prev = rotA_1;               // Store value of A for next time 
    rotA_1 = digitalRead(ROTA1_PIN);    // Read encoder pins
    rotA_2 = digitalRead(ROTA2_PIN);   
    
    rotB_1_prev = rotB_1;               // Store value of B for next time 
    rotB_1 = digitalRead(ROTB1_PIN);    // Read encoder pins
    rotB_2 = digitalRead(ROTB2_PIN);  
    
    if((!rotA_1) && (rotA_1_prev)){
      Serial.println("A Rot");
      // A has gone from high to low 
      if(rotA_2) {
        Serial.println("A +");
        valueA+=rotA_resolution;
      } else {
        Serial.println("A -");
        valueA-=rotA_resolution;
      }
      valueA = doOverflow(valueA, 0, 44);
    }
    
    if((!rotB_1) && (rotB_1_prev)){
      Serial.println("B Rot");
      // B has gone from high to low 
      if(rotB_2) {
        Serial.println("B +");
        valueB+=rotB_resolution;
      } else {
        Serial.println("B -");
        valueB-=rotB_resolution;
      }
      valueB = preventOverflow(valueB, 0, 44);
    }
    color(CHSV(0, 0, 0));
    leds[valueA] = CRGB::Red;
  }
}

void readBtn()
{
  currentTime2 = millis();
  if(currentTime2 >= (loopTime2 + 50)) {
    btnA   = digitalRead(ROTAB_PIN);
    btnB   = digitalRead(ROTBB_PIN);
    
    if((!btnA) && (btnA_prev)){
      buttonA = !buttonA;
      Serial.println("A Button Down");
    }
    if((!btnB) && (btnB_prev)){
      buttonB = !buttonB;
      Serial.println("B Button Down");
    }
    
    btnA_prev = btnA;
    btnB_prev = btnB;
    
    loopTime2 = currentTime2;
  }
}

float preventOverflow(float value, float minimum, float maximum) 
{ 
  if(value < minimum) {
    return minimum;
  } else if(value > maximum) {
    return maximum;
  } else {
    return value;
  }
}

float doOverflow(float value, float minimum, float maximum) 
{ 
  float rest;
  if(value > maximum) {
    return (minimum - 1)  + (value - maximum);
  } else if(value < minimum) {
    return (maximum + 1) - (minimum - value);
  } else {
    return value;
  }
}

void loop() 
{
  readRot();
  readBtn();
  EVERY_N_MILLISECONDS( 150 ) { 
    Serial.print("A: ");
    Serial.print(valueA);
    Serial.print(" | ");
    Serial.print("B: ");
    Serial.print(valueB);
    Serial.print(" | ");
    Serial.print("btn A: ");
    Serial.print(buttonA);
    Serial.print(" | ");
    Serial.print("btn B: ");
    Serial.print(buttonB);
    Serial.print(" | ");
    Serial.println();
  }
  
  if(buttonA){
    FastLED.setBrightness(  brightness );
    FastLED.show();
  } else {
    color(CRGB::White);
    color(CHSV(0, 0, 0));
    FastLED.show();
  }
}
