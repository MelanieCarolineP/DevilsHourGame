// Include header file
#include "inventory.h"
#include "item.h"


Inventory::Inventory() {
    Inventory::selectedPosition = 0;
    Inventory::items = {};
}

Item Inventory::getSelectedItem() {
    return Inventory::items[1];
}

void Inventory::useItem() {

}

void Inventory::changeSelectedItem() {
    Inventory::selectedPosition = ( Inventory::selectedPosition + 1 ) % 8;
}
