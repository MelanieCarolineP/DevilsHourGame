#ifndef _PLAYER_H_
#define _PLAYER_H_

/**
 * @brief class to handle the user controlled player and their actions
 * 
 */

class Player : public Actor{

    public:
        /**
         * @brief Player contructor
         * 
         */
        Player Player;
        void action (); /**< Handles when the player does an action */

    

};
#endif
