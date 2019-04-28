/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _PLAYER_H
#define _PLAYER_H

  #include <Arduino.h>
  #include <FastLED.h>
  #include <Item.h>
  #include <EasyButton.h>

  class Player {
    public:
      CRGB color;
      int position;
      int direction;
      int length;
      int brightness;
      int points;
      Item *items[255];

      Player();

      void changeDirection();
  };

#endif //_PLAYER_H
