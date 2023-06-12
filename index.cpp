#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "headers/utility.h"
#include "headers/loadingScreen.h"
#include "headers/mainMenuScreen.h"

void hideCursor() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cci;
  
  GetConsoleCursorInfo(hOut, &cci);
  cci.bVisible = FALSE;

  SetConsoleCursorInfo(hOut, &cci);
}

void disableLeftClickConsolePause() {
  HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
  DWORD prevMode;

  GetConsoleMode(hInput, &prevMode);
  SetConsoleMode(hInput, prevMode & ENABLE_EXTENDED_FLAGS);
}

void setRandomNumberSeed() {
  srand(time(0));
}

void disableResize() {
  HWND consoleWindow = GetConsoleWindow();
  LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
  style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
  SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void initializeApp() {
  hideCursor();
  disableLeftClickConsolePause();
  setRandomNumberSeed();
  disableResize();
}

int main() {
  initializeApp();
	// LoadingScreen::show();
  MainMenuScreen::show();
	return 0;
}