#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>

namespace Utility {
  void clearScreen();
  void setConsoleCursorPosition(short x, short y);
  void setConsoleTextColor(const char *colorName);
  void animateString(const char *string, short delay);

  namespace UI {
    void animateOuterBorder(short delay);

    void animateInnerBorder(short delay);
  
    void clearButtons();

    COORD waitForLeftClick();

    COORD waitForDoubleClick();
  }
}

#endif