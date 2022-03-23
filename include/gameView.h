#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

class GameView {
 public:
  /* constructor */
  GameView();

  /* methods to draw element */
  void drawUI();
  void drawRoom();
  void drawActor();
  void drawDoor();
  void drawInventory();

 private:
  /* helper function for drawInventory() */
  void drawItem();
};

#endif /* _GAMEVIEW_H_ */