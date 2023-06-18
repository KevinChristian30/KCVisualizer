#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "headers/loadingScreen.h"
#include "headers/mainMenuScreen.h"
#include "headers/globals.h"

void setRandomNumberSeed() {
  srand(time(0));
}

void saveConsoleMode() {
  // GetConsoleMode(Globals::INPUTHANDLE, &Globals::OLDCONSOLEMODE);
}

void enableWindowAndMouseInputEvents() {
  DWORD mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
  SetConsoleMode(Globals::INPUTHANDLE, mode);
}

void disableLeftClickConsolePause() {
  DWORD prevMode;
  GetConsoleMode(Globals::INPUTHANDLE, &prevMode);

  SetConsoleMode(Globals::INPUTHANDLE, prevMode & ENABLE_EXTENDED_FLAGS);
}

void hideCursor() {
  CONSOLE_CURSOR_INFO cci;
  
  GetConsoleCursorInfo(Globals::OUTPUTHANDLE, &cci);
  cci.bVisible = FALSE;

  SetConsoleCursorInfo(Globals::OUTPUTHANDLE, &cci);
}

void initializeApp() {
  setRandomNumberSeed();

  saveConsoleMode();
  disableLeftClickConsolePause();
  enableWindowAndMouseInputEvents();
  hideCursor();
}

int main() {
  initializeApp();
	// LoadingScreen::show();
  MainMenuScreen::show();
	return 0;
}