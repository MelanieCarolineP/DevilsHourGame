#include "dialog.h"

int main() {
  Dialog d(Rooms::kitchen);

  int n = d.dialogList.size();
  for (int i = 0; i < n; ++i) {
    dialog dl = d.dialogList[i];
    std::cout << dl.id << std::endl;
    // std::cout << dl.x1 << std::endl;
    // std::cout << dl.x2 << std::endl;
    // std::cout << dl.y1 << std::endl;
    // std::cout << dl.y2 << std::endl;
    std::cout << dl.pickItem << std::endl;
    std::cout << dl.triggerObject << std::endl;
    std::cout << dl.triggerState << std::endl;
    std::cout << dl.transitToState << std::endl;
    std::cout << dl.useItem << std::endl;
    std::cout << "-----------" << std::endl;
  }
  // std::cout << (d.dialogList[17].useItem == "") << std::endl;
  return 0;
}