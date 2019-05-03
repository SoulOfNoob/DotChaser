/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "DCEngine.h"

/**
 * DCEngine implementation
 */

DCEngine::DCEngine(int data_pin, int num_leds, int fieldSize, int fieldOffset) {
  Serial.begin(115200);
  Serial.println("--------");
  Serial.println("Construct DCEngine");

  _weird             = 666;
  _fieldSize         = fieldSize;
  _fieldOffset       = fieldOffset;
  _config            = 0;
  _gameSpeed         = 400;
  _speedIndicatorMin = 20;
  _speedIndicatorMax = 40;
  _speedIndicator    = 20;
  _speedExponent     = 2.03;

  _game = new Game(_players, _items, &_fieldSize, &_fieldOffset);

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

  //_drawWave(20, 10, CRGB::Red);
  if( id == 3 ) {
    _config = _doOverflow(_config + 1, 0, 2);
    Serial.print(" _config: ");
    Serial.println(_config);
  }
  if (_config == 1) {
    if ( id == 1 ) {
      _fieldSize--;
    } else if (id == 2) {
      _fieldSize++;
    }
    Serial.print(" _fieldSize: ");
    Serial.println(_fieldSize);
  } else if (_config == 2) {
    if ( id == 1 ) {
      _fieldOffset--;
    } else if (id == 2) {
      _fieldOffset++;
    }
    Serial.print(" _fieldOffset: ");
    Serial.println(_fieldOffset);
  } else if ( id != 3 ) {
    if (_playerExists(id)) {
      _game->playerButtonPressed(id);
    } else {
      _addPlayer(id);
    }
  }
}

void DCEngine::update() {
  // speedup
  // EVERY_N_MILLISECONDS( 1000 ) {
  //   _speedIndicator--;
  //   _gameSpeed = round(pow(_preventOverflow(_speedIndicator, _speedIndicatorMin, _speedIndicatorMax), _speedExponent) + 30);
  //   Serial.println(_gameSpeed);
  // }

  EVERY_N_MILLIS_I(thistimer, _gameSpeed) {
    // move player with game speed
    _movePlayers();
  }
  thistimer.setPeriod(_gameSpeed);

  // but render player as fast as possible
  if ( _config > 0 ) {
    _drawField();
  } else {
    _drawPlayers();
  }
  _render();
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

void DCEngine::_movePlayers() {
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    if ( _players[i] != 0 ) {
      _players[i]->setPosition(_doOverflow(_players[i]->getPosition() + _players[i]->getDirection(), _fieldOffset, _fieldSize - 1 + _fieldOffset));
    }
  }
}

// private graphic methods
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
      _leds[_players[i]->getPosition()] = _players[i]->getColor();
    }
  }
}

void DCEngine::_drawTrace(int position, CRGB color) {
  //CHSV color(1, 255, 255);
  _leds[position]     = color;
  _leds[position].fadeLightBy( 150 );

  for ( int i = 1 ; i < 4 ; i++ ) {
    _leds[position - i] = color;
    _leds[position - i].fadeLightBy( 150 + (25 * i) );
    _leds[position + i] = color;
    _leds[position + i].fadeLightBy( 150 + (25 * i) );
  }
}

void DCEngine::_drawWave(int position, int velocity, CRGB color) {
  for ( int i = 0 ; i < 6 ; i++ ) {
    FastLED.clear();
    _drawTrace( position + i, color );
    _drawTrace( position - i, color );
    //_leds[position] = color;
    FastLED.show();
    delay(50);
  }
}

void DCEngine::_render() {
  FastLED.setBrightness(20);
  FastLED.show();
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
