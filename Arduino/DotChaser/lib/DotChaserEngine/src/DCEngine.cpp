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
  _num_leds          = num_leds;
  _fieldSize         = fieldSize;
  _fieldOffset       = fieldOffset;
  _brightness        = 128;
  _configMode        = 0;
  _gameSpeed         = 100;
  _speedIndicatorMin = 20;
  _speedIndicatorMax = 40;
  _speedIndicator    = 20;
  _speedExponent     = 2.03;
  _collisionTolerance= 1;
  _itemCount         = 0;

  _game = new Game(_players, _items, &_fieldSize, &_fieldOffset);

  //_stillWeird();

  FastLED.addLeds<WS2812,12,GRB>(_leds, num_leds).setCorrection(TypicalLEDStrip);
}

// public methods
void DCEngine::addGame(Game *_game) {

}

void DCEngine::buttonPressed(int id) {
  Serial.print("Button ");
  Serial.print(id);
  Serial.println(" pressed.");

  //_stillWeird();

  //_drawWave(20, 10, CRGB::Red);
  if( id == 3 ) {
    _configMode = _doOverflow(_configMode + 1, 0, 3);
    Serial.print(" _configMode: ");
    Serial.println(_configMode);
  }
  if (_configMode > 0) {
    _doConfig(id);
  } else if( id < 3 ) {
    Serial.println("Check for existence");
    if (_playerExists(id)) {
      Serial.println("exists");
      //_game->playerButtonPressed(id);
      if (!_checkPlayerCollision(id) && !_checkItemCollision(id)) {
        Serial.println("no collision");
        _players[id]->changeDirection();
      }
    } else {
      Serial.println("adding");
      _addPlayer(id);
    }
  }
}

void DCEngine::update() {
  // speedup
  // EVERY_N_MILLISECONDS( 3000 ) {
  //   _speedIndicator--;
  //   _gameSpeed = round(pow(_preventOverflow(_speedIndicator, _speedIndicatorMin, _speedIndicatorMax), _speedExponent) + 30);
  //   Serial.println(_gameSpeed);
  // }

  // Spawn item
  EVERY_N_MILLISECONDS( 2000 ) {
    if(_itemCount < _maxItems) {
      _addItem(_itemCount);
      _itemCount++;
      Serial.print("Itemcount is now: ");
      Serial.println(_itemCount);
    }

  }

  EVERY_N_MILLIS_I(thistimer, _gameSpeed) {
    // move player with game speed
    _movePlayers();
  }
  thistimer.setPeriod(_gameSpeed);

  // but render player as fast as possible
  FastLED.clear();
  if ( _configMode > 0 ) {
    _drawField();
  } else {
    _drawItems();
    _drawPlayers();
  }
  _render();
}

// public setters
void DCEngine::setConfigMode(bool configMode) {
  _configMode = configMode;
}
void DCEngine::setFieldSize(int fieldSize) {
  _fieldSize = fieldSize;
}
void DCEngine::setFieldOffset(int fieldOffset) {
  _fieldOffset = fieldOffset;
}
void DCEngine::setBrightness(int brightness) {
  _brightness = brightness;
}

// private methods
void DCEngine::_doConfig(int id) {
  if (_configMode == 1) {
    if ( id == 4 ) {
      _brightness = _doOverflow(_brightness + 8, 0, 255);
    } else if ( id == 5 ) {
      _brightness = _doOverflow(_brightness - 8, 0, 255);
    }
    Serial.print(" _brightness: ");
    Serial.println(_brightness);
    EEPROM.write(1, _brightness);
    EEPROM.commit();
  } else if (_configMode == 2) {
    if ( id == 4 ) {
      _fieldOffset++;
    } else if ( id == 5 ) {
      _fieldOffset--;
    }
    Serial.print(" _fieldOffset: ");
    Serial.println(_fieldOffset);
    EEPROM.write(2, _fieldOffset);
    EEPROM.commit();
  } else if (_configMode == 3) {
    if ( id == 4 ) {
      _fieldSize = _doOverflow(_fieldSize + 1, 0, _num_leds);
    } else if (id == 5 ) {
      _fieldSize = _doOverflow(_fieldSize - 1, 0, _num_leds);
    }
    Serial.print(" _fieldSize: ");
    Serial.println(_fieldSize);
    EEPROM.write(3, _fieldSize);
    EEPROM.commit();
  }
}

void DCEngine::_addItem(int id) {
  Serial.print("Add Item ");
  Serial.print(id);
  _items[id] = new Item();
  _items[id]->setColor(CHSV(random8(),255,255));
  _items[id]->setPosition(random(_fieldOffset, _fieldSize + _fieldOffset));
  Serial.print(" Position ");
  Serial.println(_items[id]->getPosition());
  _drawItems();
  //Serial.println(players[button]);
}

