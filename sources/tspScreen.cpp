#ifndef TSP_SCREEN_CPP
#define TSP_SCREEN_CPP

#include <stdio.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/solvingAlgorithms.h"
#include "../headers/userInterface.h"

namespace TSPScreen {
  const short H = Globals::HEIGHT - 6;
  const short W = Globals::WIDTH - 4;

  UserInterface::Point::Point* Maze[H + 1][W + 1];
  COORD startCursorPosition, finishCursorPosition;
  
  UserInterface::Button btn1;
  UserInterface::Button btn2;

  int pointsToSelect;

  void initializeMaze() {
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) { 
        Maze[i][j] = UserInterface::Point::createPoint(i, j);

        if (i > 0 && i < H - 1 && j > 0 && j < W - 1) Maze[i][j]->symbol = ' ';
        if (j == 1 || j == W - 2) Maze[i][j]->symbol = '#';      
      }
  }

  void animateRawMaze() {
    for (int i = 0; i < H; i++) {
      Utility::setConsoleCursorPosition(3, 2 + i);
      for (int j = 0; j < W; j++) printf("%c", Maze[i][j]->symbol == '#' ? Globals::BLOCK_PIECE : ' ');
    }
  }

  void initializeUIElements() {
    initializeMaze();

    pointsToSelect = 5;

    const short X = 5;
    const short Y = 24;
    const short GAP = 6;
    
    btn1.position = { X, Y };
    strncpy(btn1.text, "Solve", 20);

    btn2.position = { X + (22 * 3) + (GAP * 3) + 1, Y };
    strncpy(btn2.text, "Back", 20);
  }

  void displayPointsToSelect() {
    const short X = 29;
    const short Y = 25;

    Utility::setConsoleTextColor("FOREGROUND_WHITE");
    Utility::setConsoleCursorPosition(X + 20, Y);
    printf("Select %d Points", pointsToSelect);
  }

  void displayTSPSolved() {
    const short X = 29;
    const short Y = 25;

    Utility::setConsoleTextColor("FOREGROUND_WHITE");
    Utility::setConsoleCursorPosition(X + 1, Y);
    Utility::animateString("Traveling Salesman Problem Solved! Left Click to Continue", 10);
  }

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    Utility::UI::animateInnerBorder(0);
    
    animateRawMaze();

    UserInterface::renderButton(btn2);
    displayPointsToSelect();
  }

  bool isInBound(COORD cursorPosition) {
    if (cursorPosition.X < 5 || 
        cursorPosition.X > Globals::WIDTH - 4 || 
        cursorPosition.Y < 3 || 
        cursorPosition.Y > Globals::HEIGHT - 6)
      return false;

    return true;
  }

  bool handleClick(COORD cursorPosition) {
    if (UserInterface::isCursorInButton(btn1, cursorPosition)) {
      if (pointsToSelect > 0) return false;

      SolvingAlgorithms::TSP(Maze);
      
      Utility::UI::clearButtons();
      displayTSPSolved();
      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn2, cursorPosition)) {
      return true;
    } else if (isInBound(cursorPosition)) {
      if (Maze[cursorPosition.Y - 2][cursorPosition.X - 3]->symbol == ' ') {
        if (pointsToSelect == 0) return false;

        Maze[cursorPosition.Y - 2][cursorPosition.X - 3]->symbol = '#';
        Utility::setConsoleCursorPosition(cursorPosition.X, cursorPosition.Y);
        Utility::setConsoleTextColor("FOREGROUND_WHITE");
        printf("%c", Globals::BLOCK_PIECE);

        pointsToSelect--;
      } else {
        Maze[cursorPosition.Y - 2][cursorPosition.X - 3]->symbol = ' ';
        Utility::setConsoleCursorPosition(cursorPosition.X, cursorPosition.Y);
        Utility::setConsoleTextColor("FOREGROUND_WHITE");
        printf(" ");

        pointsToSelect++;
      }
    }

    Utility::UI::clearButtons();

    if (pointsToSelect > 0) {
      displayPointsToSelect();
      UserInterface::renderButton(btn2);
    } else {
      UserInterface::renderButton(btn1);
      UserInterface::renderButton(btn2);
    }

    return false;
  }

  bool setEventHandlers() {
    COORD cursorPosition = Utility::UI::waitForLeftClick();

    return handleClick(cursorPosition);
  }

  void show() {
    Utility::clearScreen();

    initializeUIElements();
    displayUIElements();
  
    while (!setEventHandlers());
  }
}

#endif