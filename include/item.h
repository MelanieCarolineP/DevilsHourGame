#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include <map>

class Item {

    string itemName; /**< name of the item */

    map<Item, Item> itemCombinations; /**< holds the possible combinations of items, with the combined item, then the resulting item */

    public:
        /**
         * @brief Construct a new Item object
         *
         */
        Item(string itemName);

        /**
         * @brief Adds a new possible combination to the item
         *
         */
        void addItemCombination(Item combinedItem, Item finalItem);

        /**
         * @brief Adds a new possible combination to the item
         *
         */
        string getName();
};
#endif