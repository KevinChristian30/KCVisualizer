#ifndef UTILITY_CPP
#define UTILITY_CPP

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../headers/globals.h"

namespace Utility {
  #define FOREGROUND_WHITE 0x07
  #define FOREGROUND_LIGHTBLUE 0x09

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

  void clearScreen() {
    setConsoleCursorPosition(0, 0);

    for (int i = 0; i < Globals::HEIGHT; i++) {
      printf("                                                                                                                   \n");
    }
  }

  namespace UI {
    void animateOuterBorder(short delay) {
      setConsoleCursorPosition(0, 0);

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
  
    void animateInnerBorder(short delay) {
      setConsoleCursorPosition(2, 1);
      printf("%c", Globals::TOPLEFTPIECE);

      for (size_t i = 3; i < 114; i++){
        Sleep(delay);
        setConsoleCursorPosition(i, 1);
        printf("%c", Globals::HORIZONTALPIECE);
      }

      Sleep(delay);
      setConsoleCursorPosition(114, 1);
      printf("%c", Globals::TOPRIGHTPIECE);

      for (size_t i = 0; i < 22; i++){
        Sleep(delay);
        setConsoleCursorPosition(2, 2 + i);
        printf("%c", Globals::VERTICALPIECE);

        Sleep(delay);
        setConsoleCursorPosition(114, 2 + i);
        printf("%c", Globals::VERTICALPIECE);
      }

      Sleep(delay);
      setConsoleCursorPosition(2, 23);
      printf("%c", Globals::BOTTOMLEFTPIECE);

      Sleep(delay);
      setConsoleCursorPosition(114, 23);
      printf("%c", Globals::BOTTOMRIGHTPIECE);

      for (size_t i = 3; i < 114; i++){
        Sleep(delay);
        setConsoleCursorPosition(i, 23);
        printf("%c", Globals::HORIZONTALPIECE);
      }
    }
  
    void clearButtons() {
      const short Y = 25;

      for (short i = 1; i < Globals::WIDTH - 1; i++) {
        Utility::setConsoleCursorPosition(i, Y - 1);
        printf(" ");
        Utility::setConsoleCursorPosition(i, Y);
        printf(" ");
        Utility::setConsoleCursorPosition(i, Y + 1);
        printf(" ");
      }
    }
  
    COORD waitForLeftClick() {
      DWORD NUMBER_OF_EVENTS_READ;
      INPUT_RECORD INPUT_BUFFER[Globals::INPUT_BUFFER_SIZE];

      int counter;
      while (true) {
        counter = 0;

        while (counter++ <= 100) {
          ReadConsoleInput(Globals::INPUTHANDLE, INPUT_BUFFER, Globals::INPUT_BUFFER_SIZE, &NUMBER_OF_EVENTS_READ);

          for (int i = 0; i < NUMBER_OF_EVENTS_READ; i++) {
            if (INPUT_BUFFER[i].EventType == MOUSE_EVENT) {
              MOUSE_EVENT_RECORD event = INPUT_BUFFER[i].Event.MouseEvent;

              if (event.dwEventFlags != 0) continue;
              if (event.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED) continue;

              COORD cursorPosition = { event.dwMousePosition.X, event.dwMousePosition.Y };
              return cursorPosition;
            }
          }
        }
      }
    }
  }
}

#endif