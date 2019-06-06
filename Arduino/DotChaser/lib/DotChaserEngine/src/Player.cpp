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
  _winner      = false;
  _looser      = false;
}

void Player::changeDirection() {
  _direction = _direction * -1;
}

void Player::addItem(Item* item) {
  if( _itemCount < _maxItems ) {
    _items[_itemCount] = item;
    _items[_itemCount]->setCollected();
    _itemCount++;
  }
}

Item* Player::removeLastItem() {
  if ( _itemCount > 1 ) {
    Serial.print("Removing item: ");
    Serial.print(_itemCount-1);
    Item* returnedItem = _items[_itemCount-1];
    Serial.println(" ... Deleted");
    _itemCount--;
    return returnedItem;
  } else {
    return nullptr;
  }
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

bool Player::getWinner() {
  return _winner;
}

bool Player::getLooser() {
  return _looser;
}

// public setters
void Player::setPosition(int position) {
  _position = position;
}

void Player::setColor(CRGB color) {
  _color = color;
}

void Player::setWinner() {
  _winner = true;
  _looser = false;
}

void Player::setLooser() {
  _looser = true;
  _winner = false;
}
