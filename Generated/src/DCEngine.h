/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _DCENGINE_H
#define _DCENGINE_H

class DCEngine {
public: 
    int fieldSize;
    int fieldOffset;
    int gameSpeed;
    bool configmode;
    Game game;
    Player players[MAX_PLAYERS];
    CRGB leds[255];
    
/**
 * @param data_pin
 * @param num_leds
 * @param size
 * @param offset
 */
void DotChaserEngine(int data_pin, int num_leds, int size, int offset);
    
/**
 * @param game
 */
void addGame(Game game);
    
void showField();
    
/**
 * @param player
 */
void movePlayer(Player player);
    
void drawPlayers();
    
/**
 * @param button
 */
void buttonPressed(int button);
    
/**
 * call in loop
 */
void update();
    
void render();
    
/**
 * @param value
 * @param minimum
 * @param maximum
 */
float preventOverflow(float value, float minimum, float maximum);
    
/**
 * @param value
 * @param minimum
 * @param maximum
 */
float doOverflow(float value, float minimum, float maximum);
};

#endif //_DCENGINE_H