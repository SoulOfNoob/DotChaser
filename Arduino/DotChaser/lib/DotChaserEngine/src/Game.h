/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _GAME_H
#define _GAME_H

  #define MAX_PLAYERS 4
  #define MAX_ITEMS 64

  #include <Arduino.h>
  #include <FastLED.h>
  #include <Game.h>
  #include <Player.h>
  #include <Item.h>

  /**
  Checkcollision
  Array mit spielern
  Array mit items

  Check player position
  Compare with all player positions

  Check player position
  Check with all item positions

  Game object gets time as input from engine
  Game changes speed step in engine
  Game checks collision
  Game generates items
  Game only changes item/player attributes
  Engine just renders item
  And player objects

  **/

  class Game {
  public:
    Game(Player** players, Item** items, int* fieldSize, int* fieldOffset);

    void playerButtonPressed(int playerID);
    void update();
  private:
    int*      _fieldSize;
    int*      _fieldOffset;
    int       _gameSpeed;         //ToDo: move to Game object
    int       _speedIndicatorMin; //ToDo: move to Game object
    int       _speedIndicatorMax; //ToDo: move to Game object
    int       _speedIndicator;    //ToDo: move to Game object
    float     _speedExponent;     //ToDo: move to Game object
    int       _collisionTolerance;
    Player**  _players;
    Item**    _items;

    void      _movePlayers();
    bool      _checkPlayerCollision(int playerID);
    bool      _checkItemCollision(int playerID);
    void      _doPlayerCollision(Player* player1, Player* player2);
    void      _doItemCollision(Player* player, Item* item);

    // private helpers
    float     _preventOverflow(float value, float minimum, float maximum);
    float     _doOverflow(float value, float minimum, float maximum);
    //int time
  };

#endif //_GAME_H
