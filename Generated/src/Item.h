/**
 * Project DotChaserEngine
 * @author Jan Ryklikas
 * @version 0.1
 */


#ifndef _ITEM_H
#define _ITEM_H

class Item {
public: 
    CRGB color;
    int position;
    int value;
    
/**
 * @param color
 * @param position
 * @param value
 */
void Item(CRGB color, int position, int value);
};

#endif //_ITEM_H