#ifndef SANDBOX_SCREEN_CPP
#define SANDBOX_SCREEN_CPP

#include <stdio.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/userInterface.h"
#include "../headers/solvingAlgorithms.h"

namespace SandboxScreen {
  const short H = Globals::HEIGHT - 6;
  const short W = Globals::WIDTH - 4;

  UserInterface::Point::Point* Maze[H + 1][W + 1];
  COORD startCursorPosition, finishCursorPosition;
  
  UserInterface::Button btn1;
  UserInterface::Button btn2;
  UserInterface::Button btn3;
  UserInterface::Button btn4;

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
      Sleep(10);
    }
  }

  void initializeUIElements() {
    initializeMaze();

    const short X = 5;
    const short Y = 24;
    const short GAP = 6;
    
    btn1.position = { X, Y };
    strncpy(btn1.text, "BFS", 20);

    btn2.position = { X + (22 * 1) + (GAP * 1), Y };
    strncpy(btn2.text, "DFS", 20);

    btn3.position = { X + (22 * 2) + (GAP * 2) + 1, Y };
    strncpy(btn3.text, "Dijkstra's", 20);

    btn4.position = { X + (22 * 3) + (GAP * 3) + 1, Y };
    strncpy(btn4.text, "A*", 20);
  }

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    Utility::UI::animateInnerBorder(0);
    
    animateRawMaze();
  }

  void displayButtons() {
    Utility::setConsoleTextColor("FOREGROUND_WHITE");

    UserInterface::renderButton(btn1);
    UserInterface::renderButton(btn2);
    UserInterface::renderButton(btn3);
    UserInterface::renderButton(btn4);
  }

  void displayGeneratingView() {
    const short X = 29;
    const short Y = 25;

    Utility::UI::clearButtons();

    Utility::setConsoleTextColor("FOREGROUND_WHITE");
    Utility::setConsoleCursorPosition(X + 22, Y);
    printf("Generating Maze");
  }

  void displayPathFinding() {
    const short X = 29;
    const short Y = 25;

    Utility::UI::clearButtons();

    Utility::setConsoleTextColor("FOREGROUND_WHITE");
    Utility::setConsoleCursorPosition(X + 24, Y);
    printf("Searching");
  }

  void displayMazeSolved() {
    const short X = 29;
    const short Y = 25;

    Utility::UI::clearButtons();

    Utility::setConsoleTextColor("FOREGROUND_WHITE");
    Utility::setConsoleCursorPosition(X + 11, Y);
    Utility::animateString("Path Found, Left Click to Continue", 10);
  }

  void displaySolveButtons() {
    Utility::setConsoleTextColor("FOREGROUND_WHITE");

    strncpy(btn1.text, "BFS", 20);
    strncpy(btn2.text, "DFS", 20);
    strncpy(btn3.text, "Dijkstra's", 20);
    strncpy(btn4.text, "A*", 20);

    UserInterface::renderButton(btn1);
    UserInterface::renderButton(btn2);
    UserInterface::renderButton(btn3);
    UserInterface::renderButton(btn4);
  }

  bool handleClick(COORD cursorPosition) {
    if (UserInterface::isCursorInButton(btn1, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::BFS(Maze, start, finish);

      SolvingAlgorithms::printPath(Maze, finish);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn2, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::DFS(Maze, start, finish);

      SolvingAlgorithms::printPath(Maze, finish);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn3, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::dijkstra(Maze, start, finish);

      SolvingAlgorithms::printPath(Maze, finish);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn4, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::aStar(Maze, start, finish);

      SolvingAlgorithms::printPath(Maze, finish);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    }

    return false;
  }

  bool isValidPosition(COORD cursorPosition) {
    if (cursorPosition.X < 4 || 
        cursorPosition.X > Globals::WIDTH - 3 || 
        cursorPosition.Y < 2 || 
        cursorPosition.Y > Globals::HEIGHT - 5) 
      return false;

    if (Maze[cursorPosition.Y - 2][cursorPosition.X - 3]->symbol == '#') return false;

    return true;
  }

  void waitForStartingAndEndingPointInputs() {
    Utility::setConsoleCursorPosition(45, 25);
    printf("Select Start and End Position");
    
    int numberOfPointsSelected = 0;

    while (numberOfPointsSelected < 2) {
      if (numberOfPointsSelected == 0) {
        startCursorPosition = Utility::UI::waitForLeftClick();

        if (!isValidPosition(startCursorPosition)) continue;

        Utility::setConsoleTextColor("FOREGROUND_GREEN");
        Utility::setConsoleCursorPosition(startCursorPosition.X, startCursorPosition.Y);
        printf("%c", Globals::BLOCK_PIECE);

        numberOfPointsSelected++;
      } else {
        finishCursorPosition = Utility::UI::waitForLeftClick();

        if (!isValidPosition(finishCursorPosition)) continue;

        Utility::setConsoleTextColor("FOREGROUND_RED");
        Utility::setConsoleCursorPosition(finishCursorPosition.X, finishCursorPosition.Y);
        printf("%c", Globals::BLOCK_PIECE);

        numberOfPointsSelected++;
      }
    }
  
    Utility::UI::clearButtons();
  }

  bool setEventHandlers() {
    COORD cursorPosition = Utility::UI::waitForLeftClick();

    return handleClick(cursorPosition);
  }

  void show() {
    Utility::clearScreen();

    initializeUIElements();
    displayUIElements();
    waitForStartingAndEndingPointInputs();
    displayButtons();

    while (!setEventHandlers());
  }
}

#endif