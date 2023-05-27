#ifndef UTILITY_H
#define UTILITY_H

namespace Utility {
  void clear();
  void setConsoleCursorPosition(short x, short y);
  void setConsoleTextColor(const char *colorName);
  void animateString(const char *string, short delay);
}

#endif