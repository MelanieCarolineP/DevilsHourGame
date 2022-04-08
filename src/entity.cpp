
#include "entity.h"

Entity :: Entity( float x, float y, float w, float h){
    vec2f location = vec2(x, y);
    vec2f size = vec2(w, h);
    this -> position = location;
    this -> size = size;
    isEntity = true;
}

