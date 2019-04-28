/**
 * Project DCEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _DCENGINE_H
#define _DCENGINE_H

  #define MAX_PLAYERS 4

  #include <Arduino.h>
  #include <FastLED.h>
  #include <EasyButton.h>
  #include <Game.h>
  #include <Player.h>

  class DCEngine {
    public:
      bool configmode                  = false;
      int fieldSize                    = 0;
      int fieldOffset                  = 0;
      int gameSpeed                    = 1000;
      Game *game                       = {nullptr};
      Player *players[MAX_PLAYERS]     = {nullptr};
      EasyButton *buttons[MAX_PLAYERS] = {nullptr};
      CRGB leds[255];

      /**
       * @param data_pin
       * @param num_leds
       * @param size
       * @param offset
       */
      DCEngine(int data_pin, int num_leds, int size, int offset);

      void showField();

      /**
       * @param player
       */
      void movePlayer(Player *player);

      void drawPlayers();

      /**
       * @param button
       */
      void addButton(EasyButton *button);

      /**
       * @param player
       */
      void addPlayer(Player *player);

      /**
       * @param game
       */
      void addGame(Game *game);

      void buttonPressed(int button);

      /**
       * call in loop
       */
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
