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

  void clear() {
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
}

#endif