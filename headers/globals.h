#include <windows.h>

#ifndef GLOBALS
#define GLOBALS

namespace Globals {
  const HANDLE INPUT_HANDLE = GetStdHandle(STD_INPUT_HANDLE);
  const HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

  const short INPUT_BUFFER_SIZE = 128;

  const short WIDTH = 115;
  const short HEIGHT = 27;

  const short HORIZONTAL_PIECE = 205;
  const short VERTICAL_PIECE = 186;
  const short TOP_LEFT_PIECE = 201;
  const short TOP_RIGHT_PIECE = 187;
  const short BOTTOM_LEFT_PIECE = 200;
  const short BOTTOM_RIGHT_PIECE = 188;

  const short BLOCK_PIECE = 219;

  const char TEMPLATE_MAZE[200][200] = {
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
    "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
    "###############################################################################################################",
  };

  const short dirX[] = { -1, 0, 1, 0 };
  const short dirY[] = { 0, 1, 0, -1 };
}

#endif