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
  if (checkPlayerCollision(playerID)) {
    Serial.println("Player Collision detected!!");
  } else if (checkItemCollision(playerID)) {
    Serial.println("Item Collision detected!!");
  } else {
    _players[playerID]->changeDirection();
  }
}

bool Game::checkPlayerCollision(int playerID) {
  //check player Collision
  Player *currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
    Player *enemyPlayer = _players[i];
    //check if enemyPlayer is not currentPlayer and is not empty
    if ( i != playerID && enemyPlayer != nullptr ) {
      //check player positions
      if ( currentPlayer->position == enemyPlayer->position ) {
        return true;
      }
    }
  }
  return false;
}

bool Game::checkItemCollision(int playerID) {
  //check item collision
  Player *currentPlayer = _players[playerID];
  //iterate players
  for ( int i = 0 ; i < MAX_ITEMS ; i++ ) {
    Item *item = _items[i];
    //check if item is not empty
    if ( item != 0 ) {
      //check player/item positions
      if ( currentPlayer->position == item->position ) {
        return true;
      }
    }
  }
  return false;
}

void Game::update() {

}


void Game::_playerCollide(int player1ID, int player2ID) {

}

void Game::_itemCollide(int playerID, int itemID) {

}
