#include "inventory.h"

#include <iostream>

/**
 * @brief Construct a new Inventory
 *
 */
Inventory::Inventory() {
  currentPosition = 0;
  items = {
      "hands", "", "", "", "", "", "", "",
  }; /**< itilialize the items vector with 8 slots */
}

const std::string Inventory::getSelectedItem() {
  return items.at(currentPosition);
}

const std::string Inventory::getItemAtPos(int position) {
  return items.at(position);
}

const std::vector<std::string> Inventory::getAllItems() { return items; }

const bool Inventory::itemInInventory(std::string itemName) {
  for (int i = 0; i < 8; i++) {
    if (items.at(i) == itemName) {
      return true;
    }
  }
  return false;
}

void Inventory::addItem(std::string itemName) {
  for (int i = 0; i < 8; i++) {
    if (items.at(i) == "") {
      items.at(i) = itemName;
      return;
    }
  }
}

void Inventory::removeItem() {
  items.at(currentPosition) = "";
} /**< removes the item at the current position*/

void Inventory::changeSelectedItem() {
  Inventory::currentPosition = (Inventory::currentPosition + 1) % 8;
}
