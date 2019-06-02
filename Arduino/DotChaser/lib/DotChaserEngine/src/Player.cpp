/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "Player.h"

Player::Player() {
  _direction   = 1;
  _length      = 1;
  _brightness  = 32;
  _points      = 0;
  _itemCount   = 0;
}

void Player::changeDirection() {
  _direction = _direction * -1;
}

void Player::addItem(Item* item) {
  _items[_itemCount] = item;
  _items[_itemCount]->setCollected();
  _itemCount++;
}

// public getters
int Player::getPosition() {
  return _position;
}

int Player::getDirection() {
  return _direction;
}

int Player::getLength() {
  return _length;
}

int Player::getBrightness() {
  return _brightness;
}

int Player::getPoints() {
  return _points;
}

CRGB Player::getColor() {
  return _color;
}

Item** Player::getItems() {
  return _items;
}

int Player::getItemCount() {
  return _itemCount;
}
// public setters
void Player::setPosition(int position) {
  _position = position;
}

void Player::setColor(CRGB color) {
  _color = color;
}
