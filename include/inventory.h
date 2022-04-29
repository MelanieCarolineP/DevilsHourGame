#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>
#include <vector>

class Inventory {
  std::vector<std::string> items; /**< holds the items */
  int currentPosition;

 public:
  Inventory();
  const std::string getSelectedItem(); /**< gets the selected item */
  const std::string getItemAtPos(
      int position); /**< gets the item at the selected position */
  const std::vector<std::string>
  getAllItems(); /**< gets a list of all the items */

  void changeSelectedItem();          /**< change the selected item*/
  void addItem(std::string itemName); /**< adds a given item to the inventory*/
  void removeItem(); /**< removes the item at the current position*/

  /**
   * @brief Construct a new Inventory object
   *
   */
};
#endif
