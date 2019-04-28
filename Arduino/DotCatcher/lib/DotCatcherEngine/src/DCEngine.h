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
      bool configmode;
      int fieldSize;
      int fieldOffset;
      Game *game;
      Player *players[MAX_PLAYERS];
      int speed;
      EasyButton *buttons[MAX_PLAYERS];
      CRGB leds[255];

      // DATA_PIN, NUM_LEDS, LED_TYPE, COLOR_ORDER, fieldSize, fieldOffset
      DCEngine(int data_pin, int num_leds, int size, int offset);

      void showField();
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

      float preventOverflow(float value, float minimum, float maximum);
      float doOverflow(float value, float minimum, float maximum);

  };

#endif //_DCENGINE_H
