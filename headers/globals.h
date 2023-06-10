#ifndef GLOBALS
#define GLOBALS

#include <windows.h>

namespace Globals {
  const HANDLE OUTPUTHANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

  const short WIDTH = 115;
  const short HEIGHT = 27;

  const short SPACEWIDTH = 11;
  const short SPACEHEIGHT = 24;

  const short HORIZONTALPIECE = 205;
  const short VERTICALPIECE = 186;
  const short TOPLEFTPIECE = 201;
  const short TOPRIGHTPIECE = 187;
  const short BOTTOMLEFTPIECE = 200;
  const short BOTTOMRIGHTPIECE = 188;

  const short BLOCK = 219;
}

#endif