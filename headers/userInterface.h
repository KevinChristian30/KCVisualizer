#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <windows.h>

#include "./globals.h"

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
    short maxX;
    short minY;
    short maxY;
  };

  struct Button {
    Position position;
    PixelPosition pixelPosition;
    char text[21];
  };

  void renderButton(Button button);

  bool isCursorInButton(Button button, COORD cursorPosition);

  namespace Point {
    struct Point {
      UserInterface::Position position;
      int cost;
      char symbol;
      bool visited;
      Point* prev;
    };

    Point* createPoint(short x, short y);

    int findDistance(Point* point, UserInterface::Position position);
  }
}

#endif