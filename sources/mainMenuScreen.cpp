#ifndef MAIN_MENU_SCREEN_CPP
#define MAIN_MENU_SCREEN_CPP

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/globals.h"
#include "../headers/userInterface.h"

namespace MainMenuScreen {
  const char* LOGO[] = {
    " _  _________      ___                 _ _              ",
    "| |/ / ____\\ \\    / (_)               | (_)             ",
    "| ' / |     \\ \\  / / _ ___ _   _  __ _| |_ _______ _ __ ",
    "|  <| |      \\ \\/ / | / __| | | |/ _` | | |_  / _ \\ '__|",
    "| . \\ |____   \\  /  | \\__ \\ |_| | (_| | | |/ /  __/ |  ",
    "|_|\\_\\_____|   \\/   |_|___/\\__,_|\\__,_|_|_/___\\___|_|"
  };

  UserInterface::Button btnTSP;
  UserInterface::Button btnSorting;
  UserInterface::Button btnMazeSolving;
  UserInterface::Button btnSandBox;
  UserInterface::Button btnExit;

  void initializeUIElements() {
    const short X = 5;
    const short Y = 20;
    
    btnTSP.position = { X, Y };
    strncpy(btnTSP.text, "TSP", 20);

    btnSorting.position = { X + (22 * 1), Y };
    strncpy(btnSorting.text, "Sorting", 20);

    btnMazeSolving.position = { X + (22 * 2), Y };
    strncpy(btnMazeSolving.text, "Maze Solving", 20);

    btnSandBox.position = { X + (22 * 3), Y };
    strncpy(btnSandBox.text, "SandBox", 20);

    btnExit.position = { X + (22 * 4), Y };
    strncpy(btnExit.text, "Exit", 20);
  }

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

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    animateTitle(5);

    UserInterface::renderButton(btnTSP);
    
  }

  void show() {
    Utility::clearScreen();

    initializeUIElements();
    displayUIElements();

    while (true) {}
  }
}

#endif