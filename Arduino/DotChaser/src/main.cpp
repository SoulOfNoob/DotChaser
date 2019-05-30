#include <Arduino.h>
#include <EasyButton.h>
#include <FastLED.h>
#include <DCEngine.h>

#define LED_PIN     2
#define DATA_PIN    4
#define NUM_LEDS    24

const int fieldOffset = 0;
const int fieldSize = NUM_LEDS - fieldOffset;
const int buttonPins[] = {23, 22, 21};

DCEngine engine(DATA_PIN, NUM_LEDS, fieldSize, fieldOffset);
//DCEngine* engine = new DCEngine(DATA_PIN, NUM_LEDS, fieldSize, fieldOffset);
//DCEngine engine = new DCEngine(DATA_PIN, NUM_LEDS, fieldSize, fieldOffset);

// Instance of the button.
EasyButton *buttons[sizeof(buttonPins)];

// Callback function to be called when the button is pressed.
void onPressed1() { engine.buttonPressed(1); }
void onPressed2() { engine.buttonPressed(2); }
void onPressed3() { engine.buttonPressed(3); }
void onPressed4() { engine.buttonPressed(4); }

typedef void (*callbackList[])();
callbackList callbacks = { onPressed1, onPressed2, onPressed3, onPressed4 };

void setup() {
	// Initialize Serial for debuging purposes.
	//Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  for ( int i = 0 ; i <= sizeof(buttonPins) ; i++ ) {
    // Instance of the button.
    buttons[i] = new EasyButton(buttonPins[i]);
    // Initialize the button.
    buttons[i]->begin();
    // Add the callback function to be called when the button is pressed.
    buttons[i]->onPressed(callbacks[i]);
  }
  Serial.println("Setup OK!");
	//engine.setConfigMode(1);
}

void readButtons() {
	for ( int i = 0 ; i <= sizeof(buttonPins) ; i++ ) {
    buttons[i]->read();
  }
}

void loop() {
  readButtons();
	engine.update();
}
