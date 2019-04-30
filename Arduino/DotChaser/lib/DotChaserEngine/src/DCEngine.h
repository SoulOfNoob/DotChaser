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
      int weird                     = 12;
      int fieldSize                 = 0;
      int fieldOffset               = 0;
      int config                    = 0;
      int gameSpeed                 = 1000;
      float speedFactor             = 2.03;
      int speedIndicatorMin         = 9;
      int speedIndicatorMax         = 10;
      int speedIndicator            = 10;
      Player* players[MAX_PLAYERS]  = {nullptr};
      Item* items[MAX_ITEMS]        = {nullptr};
      Game* game;
      CRGB leds[255];

      void drawField();

      /**
       * @param player
       */
      void movePlayer(Player *player);

      void drawPlayers();

      /**
       * @param game
       */
      void addGame(Game *game);

      int playerExists(int id);
      void addPlayer(int id);
      int checkCollision(int id);

      /**
       * @param button
       */
      void buttonPressed(int button);

      void update();

      void render();

      /**
       * @param value
       * @param minimum
       * @param maximum
       */
      float preventOverflow(float value, float minimum, float maximum);

      /**
       * @param value
       * @param minimum
       * @param maximum
       */
      float doOverflow(float value, float minimum, float maximum);

  };

#endif //_DCENGINE_H
