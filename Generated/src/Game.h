/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _GAME_H
#define _GAME_H

class Game {
public: 
    /**
 * remaining time
 * initial time counts down
 */
double time;
    int fieldSize;
    Player players[MAX_PLAYERS];
    Item items[128];
    /**
 * array with all player positions? to check collisions
 */
int playerField[128];
    /**
 * array with all item positions? to check collisions
 */
int itemField[128];
    
/**
 * @param time
 * @param size
 * @param players[MAX_PLAYERS]
 */
void Game(double time, int size, Player players[MAX_PLAYERS]);
    
/**
 * item collision and player collision
 * 
 * @param player
 */
void checkCollision(Player player);
    
void update();
};

#endif //_GAME_H