#ifndef MAIN_MENU_SCREEN_CPP
#define MAIN_MENU_SCREEN_CPP

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/globals.h"
#include "../headers/userInterface.h"
#include "../headers/exitScreen.h"
#include "../headers/tspScreen.h"
#include "../headers/sortingScreen.h"
#include "../headers/mazeSolvingScreen.h"
#include "../headers/sandboxScreen.h"

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
    const short Y = 16;
    const short GAP = 6;
    
    btnTSP.position = { X, Y };
    btnTSP.pixelPosition = { 60, 300, 390, 450 };
    strncpy(btnTSP.text, "TSP", 20);

    btnSorting.position = { X + (22 * 1) + (GAP * 1), Y };
    btnSorting.pixelPosition = { 380, 620, 390, 450 };
    strncpy(btnSorting.text, "Sorting", 20);

    btnMazeSolving.position = { X + (22 * 2) + (GAP * 2) + 1, Y };
    btnMazeSolving.pixelPosition = { 700, 940, 390, 450 };
    strncpy(btnMazeSolving.text, "Maze Solving", 20);

    btnSandBox.position = { X + (22 * 3) + (GAP * 3) + 1, Y };
    btnSandBox.pixelPosition = { 990, 1230, 390, 450 };
    strncpy(btnSandBox.text, "SandBox", 20);

    btnExit.position = { X + (22 * 2) - 2, Y + 6};
    btnExit.pixelPosition = { 520, 760, 536, 589 };
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
    UserInterface::renderButton(btnSorting);
    UserInterface::renderButton(btnMazeSolving);
    UserInterface::renderButton(btnSandBox);
    UserInterface::renderButton(btnExit);
  }

  void handleClick(POINT cursorPosition) {
    if (UserInterface::isPointerInButtonPixelPosition(btnTSP, cursorPosition)){
      TSPScreen::show();
    } else if (UserInterface::isPointerInButtonPixelPosition(btnSorting, cursorPosition)){
      SortingScreen::show();
    } else if (UserInterface::isPointerInButtonPixelPosition(btnMazeSolving, cursorPosition)){
      MazeSolvingScreen::show();
    } else if (UserInterface::isPointerInButtonPixelPosition(btnSandBox, cursorPosition)){
      SandboxScreen::show();
    } else if (UserInterface::isPointerInButtonPixelPosition(btnExit, cursorPosition)){
      ExitScreen::show();
    }
  }

  void setEventHandlers() {
    POINT cursorPosition;
	  HWND hWnd = GetForegroundWindow();

    while (true) if (GetAsyncKeyState(VK_LBUTTON) & 1) break;

    GetCursorPos(&cursorPosition);
    ScreenToClient(hWnd, &cursorPosition);
  
    handleClick(cursorPosition);
  }

  void show() {
    initializeUIElements();

    while (true) {
      Utility::clearScreen();
      displayUIElements();
      
      setEventHandlers();
    }
  }
}

#endif