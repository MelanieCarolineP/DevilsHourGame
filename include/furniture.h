
#ifndef _FURNITURE_H_
#define _FURNITURE_H_

#include <string>
#include <vector>

#include "entity.h"

/**
 * @brief Allows the enviorment to handle
 * user interactions
 *
 */
class Furniture : public Entity {
 private:
  std::vector<std::string>
      items; /**< stores the items the furniture(object) holds */

 public:
  int interacted(); /**< handles the user interacting with furniture */
  /**
   * @brief  Furniture constructor
   *
   */
  Furniture();
};
#endif
