#ifndef EXIT_SCREEN_CPP
#define EXIT_SCREEN_CPP

#include <windows.h>

#include "../headers/globals.h"
#include "../headers/utility.h"

namespace ExitScreen {
  void displayExitMessage() {
    Utility::setConsoleCursorPosition(15, Globals::HEIGHT / 2 - 5);
    Utility::animateString("\"Wonderful Things Can be Achieved When There's Teamwork, Hardwork, and Perseverance\"", 30);

    Sleep(500);

    Utility::setConsoleTextColor("FOREGROUND_BLUE");
    Utility::setConsoleCursorPosition(15, Globals::HEIGHT / 2 - 3);
    Utility::animateString("- Bluejackets 22-2", 15);

    Sleep(1000);

    Utility::setConsoleTextColor("FOREGROUND_GREEN");
    Utility::setConsoleCursorPosition(15, Globals::HEIGHT / 2 + 2);
    Utility::animateString("Made by: KC22-2", 30);
    Sleep(500);

    Utility::setConsoleTextColor("FOREGROUND_WHITE");
    Utility::setConsoleCursorPosition(15, Globals::HEIGHT / 2 + 5);
    Utility::animateString("Click Anywhere to Exit", 30);
  }

  void show() {
    Utility::clearScreen();
    Utility::UI::animateOuterBorder(0);
    displayExitMessage();

    Utility::UI::waitForLeftClick();

    exit(0);
  }
}

#endif