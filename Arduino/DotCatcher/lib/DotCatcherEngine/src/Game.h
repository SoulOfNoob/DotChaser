/**
 * Project DotCatcherEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _GAME_H
#define _GAME_H

#include <Arduino.h>
#include <FastLED.h>
#include <Game.h>
#include <Player.h>
#include <Item.h>

class Game {
public:

/**
 * @param time
 * @param size
 * @param players
 */
Game(double time, int size, Player *players[4]);

/**
 * item collision and player collision
 *
 * @param player
 */
void checkCollision(Player *player);

void update();
private:
   /**
   * remaining time
   * initial time counts down
   */
  double time;
  int fieldSize;
  Player *players[4];
  Item *items[255];
  /**
  * array with all player positions? to check collisions
  */
  int playerField[255];
  /**
  * array with all item positions? to check collisions
  */
  int itemField[255];
};

#endif //_GAME_H
