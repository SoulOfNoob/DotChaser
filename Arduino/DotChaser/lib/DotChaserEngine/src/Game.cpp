/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "Game.h"

/**
 * Game implementation
 */

Game::Game(Player** players, Item** items, int* fieldSize, int* fieldOffset) {
  _fieldSize          = fieldSize;
  _fieldOffset        = fieldOffset;
  _gameSpeed          = 1000;
  _speedIndicatorMin  = 20;
  _speedIndicatorMax  = 40;
  _speedIndicator     = 20;
  _speedExponent      = 2.03;
  _collisionTolerance = 2;
  _players            = players;
  _items              = items;
}

void Game::playerButtonPressed(int playerID) {
  if (!_checkPlayerCollision(playerID) && !_checkItemCollision(playerID)) {
    _players[playerID]->changeDirection();
  }
}

void Game::update() {

}

void Game::_movePlayers() {
  //int fieldOffset = _fieldOffset;
  //int fieldSize = _fieldSize;
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    Player* player = _players[i];
    if ( player != 0 ) {
      //player->setPosition( _doOverflow( player->getPosition() + player->getDirection(), _fieldOffset, ( _fieldSize - 1 ) + _fieldOffset ) );
    }
  }
}

bool Game::_checkPlayerCollision(int playerID) {
  //check player Collision
  Player* currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    Player* enemyPlayer = _players[i];
    //check if enemyPlayer is not currentPlayer and is not empty
    if ( i != playerID && enemyPlayer != nullptr ) {
      //check player positions
      // i suggest collision at +-1 field
      //if ( currentPlayer->getPosition() == enemyPlayer->getPosition() ) {
      if ( currentPlayer->getPosition() <= enemyPlayer->getPosition() + _collisionTolerance && currentPlayer->getPosition() >= enemyPlayer->getPosition() - _collisionTolerance ) {
        _doPlayerCollision(currentPlayer, enemyPlayer);
        return true;
      }
    }
  }
  return false;
}

bool Game::_checkItemCollision(int playerID) {
  //check item collision
  Player* currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < MAX_ITEMS ; i++ ) {
    Item* item = _items[i];
    //check if item is not empty
    if ( item != 0 ) {
      //check player/item positions
      // i suggest collision at +-1 field
      if ( currentPlayer->getPosition() == item->getPosition() ) {
        _doItemCollision(currentPlayer, item);
        return true;
      }
    }
  }
  return false;
}

void Game::_doPlayerCollision(Player* player1, Player* player2) {
  // explosionseffekt
  Serial.println("Player Collision detected!!");
  //ToDo Getter Setter Methods
  player1->setColor(CRGB::Green);
  player2->setColor(CRGB::Red);
  //do Collision
}

void Game::_doItemCollision(Player* player, Item* item) {
  Serial.println("Item Collision detected!!");
  //do Collision
}

// private helpers
float Game::_preventOverflow(float value, float minimum, float maximum) {
	  if(value < minimum) {
	    return minimum;
	  } else if(value > maximum) {
	    return maximum;
	  } else {
	    return value;
	  }
	}

float Game::_doOverflow(float value, float minimum, float maximum) {
  if(value > maximum) {
    return (minimum - 1)  + (value - maximum);
  } else if(value < minimum) {
    return (maximum + 1) - (minimum - value);
  } else {
    return value;
  }
}
