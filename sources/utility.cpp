#ifndef UTILITY_CPP
#define UTILITY_CPP

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../headers/globals.h"
#include "../headers/utility.h"

namespace Utility {
  #define FOREGROUND_WHITE 0x07
  #define FOREGROUND_LIGHTBLUE 0x09

  void clearScreen() {
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
  }

  void setConsoleCursorPosition(short x, short y) {
    COORD targetPosition = {x, y};
    SetConsoleCursorPosition(Globals::OUTPUTHANDLE, targetPosition);
  }

  void setConsoleTextColor(const char *colorName) {
    if (strcmp(colorName, "FOREGROUND_RED") == 0){
      SetConsoleTextAttribute(Globals::OUTPUTHANDLE, FOREGROUND_RED);
    } else if (strcmp(colorName, "FOREGROUND_GREEN") == 0){
      SetConsoleTextAttribute(Globals::OUTPUTHANDLE, FOREGROUND_GREEN);
    } else if (strcmp(colorName, "FOREGROUND_BLUE") == 0){
      SetConsoleTextAttribute(Globals::OUTPUTHANDLE, FOREGROUND_LIGHTBLUE);
    } else if (strcmp(colorName, "FOREGROUND_WHITE") == 0){
      SetConsoleTextAttribute(Globals::OUTPUTHANDLE, FOREGROUND_WHITE);
    } 
  }

  void animateString(const char *str, short delay) {
    size_t stringLength = strlen(str);
    for (size_t i = 0; i < stringLength; i++) {
      Sleep(delay);
      printf("%c", str[i]);
    }
  }

  namespace UI {
    void animateOuterBorder(short delay) {
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
  }
}

#endif