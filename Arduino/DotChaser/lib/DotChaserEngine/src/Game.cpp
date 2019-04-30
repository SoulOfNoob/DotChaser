/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "Game.h"

/**
 * Game implementation
 */

Game::Game(Player** players, Item** items) {
  _items = items;
  _players = players;
}

void Game::playerButtonPressed(int playerID) {
  if (!_checkPlayerCollision(playerID) && !_checkItemCollision(playerID)) {
    _players[playerID]->changeDirection();
  }
}

void Game::update() {

}

bool Game::_checkPlayerCollision(int playerID) {
  //check player Collision
  Player *currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    Player *enemyPlayer = _players[i];
    //check if enemyPlayer is not currentPlayer and is not empty
    if ( i != playerID && enemyPlayer != nullptr ) {
      //check player positions
      if ( currentPlayer->getPosition() == enemyPlayer->getPosition() ) {
        _doPlayerCollision(currentPlayer, enemyPlayer);
        return true;
      }
    }
  }
  return false;
}

bool Game::_checkItemCollision(int playerID) {
  //check item collision
  Player *currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < MAX_ITEMS ; i++ ) {
    Item *item = _items[i];
    //check if item is not empty
    if ( item != 0 ) {
      //check player/item positions
      if ( currentPlayer->getPosition() == item->getPosition() ) {
        _doItemCollidsion(currentPlayer, item);
        return true;
      }
    }
  }
  return false;
}

void Game::_doPlayerCollision(Player* player1, Player* player2) {
  Serial.println("Player Collision detected!!");
  //ToDo Getter Setter Methods
  player1->setColor(CRGB::Green);
  player2->setColor(CRGB::Red);
  //do Collision
}

void Game::_doItemCollidsion(Player* player, Item* item) {
  Serial.println("Item Collision detected!!");
  //do Collision
}
