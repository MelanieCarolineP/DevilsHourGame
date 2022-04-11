
#include "entity.h"

/**
 * @brief Entity constructor
 * 
 * @param x x- cordinate
 * @param y y-cordinate
 * @param w width dimension
 * @param h height dimension
 * @return Entity object
 */
Entity :: Entity( float x, float y, float w, float h){
    vec2f location = vec2(x, y);
    vec2f size = vec2(w, h);
    this -> position = location;
    this -> size = size;
    isEntity = true;
}

