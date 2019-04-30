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
    Game(Player** players, Item** items);

    void playerButtonPressed(int playerID);
    void update();
  private:
    Player**  _players;
    Item**    _items;
    bool      _checkPlayerCollision(int playerID);
    bool      _checkItemCollision(int playerID);
    void      _doPlayerCollision(Player* player1, Player* player2);
    void      _doItemCollidsion(Player* player, Item* item);
    //int time
  };

#endif //_GAME_H
