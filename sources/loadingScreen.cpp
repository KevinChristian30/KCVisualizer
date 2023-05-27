#ifndef LOADING_SCREEN_CPP
#define LOADING_SCREEN_CPP

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../headers/utility.h"

namespace LoadingScreen {
  #define WIDTH 115
  #define HEIGHT 27

  const short HORIZONTALPIECE = 205;
  const short VERTICALPIECE = 186;
  const short TOPLEFTPIECE = 201;
  const short TOPRIGHTPIECE = 187;
  const short BOTTOMLEFTPIECE = 200;
  const short BOTTOMRIGHTPIECE = 188;

  void animateOuterBorder(short delay = 0) {
    printf("%c", TOPLEFTPIECE); 
    for (int i = 1; i <= WIDTH; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(i, 0);
      printf("%c", HORIZONTALPIECE);
    }
    printf("%c", TOPRIGHTPIECE); 

    for (int i = 1; i <= HEIGHT; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(0, i);
      printf("%c", VERTICALPIECE);
      Utility::setConsoleCursorPosition(WIDTH + 1, i);
      printf("%c", VERTICALPIECE);
    }

    Utility::setConsoleCursorPosition(0, HEIGHT);
    printf("%c", BOTTOMLEFTPIECE);
    Utility::setConsoleCursorPosition(WIDTH + 1, HEIGHT);
    printf("%c", BOTTOMRIGHTPIECE);
    Utility::setConsoleCursorPosition(WIDTH, HEIGHT);
    printf("%c", HORIZONTALPIECE);
    for (int i = 1; i <= WIDTH / 2 ; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(i, HEIGHT);
      printf("%c", HORIZONTALPIECE);
      Utility::setConsoleCursorPosition(WIDTH - i, HEIGHT);
      printf("%c", HORIZONTALPIECE);
    }

  }

  void animateLoadingBar(short delay = 0) {
    short progress = 0;
    while (progress < 100) {
      Sleep(delay);

      if (progress <= 40) Utility::setConsoleTextColor("FOREGROUND_RED");
      else if (progress <= 80) Utility::setConsoleTextColor("FOREGROUND_BLUE");
      else Utility::setConsoleTextColor("FOREGROUND_GREEN");

      Utility::setConsoleCursorPosition(WIDTH / 2 - 5, HEIGHT / 2);
      printf("Loading %d%%", progress);

      progress += rand() % 3;
    }

    Utility::setConsoleCursorPosition(WIDTH / 2 - 5, HEIGHT / 2);
    printf("Loading %d%%", progress = 100);

    Utility::setConsoleCursorPosition(WIDTH / 2 - 15, HEIGHT / 2 + 1);
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