#include <Arduino.h>
#include <EasyButton.h>
#include <FastLED.h>
#include <Player.h>
#include <Item.h>
#include <Game.h>
#include <DotChaserEngine.h>

// Arduino pin where the button is connected to.
#define BUTTON1_PIN 23
#define BUTTON2_PIN 22
#define LED_PIN 2

int ledState = HIGH;

// Instance of the button.
EasyButton button1(BUTTON1_PIN);
EasyButton button2(BUTTON2_PIN);
// Callback function to be called when the button is pressed.
void onPressed1() {
	Serial.println("Button1 has been pressed!");
  ledState = !ledState;
}
void onPressed2() {
	Serial.println("Button2 has been pressed!");
  ledState = !ledState;
}

void setup() {
	// Initialize Serial for debuging purposes.
	Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  digitalWrite(LED_PIN, ledState);
	// Initialize the button.
	button1.begin();
  button2.begin();
	// Add the callback function to be called when the button is pressed.
	button1.onPressed(onPressed1);
  button2.onPressed(onPressed2);
}

void loop() {
	// Continuously read the status of the button.
	button1.read();
  button2.read();
  //Serial.println(digitalRead(BUTTON_PIN));
  //Serial.println(digitalRead(22));
  digitalWrite(LED_PIN, ledState);
}
