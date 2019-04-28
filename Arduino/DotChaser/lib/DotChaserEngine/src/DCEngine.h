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
      int fieldSize                 = 0;
      int fieldOffset               = 0;
      int gameSpeed                 = 1000;
      bool configmode               = false;
      Game *game                    = {nullptr};
      Player *players[MAX_PLAYERS]  = {nullptr};;
      CRGB leds[255];

      // DATA_PIN, NUM_LEDS, LED_TYPE, COLOR_ORDER, fieldSize, fieldOffset
      DCEngine(int data_pin, int num_leds, int size, int offset, int speed);

      void addGame(Game *game);

      void showField();
      void movePlayer(Player *player);
      void drawPlayers();

      void buttonPressed(int button);

      void update();
      void render();

      float preventOverflow(float value, float minimum, float maximum);
      float doOverflow(float value, float minimum, float maximum);
  };

#endif //_DCENGINE_H
