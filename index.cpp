#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "headers/loadingScreen.h"
#include "headers/mainMenuScreen.h"
#include "headers/globals.h"

void setRandomNumberSeed() {
  srand(time(0));
}

void enableWindowAndMouseInputEvents() {
  DWORD mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
  SetConsoleMode(Globals::INPUT_HANDLE, mode);
}

void disableLeftClickConsolePause() {
  DWORD prevMode;
  GetConsoleMode(Globals::INPUT_HANDLE, &prevMode);

  SetConsoleMode(Globals::INPUT_HANDLE, prevMode & ENABLE_EXTENDED_FLAGS);
}

void hideCursor() {
  CONSOLE_CURSOR_INFO cci;
  
  GetConsoleCursorInfo(Globals::OUTPUT_HANDLE, &cci);
  cci.bVisible = FALSE;

  SetConsoleCursorInfo(Globals::OUTPUT_HANDLE, &cci);
}

void initializeApp() {
  setRandomNumberSeed();

  disableLeftClickConsolePause();
  enableWindowAndMouseInputEvents();
  hideCursor();
}

int main() {
  initializeApp();
	LoadingScreen::show();
  MainMenuScreen::show();
	return 0;
}