// private player methods
void DCEngine::_addPlayer(int id) {
  Serial.print("Add Player ");
  Serial.println(id);
  _players[id] = new Player();
  if(id == 0){
    _players[id]->setColor(CRGB::Red);
  } else if (id == 1) {
    _players[id]->setColor(CRGB::Blue);
  }
  _players[id]->setPosition(random(_fieldOffset, _fieldSize + _fieldOffset));
  _drawPlayers();
  //Serial.println(players[button]);
}

bool DCEngine::_playerExists(int id) {
  if (_players[id] == 0 && id < _maxPlayers) {
    return false;
  } else {
    return true;
  }
}

void DCEngine::_movePlayers() {
  for ( int i = 0 ; i < _maxPlayers ; i++ ) {
    Player* player = _players[i];
    if ( player != 0 ) {
      int newPosition = _doOverflow(player->getPosition() + player->getDirection(), _fieldOffset, _fieldSize - 1 + _fieldOffset);
      player->setPosition(newPosition);
      // move items
      Item** items = player->getItems();
      // Serial.print("Moving ");
      // Serial.print(player->getItemCount());
      // Serial.print(" Items Belonging to: Player");
      // Serial.println(i);

      for( int b = 0 ; b < player->getItemCount() ; b++ ) {
        Item* item = items[b];
        if (item->getCollected()) {
          int newItemPosition = _doOverflow(player->getPosition() - ((b+1) * player->getDirection()), _fieldOffset, _fieldSize - 1 + _fieldOffset);
          item->setPosition(newItemPosition);
        }
      }
    }
  }
}

// private graphic methods
void DCEngine::_drawField() {
  for ( int i = _fieldOffset ; i < _fieldSize + _fieldOffset ; i++ ) {
    _leds[i] = CRGB::Red;
  }
}

void DCEngine::_drawPlayers() {
  for ( int i = 0 ; i < _maxPlayers ; i++ ) {
    Player* player = _players[i];
    if ( player != nullptr ) {
      _leds[player->getPosition()] = player->getColor();
      // Draw Player Items
      Item** items = player->getItems();
      for( int b = 0 ; b < player->getItemCount() ; b++ ) {
        Item* item = items[b];
        if (item->getCollected()) {
          _leds[item->getPosition()] = item->getColor();
        }
      }
    }
  }
}

void DCEngine::_drawItems() {
  for ( int i = 0 ; i < _itemCount ; i++ ) {
    if ( _items[i] != 0 && !_items[i]->getCollected() ) {
    //if ( _items[i] != nullptr ) {
      _leds[_items[i]->getPosition()] = _items[i]->getColor();
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
    _drawTrace( position + i, color );
    _drawTrace( position - i, color );
    //_leds[position] = color;
    FastLED.show();
    delay(50);
  }
}

void DCEngine::_render() {
  FastLED.setBrightness(_brightness);
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

bool DCEngine::_checkPlayerCollision(int playerID) {
  //check player Collision
  Serial.println("check player Collision");
  Serial.print("ID: ");
  Serial.println(playerID);
  Player* currentPlayer = _players[playerID];
  //iterate players
  Serial.println("iterate players");
  for ( int i = 0 ; i < _maxPlayers ; i++ ) {
    Serial.print("check player ");
    Serial.println(i);
    Player* enemyPlayer = _players[i];
    //check if enemyPlayer is not currentPlayer and is not empty
    if ( i != playerID && enemyPlayer != nullptr ) {
      Serial.println("is enemy player");
      //check player positions
      // i suggest collision at +-1 field
      //if ( currentPlayer->getPosition() == enemyPlayer->getPosition() ) {
      if ( currentPlayer->getPosition() <= enemyPlayer->getPosition() + _collisionTolerance && currentPlayer->getPosition() >= enemyPlayer->getPosition() - _collisionTolerance ) {
        _doPlayerCollision(currentPlayer, enemyPlayer);
        return true;
      }
    } else {
      Serial.println("is not enemy player");
    }
  }
  return false;
}

bool DCEngine::_checkItemCollision(int playerID) {
  //check item collision
  Serial.println("check item Collision");
  Player* currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < _itemCount ; i++ ) {
    Item* item = _items[i];
    //check if item is not empty
    if ( item != nullptr ) {
      //check player/item positions
      // i suggest collision at +-1 field
      if ( !item->getCollected() && ( currentPlayer->getPosition() <= item->getPosition() + _collisionTolerance && currentPlayer->getPosition() >= item->getPosition() - _collisionTolerance ) ) {
        _doItemCollision(currentPlayer, item);
        return true;
      }
    }
  }
  return false;
}

void DCEngine::_doPlayerCollision(Player* player1, Player* player2) {
  // explosionseffekt
  Serial.println("Player Collision detected!!");
  //ToDo Getter Setter Methods
  player1->setColor(CRGB::Green);
  player2->setColor(CRGB::Red);
  //do Collision
}

void DCEngine::_doItemCollision(Player* player, Item* item) {
  Serial.println("Item Collision detected!!");
  player->addItem(item);
  //do Collision
}

void DCEngine::_stillWeird() {
  Serial.println("--------");
  Serial.print("Still Weird? - ");
  Serial.println(_weird);
  Serial.println("--------");
}
