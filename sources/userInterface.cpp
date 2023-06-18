#ifndef USER_INTERFACE_CPP
#define USER_INTERFACE_CPP

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../headers/globals.h"
#include "../headers/utility.h"

namespace UserInterface {
  /**
   * Position of a Button, starting from top left
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

  void renderButton(UserInterface::Button button) {
    Utility::setConsoleCursorPosition(button.position.x, button.position.y);
    printf("%c", Globals::TOPLEFTPIECE);

    Utility::setConsoleCursorPosition(button.position.x + 1, button.position.y);
    for (short i = 0; i < 20; i++) printf("%c", Globals::HORIZONTALPIECE);

    Utility::setConsoleCursorPosition(button.position.x + 21, button.position.y);
    printf("%c", Globals::TOPRIGHTPIECE);

    Utility::setConsoleCursorPosition(button.position.x, button.position.y + 1);
    printf("%c", Globals::VERTICALPIECE);

    size_t length = strlen(button.text);
    for (int i = 0; i < (20 - length) / 2; i++) printf(" ");
    printf("%s", button.text);

    Utility::setConsoleCursorPosition(button.position.x + 21, button.position.y + 1);
    printf("%c", Globals::VERTICALPIECE);

    Utility::setConsoleCursorPosition(button.position.x, button.position.y + 2);
    printf("%c", Globals::BOTTOMLEFTPIECE);

    Utility::setConsoleCursorPosition(button.position.x + 1, button.position.y + 2);
    for (short i = 0; i < 20; i++) printf("%c", Globals::HORIZONTALPIECE);

    Utility::setConsoleCursorPosition(button.position.x + 21, button.position.y + 2);
    printf("%c", Globals::BOTTOMRIGHTPIECE);
  };

 bool isPointerInButtonPixelPosition(Button button, COORD cursorPosition) {
    return 
      cursorPosition.X >= button.position.x && 
      cursorPosition.X <= button.position.x + 22 &&
      cursorPosition.Y >= button.position.y &&
      cursorPosition.Y <= button.position.y + 2;
  }

  namespace Point {
    struct Point {
      UserInterface::Position position;
      int cost;
      char symbol;
      bool visited;
      Point* prev;
    };

    Point* createPoint(short x, short y){
      Point* newPoint = (Point*) malloc(sizeof(Point));
      
      newPoint->position = { x, y };
      newPoint->symbol = Globals::TemplateMaze[x][y];
      newPoint->cost = INT_MAX;
      newPoint->visited = false;
      newPoint->prev = NULL;

      return newPoint;
    }

    int findDistance(Point* point, UserInterface::Position position){
      int distanceX = pow(point->position.x - position.x, 2);
      int distanceY = pow(point->position.y - position.y, 2);

      return point->cost + sqrt(distanceX + distanceY);
    }    
  }
}

#endif