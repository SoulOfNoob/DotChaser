/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _PLAYER_H
#define _PLAYER_H

  #define MAX_PLAYERS 2
  #define MAX_ITEMS 64

  #include <Arduino.h>
  #include <FastLED.h>
  #include <Item.h>

  class Player {
    public:
      Player();

      // public methods
      void  changeDirection();
      void  addItem(Item* item);

      // public getters
      int    getPosition();
      int    getDirection();
      int    getLength();
      int    getBrightness();
      int    getPoints();
      CRGB   getColor();
      Item** getItems();
      int    getItemCount();

      // public setters
      void   setPosition(int position);
      void   setColor(CRGB color);

    private:
      int    _position;
      int    _direction;
      int    _length;
      int    _brightness;
      int    _points;
      CRGB   _color;
      Item*  _items[MAX_ITEMS];
      int    _itemCount;

  };

#endif //_PLAYER_H
