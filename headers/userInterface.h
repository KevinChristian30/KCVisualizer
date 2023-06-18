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

  struct Button {
    Position position;
    char text[21];
  };

  void renderButton(Button button);

  bool isCursorInButton(Button button, COORD cursorPosition);

  Position translateUICoordinateToMazePoint(COORD coordinate);

  namespace Point {
    struct Point {
      UserInterface::Position position;
      int cost;
      char symbol;
      bool visited;
      Point* prev;
    };

    Point* createPoint(short x, short y);

    int calculateDistance(Point* point, UserInterface::Position position);
  }
}

#endif