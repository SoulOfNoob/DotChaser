/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */

#ifndef _DCENGINE_H
#define _DCENGINE_H

  #define MAX_PLAYERS 4
  #define MAX_ITEMS 64

  #include <Arduino.h>
  #include <FastLED.h>
  #include <EasyButton.h>
  #include <Game.h>
  #include <Player.h>
  #include <Item.h>

  class DCEngine {
    public:
      DCEngine(int data_pin, int num_leds, int size, int offset);

      // public methods
      void    addGame(Game* game);
      void    buttonPressed(int button);
      void    update();

      // public setters
      void    setConfigMode(bool configMode);
    private:
      int     _weird;
      bool    _config;
      int     _fieldSize;
      int     _fieldOffset;
      int     _gameSpeed;         //ToDo: move to Game object
      int     _speedIndicatorMin; //ToDo: move to Game object
      int     _speedIndicatorMax; //ToDo: move to Game object
      int     _speedIndicator;    //ToDo: move to Game object
      float   _speedFactor;       //ToDo: move to Game object
      Player* _players[MAX_PLAYERS] = {nullptr};
      Item*   _items[MAX_ITEMS]     = {nullptr};
      Game*   _game;
      CRGB    _leds[255];

      // private player methods
      void    _addPlayer(int id);
      bool    _playerExists(int id);
      void    _movePlayer(Player *player);

      // private graphic methods
      void    _render();
      void    _drawField();
      void    _drawPlayers();

      // private helpers
      float   _preventOverflow(float value, float minimum, float maximum);
      float   _doOverflow(float value, float minimum, float maximum);
      void    _stillWeird();
  };

#endif //_DCENGINE_H
