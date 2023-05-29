#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

namespace UserInterface {
  /**
   * Position of a Button, starting from top left
  */
  struct Position {
    short x;
    short y;
  };

  struct Button {
    Position position;
    char text[21];
  };

  void renderButton(Button button);
}

#endif