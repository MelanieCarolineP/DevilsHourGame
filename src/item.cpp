// Include header file
#include "item.h"

Item::Item(string itemName) {
    Item::itemName = itemName;
}

void Item::addItemCombination(Item combinedItem, Item finalItem) {
    Item::itemCombinations.insert( std::pair<Item,Item>(combinedItem,finalItem) );
}

string Item::getName() {
    return Item::itemName;
}