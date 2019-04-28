/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _GAME_H
#define _GAME_H

  #define MAX_PLAYERS 4

  #include <Arduino.h>
  #include <FastLED.h>
  #include <Game.h>
  #include <Player.h>
  #include <Item.h>

  class Game {
  public:
    double time;
    int fieldSize;
    Player *players[MAX_PLAYERS];
    Item *items[255];
    int playerField[255];
    int itemField[255];

  Game(double time, int size, Player *players[MAX_PLAYERS]);

  void checkCollision(Player *player);

  void update();

  };

#endif //_GAME_H
