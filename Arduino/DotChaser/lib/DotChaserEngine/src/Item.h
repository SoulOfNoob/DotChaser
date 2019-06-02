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
      Item();

      // public getters
      int   getPosition();
      int   getValue();
      CRGB  getColor();
      bool  getCollected();

      // public setters
      void  setPosition(int position);
      void  setValue(int value);
      void  setColor(CRGB color);
      void  setCollected();
    private:
      int   _position;
      int   _value;
      CRGB  _color;
      bool  _collected;
  };

#endif //_ITEM_H
