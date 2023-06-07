#ifndef MAZE_SOLVING_SCREEN_CPP
#define MAZE_SOLVING_SCREEN_CPP

#include <stdio.h>
#include <windows.h>
#include <limits.h>
#include <math.h>
#include <vector>

#include "../headers/globals.h"
#include "../headers/utility.h"
#include "../headers/userInterface.h"

using namespace std;

namespace MazeSolvingScreen {
  const short H = Globals::HEIGHT - 6;
  const short W = Globals::WIDTH - 4;

  const short dirX[] = {0, 1, 0, -1};
  const short dirY[] = {-1, 0, 1, 0};

  const char TemplateMaze[H + 1][W + 1] = {
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

  namespace Point {
    struct Point {
      UserInterface::Position position;
      int cost;
      char symbol;
      bool visited;
      Point* prev;
    };

    Point* createPoint(short x, short y){
      Point* newPoint = (Point*) malloc(sizeof(Point));
      
      newPoint->position = { x, y };
      newPoint->symbol = TemplateMaze[x][y];
      newPoint->cost = INT_MAX;;
      newPoint->visited = false;
      newPoint->prev = NULL;

      return newPoint;
    }

    int findDistance(Point* point, UserInterface::Position position){
      int distanceX = pow(point->position.x - position.x, 2);
      int distanceY = pow(point->position.y - position.y, 2);

      return point->cost + sqrt(distanceX + distanceY);
    }    
  }

  namespace RecursiveBacktracking {
    void randomizeDirections(int array[5]) {
      bool isInArray[5] = { false };
      int elementInArray = 0;

      while (elementInArray < 4){
        int randomNumber = rand() % 4;
        if (!isInArray[randomNumber]){
          array[elementInArray++] = randomNumber;
          isInArray[randomNumber] = true;
        }
      }
    }

    void recursiveBacktracking(Point::Point* Maze[H + 1][W + 1], int posX, int posY) {
      if (posX < 0 || posY < 0 || posX > H - 1 || posY > W - 3) return;

      Maze[posX][posY]->visited = true;

      int order[5];
      randomizeDirections(order);

      vector <Point::Point*> directions;

      for (int i = 0; i < 4; i++) {
        if (posX + (2 * dirX[order[i]]) < 0 || 
            posX + (2 * dirX[order[i]]) > H - 1 ||
            posY + (2 * dirY[order[i]]) < 0 || 
            posY + (2 * dirY[order[i]]) > W - 3) continue;

        if (Maze[posX + (2 * dirX[order[i]])][posY + (2 * dirY[order[i]])]->visited == false) {
          directions.push_back(Point::createPoint(dirX[order[i]], dirY[order[i]]));

          Maze[posX + dirX[order[i]]][posY + dirY[order[i]]]->symbol = ' ';
          Maze[posX + dirX[order[i]]][posY + dirY[order[i]]]->visited = true;

          Utility::setConsoleTextColor("FOREGROUND_GREEN");
          Utility::setConsoleCursorPosition(posY + 4 + dirY[order[i]], posX + 2 + dirX[order[i]]);
          printf("%c", Globals::BLOCK);

          Utility::setConsoleCursorPosition(posY + 4, posX + 2);
          printf("%c", Globals::BLOCK);
          Sleep(5);
          Utility::setConsoleTextColor("FOREGROUND_WHITE");

          recursiveBacktracking(Maze, posX + (2 * dirX[order[i]]), posY + (2 * dirY[order[i]]));
        } 
      }

      Utility::setConsoleTextColor("FOREGROUND_WHITE");
      Utility::setConsoleCursorPosition(posY + 4, posX + 2);
      printf(" ");

      for (int i = 0; i < directions.size(); i++){
        Utility::setConsoleCursorPosition(posY + directions.at(i)->position.y + 4, posX +  directions.at(i)->position.x + 2);
        printf(" ");
      }
    
      Sleep(5);
    }
  }

  Point::Point* Maze[H + 1][W + 1];

  UserInterface::Button btnRecursiveBacktracking;
  UserInterface::Button btnPrim;
  UserInterface::Button btnKruskal;
  UserInterface::Button btnBack;

  void initializeMaze(){
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) Maze[i][j] = Point::createPoint(i, j);
  }

  void animateRawMaze(){
    for (int i = 0; i < H; i++){
      Utility::setConsoleCursorPosition(3, 2 + i);
      for (int j = 0; j < W; j++) printf("%c", Globals::BLOCK);
      Sleep(10);
    }
  }

  void initializeUIElements() {
    initializeMaze();

    const short X = 5;
    const short Y = 24;
    const short GAP = 6;
    
    btnRecursiveBacktracking.position = { X, Y };
    btnRecursiveBacktracking.pixelPosition = { 60, 300, 580, 640 };
    strncpy(btnRecursiveBacktracking.text, "Backtracking", 20);

    btnPrim.position = { X + (22 * 1) + (GAP * 1), Y };
    btnPrim.pixelPosition = { 380, 620, 580, 640 };
    strncpy(btnPrim.text, "Prim", 20);

    btnKruskal.position = { X + (22 * 2) + (GAP * 2) + 1, Y };
    btnKruskal.pixelPosition = { 700, 940, 580, 640 };
    strncpy(btnKruskal.text, "Kruskal", 20);

    btnBack.position = { X + (22 * 3) + (GAP * 3) + 1, Y };
    btnBack.pixelPosition = { 990, 1230, 580, 640 };
    strncpy(btnBack.text, "Back", 20);
  }

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    Utility::UI::animateInnerBorder(0);
    
    animateRawMaze();

    UserInterface::renderButton(btnRecursiveBacktracking);
    UserInterface::renderButton(btnPrim);
    UserInterface::renderButton(btnKruskal);
    UserInterface::renderButton(btnBack);
  }

  bool handleClick(POINT cursorPosition) {
    if (UserInterface::isPointerInButtonPixelPosition(btnRecursiveBacktracking, cursorPosition)) {
      RecursiveBacktracking::recursiveBacktracking(Maze, 1, 1);
      while (true);

      return false;
    } else if (UserInterface::isPointerInButtonPixelPosition(btnPrim, cursorPosition)) {
      

      return false;
    } else if (UserInterface::isPointerInButtonPixelPosition(btnKruskal, cursorPosition)) {
      return false;
    } else if (UserInterface::isPointerInButtonPixelPosition(btnBack, cursorPosition)) {
      return false;
    }

    return true;
  }

  bool setEventHandlers() {
    POINT cursorPosition;
	  HWND hWnd = GetForegroundWindow();

    if (GetAsyncKeyState(VK_LBUTTON) & 1) {
      GetCursorPos(&cursorPosition);
      ScreenToClient(hWnd, &cursorPosition);
    
      if (!handleClick(cursorPosition)) return false;
    }

    return true;
  }

  void show() {
    Utility::clearScreen();

    initializeUIElements();
    displayUIElements();

    while (setEventHandlers());
  }
}

#endif