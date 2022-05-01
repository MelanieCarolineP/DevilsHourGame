#include "room.h"

#include <iostream>

int main() {
  Room r(Rooms::bathroom);
  // std::cout << r.entityList.size() << std::endl;
  int n = r.entityList.size();
  std::cout << r.boundX << std::endl;
  std::cout << r.boundY << std::endl;
  std::cout << r.boundW << std::endl;
  std::cout << r.boundH << std::endl;
  for (int i = 0; i < n; ++i) {
    std::cout << r.entityList[i].name << std::endl;
    std::cout << r.entityList[i].position.x << std::endl;
    std::cout << r.entityList[i].position.y << std::endl;
    std::cout << r.entityList[i].size.x << std::endl;
    std::cout << r.entityList[i].size.y << std::endl;
    std::cout << r.entityList[i].isEntity << std::endl;
    std::cout << std::endl;
  }
  return 0;
}