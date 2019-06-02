#include <Arduino.h>
#include <EasyButton.h>
#include <FastLED.h>
#include <DCEngine.h>
#include <BLEController.h>

#define DATA_PIN    12
#define NUM_LEDS    24

const byte interruptPins[3] = {32, 27, 13};

const int fieldOffset = 0;
const int fieldSize = NUM_LEDS - fieldOffset;
volatile unsigned int debounceDelay = 200;

volatile unsigned int bounceTimers[3] = {0, 0, 0};
volatile int interruptCounters[3] = {0, 0, 0};
int numberOfInterrupts[3] = {0, 0, 0};

DCEngine engine(DATA_PIN, NUM_LEDS, fieldSize, fieldOffset);

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR ISR_Button_1() {
  if(millis() - bounceTimers[0] > debounceDelay){
    portENTER_CRITICAL_ISR(&mux);
    interruptCounters[0]++;
    portEXIT_CRITICAL_ISR(&mux);
  }
  bounceTimers[0] = millis();
}

void IRAM_ATTR ISR_Button_2() {
  if(millis() - bounceTimers[1] > debounceDelay){
    portENTER_CRITICAL_ISR(&mux);
    interruptCounters[1]++;
    portEXIT_CRITICAL_ISR(&mux);
  }
  bounceTimers[1] = millis();
}

void IRAM_ATTR ISR_Button_3() {
  if(millis() - bounceTimers[2] > debounceDelay){
    portENTER_CRITICAL_ISR(&mux);
    interruptCounters[2]++;
    portEXIT_CRITICAL_ISR(&mux);
  }
  bounceTimers[2] = millis();
}

typedef void (*ISRList[])();
ISRList ISRs = { ISR_Button_1, ISR_Button_2, ISR_Button_3 };

static void buttonCB(int i) { engine.buttonPressed(i); }

void setup() {
  Serial.println("Start Setup");
  for( int i = 0 ; i < sizeof(interruptPins) ; i++ ) {
    pinMode(interruptPins[i], INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPins[i]), ISRs[i], FALLING);
  }

  EEPROM.begin(5);

  int eeprom = EEPROM.read(1);
  if(eeprom != 0) {
    Serial.print("Reading _brightness: ");
    Serial.print(eeprom);
    Serial.println(" from EEPROM");
    engine.setBrightness(eeprom);
  }
  eeprom = EEPROM.read(2);
  if(eeprom != 0) {
    Serial.print("Reading _fieldOffset: ");
    Serial.print(eeprom);
    Serial.println(" from EEPROM");
    engine.setFieldOffset(eeprom);
  }
  eeprom = EEPROM.read(3);
  if(eeprom != 0) {
    Serial.print("Reading _fieldSize: ");
    Serial.print(eeprom);
    Serial.println(" from EEPROM");
    engine.setFieldSize(eeprom);
  }

  BLEDevice::init("ESP32");

  BLEController::init(buttonCB);

  Serial.println("Setup OK!");
	//engine.setConfigMode(1);
}

void loop() {
  BLEController::loop();
	engine.update();

  for( int i = 0 ; i < sizeof(interruptPins) ; i++ ) {
      if(interruptCounters[i]>0){
        portENTER_CRITICAL(&mux);
        interruptCounters[i]--;
        portEXIT_CRITICAL(&mux);

        numberOfInterrupts[i]++;
        Serial.print("Interrupt ");
        Serial.print(i);
        Serial.print(" has occurred. Total: ");
        Serial.println(numberOfInterrupts[i]);
        engine.buttonPressed(i+3);
      }
    }
}
