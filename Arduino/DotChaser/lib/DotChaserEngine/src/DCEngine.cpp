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
  Serial.begin(115200);
  Serial.println("Construct DCEngine");

  fieldOffset           = offset;
  fieldSize             = size;

  Serial.println("--------");
  Serial.println(weird);
  Serial.println(fieldOffset);
  Serial.println(config);
  Serial.println(fieldSize);
  Serial.println("--------");

  FastLED.addLeds<WS2812,4,GRB>(leds, num_leds).setCorrection(TypicalLEDStrip);
}

void DCEngine::addGame(Game *game) {

}

void DCEngine::drawField() {
  FastLED.clear();
  for ( int i = fieldOffset ; i < fieldSize + fieldOffset ; i++ ) {
    leds[i] = CRGB::Red;
  }
}

void DCEngine::drawPlayers() {
  FastLED.clear();
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    if ( players[i] != 0 ) {
      movePlayer(players[i]);
      leds[players[i]->position] = players[i]->color;
      // Serial.print("DrawPlayer: ");
      // Serial.print(i);
      // Serial.print(" Pos: ");
      // Serial.print(players[i]->position);
      // Serial.print(" Color: ");
      // Serial.print(players[i]->color);
      // Serial.println();
    }
  }
}

void DCEngine::update() {
  EVERY_N_MILLISECONDS( 1000 ) {
    speedIndicator--;
    gameSpeed = round(pow(preventOverflow(speedIndicator, speedIndicatorMin, speedIndicatorMax), speedFactor) + 30);
    //Serial.println(gameSpeed);
  }

  EVERY_N_MILLIS_I(thistimer, gameSpeed) {
    if (config == 1) {
      drawField();
    } else {
      drawPlayers();
    }
    render();
  }
  thistimer.setPeriod(gameSpeed);
}

void DCEngine::render() {
  FastLED.setBrightness(5);
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

void DCEngine::movePlayer(Player *player) {
  player->position = doOverflow(player->position + player->direction, fieldOffset, fieldSize - 1 + fieldOffset);
}

int DCEngine::playerExists(int id) {
  Serial.print("playerExists ");
  Serial.println(id);
  if (players[id] == 0 && id < MAX_PLAYERS) {
    return 0;
    Serial.println("0 ");
  } else {
    return 1;
    Serial.println("1 ");
  }
}

void DCEngine::addPlayer(int id) {
  Serial.print("Add Player ");
  Serial.println(id);
  players[id] = new Player();
  players[id]->color = CHSV(random8(),255,255);
  players[id]->position = random(fieldOffset, fieldSize + fieldOffset);
  drawPlayers();
  //Serial.println(players[button]);
}

int DCEngine::checkCollision(int id) {
  Serial.println("check Collision");
  //if collision
  if ( 0 ) {
    return 1;
  } else {
    return 0;
  }
}

void DCEngine::buttonPressed(int id) {
  Serial.print("Button ");
  Serial.print(id);
  Serial.println(" pressed.");

  Serial.println("--------");
  Serial.println(weird);
  Serial.println(fieldOffset);
  Serial.println(config);
  Serial.println(fieldSize);
  Serial.println("--------");

  if (config == 1) {
    if ( id == 1 ) {
      fieldSize--;
    } else if (id == 2) {
      fieldSize++;
    }
    Serial.print(" size: ");
    Serial.println(fieldSize);
  } else {
    if (playerExists(id)) {
      //game.playerButtonPressed(id);
      if (checkCollision(id)) {
        Serial.println("Collision detected!!");
      } else {
        players[id]->changeDirection();
      }
    } else {
      addPlayer(id);
    }
  }
}
