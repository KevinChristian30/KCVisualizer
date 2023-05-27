#ifndef MAIN_MENU_SCREEN_CPP
#define MAIN_MENU_SCREEN_CPP

#include <stdio.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/globals.h"

namespace MainMenuScreen {
  const char* LOGO[] = {
    " _  _________      ___                 _ _              ",
    "| |/ / ____\\ \\    / (_)               | (_)             ",
    "| ' / |     \\ \\  / / _ ___ _   _  __ _| |_ _______ _ __ ",
    "|  <| |      \\ \\/ / | / __| | | |/ _` | | |_  / _ \\ '__|",
    "| . \\ |____   \\  /  | \\__ \\ |_| | (_| | | |/ /  __/ |  ",
    "|_|\\_\\_____|   \\/   |_|___/\\__,_|\\__,_|_|_/___\\___|_|"
  };

  void animateTitle(short delay = 0) {
    const short X = 30;

    for (size_t i = 0; i < 6; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(X, 5 + i);
      printf("%s\n", LOGO[i]);
    }

    for (size_t i = 0; i < 7; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(X - 2, 5 + i);
      printf("%c", Globals::VERTICALPIECE);
    }

    Sleep(delay);
    Utility::setConsoleCursorPosition(X - 2, 12);
    printf("%c", Globals::BOTTOMLEFTPIECE);

    for (size_t i = 1; i <= 59; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(X - 2 + i, 12);
      printf("%c", Globals::HORIZONTALPIECE);
    }

    Sleep(delay);
    Utility::setConsoleCursorPosition(X - 2 + 59, 12);
    printf("%c", Globals::BOTTOMRIGHTPIECE);

    for (short i = 6; i >= 0; i--){
      Sleep(delay);
      Utility::setConsoleCursorPosition(X - 2 + 59, 5 + i);
      printf("%c", Globals::VERTICALPIECE);
    }

    Sleep(delay);
    Utility::setConsoleCursorPosition(X - 2 + 59, 4);
    printf("%c", Globals::TOPRIGHTPIECE);

    for (size_t i = 59; i > 1; i--){
      Sleep(delay);
      Utility::setConsoleCursorPosition(X - 3 + i, 4);
      printf("%c", Globals::HORIZONTALPIECE);
    }

    Sleep(delay);
    Utility::setConsoleCursorPosition(X - 2, 4);
    printf("%c", Globals::TOPLEFTPIECE);

    Utility::setConsoleTextColor("FOREGROUND_GREEN");
    for (size_t i = 0; i < 6; i++){
      Sleep(delay);
      Utility::setConsoleCursorPosition(X, 5 + i);
      printf("%s\n", LOGO[i]);
    }
    
    Utility::setConsoleTextColor("FOREGROUND_WHITE");
  }

  void displayMenuOptions() {
    const short X = 54;

    Utility::setConsoleCursorPosition(X, 15);
    printf("Sorting");

    Utility::setConsoleCursorPosition(X, 17);
    printf("Maze Solving");

    Utility::setConsoleCursorPosition(X, 19);
    printf("Field Pathfinding");

    Utility::setConsoleCursorPosition(X, 21);
    printf("Exit");
  }

  void show() {
    Utility::clearScreen();
    Utility::UI::animateOuterBorder(0);
    animateTitle(5);
    displayMenuOptions();

    while (true) {}
  }
}

#endif