#ifndef LOADING_SCREEN_CPP
#define LOADING_SCREEN_CPP

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/globals.h"

namespace LoadingScreen {
  void animateLoadingBar(short delay = 0) {
    short progress = 0;
    while (progress < 100) {
      Sleep(delay);

      if (progress <= 40) Utility::setConsoleTextColor("FOREGROUND_RED");
      else if (progress <= 80) Utility::setConsoleTextColor("FOREGROUND_BLUE");
      else Utility::setConsoleTextColor("FOREGROUND_GREEN");

      Utility::setConsoleCursorPosition(Globals::WIDTH / 2 - 5, Globals::HEIGHT / 2);
      printf("Loading %d%%", progress);

      progress += rand() % 3;
    }

    Utility::setConsoleCursorPosition(Globals::WIDTH / 2 - 5, Globals::HEIGHT / 2);
    printf("Loading %d%%", progress = 100);

    Utility::setConsoleCursorPosition(Globals::WIDTH / 2 - 14, Globals::HEIGHT / 2 + 1);
    Utility::animateString("Double Click Anywhere to Continue", 15);
  }

  void show() {
    Utility::UI::animateOuterBorder(1);
    animateLoadingBar(20);
    
    Utility::UI::waitForDoubleClick();

    Utility::clearScreen();
    Utility::setConsoleTextColor("FOREGROUND_WHITE");
  }
}

#endif