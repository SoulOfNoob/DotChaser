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
  Serial.println("--------");
  Serial.println("Construct DCEngine");

  _weird             = 666;
  _fieldOffset       = offset;
  _fieldSize         = size;
  _config            = false;
  _gameSpeed         = 1000;
  _speedFactor       = 2.03;
  _speedIndicatorMin = 9;
  _speedIndicatorMax = 10;
  _speedIndicator    = 10;
  _game = new Game(_players, _items);

  _stillWeird();

  FastLED.addLeds<WS2812,4,GRB>(_leds, num_leds).setCorrection(TypicalLEDStrip);
}

// public methods
void DCEngine::addGame(Game *_game) {

}

void DCEngine::buttonPressed(int id) {
  Serial.print("Button ");
  Serial.print(id);
  Serial.println(" pressed.");

  _stillWeird();

  if (_config) {
    if ( id == 1 ) {
      _fieldSize--;
    } else if (id == 2) {
      _fieldSize++;
    }
    Serial.print(" _fieldSize: ");
    Serial.println(_fieldSize);
  } else {
    if (_playerExists(id)) {
      _game->playerButtonPressed(id);
    } else {
      _addPlayer(id);
    }
  }
}

void DCEngine::update() {
  EVERY_N_MILLISECONDS( 1000 ) {
    _speedIndicator--;
    _gameSpeed = round(pow(_preventOverflow(_speedIndicator, _speedIndicatorMin, _speedIndicatorMax), _speedFactor) + 30);
    //Serial.println(gameSpeed);
  }

  EVERY_N_MILLIS_I(thistimer, _gameSpeed) {
    if (_config) {
      _drawField();
    } else {
      _drawPlayers();
    }
    _render();
  }
  thistimer.setPeriod(_gameSpeed);
}

// public setters
void DCEngine::setConfigMode(bool configMode) {

}

// private player methods
void DCEngine::_addPlayer(int id) {
  Serial.print("Add Player ");
  Serial.println(id);
  _players[id] = new Player();
  _players[id]->setColor(CHSV(random8(),255,255));
  _players[id]->setPosition(random(_fieldOffset, _fieldSize + _fieldOffset));
  _drawPlayers();
  //Serial.println(players[button]);
}

bool DCEngine::_playerExists(int id) {
  if (_players[id] == 0 && id < MAX_PLAYERS) {
    return false;
  } else {
    return true;
  }
}

void DCEngine::_movePlayer(Player *player) {
  player->setPosition(_doOverflow(player->getPosition() + player->getDirection(), _fieldOffset, _fieldSize - 1 + _fieldOffset));
}

// private graphic methods
void DCEngine::_render() {
  FastLED.setBrightness(5);
  FastLED.show();
}

void DCEngine::_drawField() {
  FastLED.clear();
  for ( int i = _fieldOffset ; i < _fieldSize + _fieldOffset ; i++ ) {
    _leds[i] = CRGB::Red;
  }
}

void DCEngine::_drawPlayers() {
  FastLED.clear();
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    if ( _players[i] != 0 ) {
      _movePlayer(_players[i]);
      _leds[_players[i]->getPosition()] = _players[i]->getColor();
    }
  }
}

// private helpers
float DCEngine::_preventOverflow(float value, float minimum, float maximum) {
	  if(value < minimum) {
	    return minimum;
	  } else if(value > maximum) {
	    return maximum;
	  } else {
	    return value;
	  }
	}

float DCEngine::_doOverflow(float value, float minimum, float maximum) {
  if(value > maximum) {
    return (minimum - 1)  + (value - maximum);
  } else if(value < minimum) {
    return (maximum + 1) - (minimum - value);
  } else {
    return value;
  }
}

void DCEngine::_stillWeird() {
  Serial.println("--------");
  Serial.print("Still Weird? - ");
  Serial.println(_weird);
  Serial.println("--------");
}
