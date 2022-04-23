#include "dialog.h"

int main() {
  Dialog d(Rooms::bathroom);
  std::cout << d.dialogList.size() << std::endl;
  std::cout << d.dialogList[3].texts[0] << std::endl;
  return 0;
}