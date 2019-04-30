/**
 * Project DotChaserEngine
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

      // public getters
      int   getPosition();
      int   getValue();
      CRGB  getColor();

      // public setters
      void  setPosition(int position);
      void  setValue(int value);
      void  setColor(CRGB color);
    private:
      int   _position;
      int   _value;
      CRGB  _color;
  };

#endif //_ITEM_H
