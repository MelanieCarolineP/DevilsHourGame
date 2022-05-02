#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>
#include <vector>

class Inventory {
  std::vector<std::string> items; /**< holds the items */

 public:
  Inventory();
  const std::string getSelectedItem(); /**< gets the selected item */
  const std::string getItemAtPos(
      int position); /**< gets the item at the selected position */
  const std::vector<std::string>
  getAllItems(); /**< gets a list of all the items */
  const bool itemInInventory(
      std::string itemName); /**< returns true if the player
                          has an item, false if not */

  void changeSelectedItem();          /**< change the selected item*/
  void addItem(std::string itemName); /**< adds a given item to the inventory*/
  void removeItem(); /**< removes the item at the current position*/

  int currentPosition;
  /**
   * @brief Construct a new Inventory object
   *
   */
};
#endif
