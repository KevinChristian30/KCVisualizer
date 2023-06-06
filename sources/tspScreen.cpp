#ifndef TSP_SCREEN_CPP
#define TSP_SCREEN_CPP

#include "../headers/utility.h"

namespace TSPScreen {
  void show() {
    Utility::clearScreen();
    Utility::UI::animateOuterBorder(0);
  }
}

#endif