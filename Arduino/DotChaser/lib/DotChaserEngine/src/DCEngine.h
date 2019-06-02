/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */

#ifndef _DCENGINE_H
#define _DCENGINE_H

  #include <Arduino.h>
  #include <FastLED.h>
  #include <EasyButton.h>
  #include <Game.h>
  #include <Player.h>
  #include <Item.h>
  #include <EEPROM.h>
  //#include <BLEController.h>

  class DCEngine {
    public:
      DCEngine(int data_pin, int num_leds, int fieldSize, int fieldOffset);

      // public methods
      void    addGame(Game* game);
      void    buttonPressed(int button);
      void    update();

      // public setters
      void    setConfigMode(bool configMode);
      void    setFieldSize(int fieldSize);
      void    setFieldOffset(int fieldOffset);
      void    setBrightness(int brightness);
    private:
      int     _weird;
      static const int _maxPlayers = 2;
      static const int _maxItems = 15;
      int     _num_leds;
      int     _configMode;
      int     _fieldSize;
      int     _fieldOffset;
      int     _brightness;
      int     _gameSpeed;         //ToDo: move to Game object
      int     _speedIndicatorMin; //ToDo: move to Game object
      int     _speedIndicatorMax; //ToDo: move to Game object
      int     _speedIndicator;    //ToDo: move to Game object
      float   _speedExponent;     //ToDo: move to Game object
      int     _collisionTolerance;
      Player* _players[_maxPlayers] = {nullptr};
      Item*   _items[_maxItems]     = {nullptr};
      int     _itemCount;
      Game*   _game;
      CRGB    _leds[255];

      // private methods
      void    _doConfig(int id);

      // private player methods
      void    _addPlayer(int id);
      void    _addItem(int id);
      bool    _playerExists(int id);
      void    _movePlayers();

      // private graphic methods
      void    _drawField();
      void    _drawPlayers();
      void    _drawItems();
      void    _drawTrace(int position, CRGB color);
      void    _drawWave(int position, int velocity, CRGB color);
      void    _render();

      // private helpers
      bool    _checkPlayerCollision(int playerID);
      bool    _checkItemCollision(int playerID);
      void    _doPlayerCollision(Player* player1, Player* player2);
      void    _doItemCollision(Player* player, Item* item);
      float   _preventOverflow(float value, float minimum, float maximum);
      float   _doOverflow(float value, float minimum, float maximum);
      void    _stillWeird();
  };

#endif //_DCENGINE_H
