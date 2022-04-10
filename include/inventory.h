#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <vector>
#include "item.h"

class Inventory {

    int selectedPosition;

    vector< Item > items;  /**< holds the items */

    public:

        Item getSelectedItem(); /**< gets the selected item */

        void changeSelectedItem(); /**< change the selected item*/

        /**
         * @brief uses the item at the selectedPosition
         *
         */
        void useItem();

        /**
         * @brief Construct a new Inventory object
         *
         */
        Inventory();

};
#endif
