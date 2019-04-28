/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#include "Player.h"

Player::Player() {
  direction   = 1;
  length      = 1;
  brightness  = 32;
  points      = 0;
}

void Player::changeDirection() {
  direction = direction * -1;
}
