/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "DCEngine.h"

/**
 * DCEngine implementation
 */
DCEngine::DCEngine(int data_pin, int num_leds, int size, int offset) {
  fieldOffset           = offset;
  fieldSize             = size;
  configmode            = false;
  players[MAX_PLAYERS]  = {nullptr};
  buttons[MAX_PLAYERS]  = {nullptr};
  game                  = {nullptr};

  FastLED.addLeds<WS2812,4,GRB>(leds, num_leds).setCorrection(TypicalLEDStrip);
}

/**
 * @param button
 */
void DCEngine::addButton(EasyButton *button) {

}

/**
 * @param player
 */
void DCEngine::addPlayer(Player *player) {

}

/**
 * @param game
 */
void DCEngine::addGame(Game *game) {

}

void DCEngine::showField() {
  FastLED.clear();
  for ( int i = fieldOffset ; i < fieldSize + fieldOffset ; i++ ) {
    leds[i] = CRGB::Red;
  }
}

void DCEngine::movePlayer(Player *player) {
  player->position = doOverflow(player->position + player->direction, fieldOffset, fieldSize + fieldOffset);
}

void DCEngine::drawPlayers() {
  FastLED.clear();
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    if ( players[i] != 0 ) {

      movePlayer(players[i]);

      Serial.print("DrawPlayer: ");
      Serial.print(i);
      Serial.print(" Pos: ");
      Serial.print(players[i]->position);
      Serial.print(" Color: ");
      Serial.print(players[i]->color);
      Serial.println();

      leds[players[i]->position] = players[i]->color;
    }
  }
}

void DCEngine::buttonPressed(int button) {
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  Serial.print("Button ");
  Serial.print(button);
  Serial.println(" pressed.");

  if (players[button] == 0 && button < MAX_PLAYERS) {
    Serial.print("Add Player ");
    Serial.println(button);
    players[button] = new Player();
    players[button]->color = CHSV(random8(),255,255);
    players[button]->position = random(fieldOffset, fieldSize + fieldOffset);
    //Serial.println(players[button]);
  } else {
    Serial.println("check Collision");
    //if collision
    if ( false ) {

    } else {
      players[button]->changeDirection();
    }
  }

  drawPlayers();
}

void DCEngine::update() {
  //if (configmode) showField();
  drawPlayers();
  render();
}

void DCEngine::render() {
  FastLED.setBrightness(20);
  FastLED.show();
}


float DCEngine::preventOverflow(float value, float minimum, float maximum)
	{
	  if(value < minimum) {
	    return minimum;
	  } else if(value > maximum) {
	    return maximum;
	  } else {
	    return value;
	  }
	}

float DCEngine::doOverflow(float value, float minimum, float maximum)
{
  if(value > maximum) {
    return (minimum - 1)  + (value - maximum);
  } else if(value < minimum) {
    return (maximum + 1) - (minimum - value);
  } else {
    return value;
  }
}