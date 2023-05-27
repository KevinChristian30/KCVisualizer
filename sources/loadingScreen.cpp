#ifndef LOADING_SCREEN_CPP
#define LOADING_SCREEN_CPP

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/globals.h"

namespace LoadingScreen {
  void animateOuterBorder(short delay = 0) {
    printf("%c", Globals::TOPLEFTPIECE); 
    for (int i = 1; i <= Globals::WIDTH; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(i, 0);
      printf("%c", Globals::HORIZONTALPIECE);
    }
    printf("%c", Globals::TOPRIGHTPIECE); 

    for (int i = 1; i <= Globals::HEIGHT; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(0, i);
      printf("%c", Globals::VERTICALPIECE);
      Utility::setConsoleCursorPosition(Globals::WIDTH + 1, i);
      printf("%c", Globals::VERTICALPIECE);
    }

    Utility::setConsoleCursorPosition(0, Globals::HEIGHT);
    printf("%c", Globals::BOTTOMLEFTPIECE);
    Utility::setConsoleCursorPosition(Globals::WIDTH + 1, Globals::HEIGHT);
    printf("%c", Globals::BOTTOMRIGHTPIECE);
    Utility::setConsoleCursorPosition(Globals::WIDTH, Globals::HEIGHT);
    printf("%c", Globals::HORIZONTALPIECE);
    for (int i = 1; i <= Globals::WIDTH / 2 ; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(i, Globals::HEIGHT);
      printf("%c", Globals::HORIZONTALPIECE);
      Utility::setConsoleCursorPosition(Globals::WIDTH - i, Globals::HEIGHT);
      printf("%c", Globals::HORIZONTALPIECE);
    }

  }

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

    Utility::setConsoleCursorPosition(Globals::WIDTH / 2 - 15, Globals::HEIGHT / 2 + 1);
    Utility::animateString("Left Click Anywhere to Continue", 15);
  }

  void waitForLeftClick() {
    while(true) 
      if(GetAsyncKeyState(VK_LBUTTON) & 1) break;
  }

  void show() {
    animateOuterBorder(1);
    animateLoadingBar(20);
    waitForLeftClick();
  }
}

#endif