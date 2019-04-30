/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "Item.h"

/**
 * Item implementation
 */

Item::Item(CRGB color, int position, int value) {
  _color = color;
  _position = position;
  _value = value;
}

// public getters
int Item::getPosition() {
  return _position;
}

int Item::getValue() {
  return _value;
}

CRGB Item::getColor() {
  return _color;
}

// public setters
void Item::setPosition(int position) {
  _position = position;
}

void Item::setValue(int value) {
  _value = value;
}

void Item::setColor(CRGB color) {
  _color = color;
}
