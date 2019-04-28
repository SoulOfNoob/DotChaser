/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _PLAYER_H
#define _PLAYER_H

class Player {
public: 
    CRGB color;
    int position;
    /**
 * 1 right
 * -1 left
 * 0 stationary
 */
int direction;
    int length;
    int brightness;
    int points;
    Item items[16];
    
/**
 * @param position
 * @param button
 */
void Player(int position, EasyButton button);
    
void changeDirection();
};

#endif //_PLAYER_H