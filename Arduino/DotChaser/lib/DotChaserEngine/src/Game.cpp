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
  if (!checkPlayerCollision(playerID) && !checkItemCollision(playerID)) {
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
        _playerCollide(currentPlayer, enemyPlayer);
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
        _itemCollide(currentPlayer, item);
        return true;
      }
    }
  }
  return false;
}

void Game::update() {

}

void Game::_playerCollide(Player* player1, Player* player2) {
  Serial.println("Player Collision detected!!");
  //ToDo Getter Setter Methods
  player1->color = CRGB::Green;
  player2->color = CRGB::Red;
  //do Collision
}

void Game::_itemCollide(Player* player, Item* item) {
  Serial.println("Item Collision detected!!");
  //do Collision
}
