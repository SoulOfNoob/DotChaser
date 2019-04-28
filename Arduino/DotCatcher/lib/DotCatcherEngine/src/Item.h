/**
 * Project DotCatcherEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _ITEM_H
#define _ITEM_H

  #include <Arduino.h>
  #include <FastLED.h>

  class Item {
    public:

      Item(CRGB color, int position, int value);

      void getColor();

      void getPosition();

      void getValue();
    private:
      CRGB color;
      int position;
      int value;
  };

#endif //_ITEM_H
