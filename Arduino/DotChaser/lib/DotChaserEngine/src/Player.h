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

  class Player {
    public:
      Player();

      // public methods
      void  changeDirection();
      void  addItem(Item* item);
      Item* removeLastItem();

      // public getters
      int    getPosition();
      int    getDirection();
      int    getLength();
      int    getBrightness();
      int    getPoints();
      CRGB   getColor();
      Item** getItems();
      int    getItemCount();
      bool   getWinner();
      bool   getLooser();

      // public setters
      void   setPosition(int position);
      void   setColor(CRGB color);
      void   setWinner();
      void   setLooser();

    private:
      int    _position;
      int    _direction;
      int    _length;
      int    _brightness;
      int    _points;
      CRGB   _color;
      static const int _maxItems = 255;
      Item*  _items[_maxItems];
      int    _itemCount;
      bool   _winner;
      bool   _looser;

  };

#endif //_PLAYER_H
