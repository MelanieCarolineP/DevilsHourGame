#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <vector>

class Inventory {

    public:
        vector< string* > items;  /**< holds the items */
        getSelectedItem(); /**< gets the selected item */
        changeSelectedItem(); /**< change the selected item*/
        
        /**
         * @brief handeles the use of items 
         * 
         */
        useItem(item, position);
        /**
         * @brief Construct a new Inventory object
         * 
         */
        Inventory Inventory();

};
#endif
