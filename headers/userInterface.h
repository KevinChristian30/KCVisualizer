#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

namespace UserInterface {
  /**
   * Position of a Button in spaces, starting from top left
  */
  struct Position {
    short x;
    short y;
  };

  /**
   * Position of a Button in pixels, used to detect mouse click
  */
  struct PixelPosition {
    short minX;
    short minY;
    short maxX;
    short maxY;
  };

  struct Button {
    Position position;
    PixelPosition pixelPosition;
    char text[21];
  };

  void renderButton(Button button);

  bool isPointerInButtonPixelPosition(Button button, POINT cursorPosition);
}

#endif