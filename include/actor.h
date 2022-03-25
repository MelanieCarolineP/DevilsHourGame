#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "entity.h"

/**
 * @brief Actor handles all the enities in the game that move independently
 * 
 */
class Actor : public Entity {
    
    public:
        /**
         * @brief contructor
         * 
         * @return Actor 
         */
        Actor Actor();
        float velocity; /**< how fast they move */
        void move(); /**< handles movement */
        void collision(); /**< handles when the actor in in contact with something */


};

#endif /* _ACTOR_H_ */
