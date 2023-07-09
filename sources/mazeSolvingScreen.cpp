#ifndef MAZE_SOLVING_SCREEN_CPP
#define MAZE_SOLVING_SCREEN_CPP

#include <stdio.h>
#include <windows.h>
#include <limits.h>
#include <vector>

#include "../headers/globals.h"
#include "../headers/utility.h"
#include "../headers/userInterface.h"
#include "../headers/solvingAlgorithms.h"

using namespace std;

namespace MazeSolvingScreen {
  const short H = Globals::HEIGHT - 6;
  const short W = Globals::WIDTH - 4;

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

  UserInterface::Point::Point* Maze[H + 1][W + 1];
  COORD startCursorPosition, finishCursorPosition;
  
  UserInterface::Button btn1;
  UserInterface::Button btn2;
  UserInterface::Button btn3;
  UserInterface::Button btn4;

  namespace RecursiveBacktracking {
    void recursiveBacktracking(UserInterface::Point::Point* Maze[H + 1][W + 1], int posX, int posY) {
      if (posX < 0 || posY < 0 || posX > H - 1 || posY > W - 3) return;

      Maze[posX][posY]->visited = true;

      int order[5];
      randomizeDirections(order);

      vector <UserInterface::Point::Point*> directions;

      for (int i = 0; i < 4; i++) {
        if (posX + (2 * Globals::dirX[order[i]]) < 0 || 
            posX + (2 * Globals::dirX[order[i]]) > H - 1 ||
            posY + (2 * Globals::dirY[order[i]]) < 0 || 
            posY + (2 * Globals::dirY[order[i]]) > W - 3) continue;

        if (Maze[posX + (2 * Globals::dirX[order[i]])][posY + (2 * Globals::dirY[order[i]])]->visited == false) {
          directions.push_back(UserInterface::Point::createPoint(Globals::dirX[order[i]], Globals::dirY[order[i]]));

          Maze[posX + Globals::dirX[order[i]]][posY + Globals::dirY[order[i]]]->symbol = ' ';
          Maze[posX + Globals::dirX[order[i]]][posY + Globals::dirY[order[i]]]->visited = true;

          Utility::setConsoleTextColor("FOREGROUND_BLUE");
          Utility::setConsoleCursorPosition(posY + 4 + Globals::dirY[order[i]], posX + 2 + Globals::dirX[order[i]]);
          printf("%c", Globals::BLOCK_PIECE);

          Utility::setConsoleCursorPosition(posY + 4, posX + 2);
          printf("%c", Globals::BLOCK_PIECE);
          Sleep(5);
          Utility::setConsoleTextColor("FOREGROUND_WHITE");

          recursiveBacktracking(Maze, posX + (2 * Globals::dirX[order[i]]), posY + (2 * Globals::dirY[order[i]]));
        } 
      }

      Utility::setConsoleTextColor("FOREGROUND_WHITE");
      Utility::setConsoleCursorPosition(posY + 4, posX + 2);
      printf(" ");

      for (int i = 0; i < directions.size(); i++){
        Utility::setConsoleCursorPosition(posY + directions.at(i)->position.y + 4, posX +  directions.at(i)->position.x + 2);
        printf(" ");
      }
    
      directions.clear();
      directions.shrink_to_fit();

      Sleep(5);
    }
  }

  namespace Prim {
    void colorFrontiers(vector<UserInterface::Point::Point*> frontiers){
      for (int i = 0; i < frontiers.size(); i++){
        Utility::setConsoleCursorPosition(frontiers.at(i)->position.y + 4, frontiers.at(i)->position.x + 2);
        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        printf("%c", Globals::BLOCK_PIECE);
        Utility::setConsoleTextColor("FOREGROUND_WHITE");
      }
    }

    void prim(UserInterface::Point::Point *Maze[H + 1][W + 1], int posX, int posY) {
      vector <UserInterface::Point::Point*> frontiers;
      frontiers.push_back(Maze[posX][posY]);
      Maze[posX][posY]->visited = true;

      while (frontiers.size() > 0) {
        int randomIndex = rand() % (frontiers.size());
        UserInterface::Point::Point* current = frontiers.at(randomIndex);

        Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
        printf(" ");
        Sleep(5);

        int order[5];
        randomizeDirections(order);
        for (int i = 0; i < 4; i++) {
          if (current->position.x + 2 * Globals::dirX[order[i]] < 0     ||
              current->position.y + 2 * Globals::dirY[order[i]] < 0     || 
              current->position.x + 2 * Globals::dirX[order[i]] > H - 1 || 
              current->position.y + 2 * Globals::dirY[order[i]] > W - 3 ||
              Maze[current->position.x + 2 * Globals::dirX[order[i]]][current->position.y + 2 * Globals::dirY[order[i]]]->visited) continue;

          Utility::setConsoleCursorPosition(current->position.y + Globals::dirY[order[i]] + 4, current->position.x + Globals::dirX[order[i]] + 2);
          printf(" ");
          Sleep(5);

          Maze[current->position.x + Globals::dirX[order[i]]][current->position.y + Globals::dirY[order[i]]]->visited = true;
          Maze[current->position.x + Globals::dirX[order[i]]][current->position.y + Globals::dirY[order[i]]]->symbol = ' ';
          
          Maze[current->position.x + 2 * Globals::dirX[order[i]]][current->position.y + 2 * Globals::dirY[order[i]]]->visited = true;

          frontiers.push_back(Maze[current->position.x + 2 * Globals::dirX[order[i]]][current->position.y + 2 * Globals::dirY[order[i]]]);
        }

        frontiers.erase(frontiers.begin() + randomIndex);
        Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
        Utility::setConsoleTextColor("FOREGROUND_WHITE");
        printf(" ");

        colorFrontiers(frontiers);
      }
    }
  }

  namespace Kruskal {
    struct Set{
      int x;
      int y;
    };

    Set disjointSet[H + 1][W + 1];

    void initializeDisjointSet() {
      for (int i = 1; i <= H - 2; i += 2)
        for (int j = 1; j <= W - 2; j += 2) {
          Set newSet = { i, j };
          disjointSet[i][j] = newSet;
        }
    }

    vector<UserInterface::Point::Point*> listAllFrontiers(){
      vector <UserInterface::Point::Point*> result;

      for (int i = 1; i <= H - 2; i += 2)
        for (int j = 1; j <= W - 4; j += 2) result.push_back(Maze[i][j]);
      
      return result;
    }

    bool isSameSet(UserInterface::Point::Point *current, int dirX, int dirY){
      Set set1 = disjointSet[current->position.x][current->position.y];
      Set set2 = disjointSet[current->position.x + dirX][current->position.y + dirY];

      if (set1.x != set2.x || set1.y != set2.y) return false;
      return true;
    }

    void joinSet(UserInterface::Point::Point *current, int dirX, int dirY){
      Set set1 = disjointSet[current->position.x][current->position.y];
      Set set2 = disjointSet[current->position.x + dirX][current->position.y + dirY];

      for (int i = 1; i <= H - 2; i += 2)
        for (int j = 1; j <= W - 2; j += 2) {
            if (disjointSet[i][j].x == set2.x && disjointSet[i][j].y == set2.y){
              disjointSet[i][j].x = set1.x;
              disjointSet[i][j].y = set1.y;
            }
        }
    }

    bool breakWall(UserInterface::Point::Point* current){
      int order[5];
      randomizeDirections(order);

      for (int i = 0; i < 4; i++) {
        if (current->position.x + 2 * Globals::dirX[order[i]] < 0 ||
            current->position.x + 2 * Globals::dirX[order[i]] > H - 1 ||
            current->position.y + 2 * Globals::dirY[order[i]] < 0 ||
            current->position.y + 2 * Globals::dirY[order[i]] > W - 3 ||
            isSameSet(current, 2 * Globals::dirX[order[i]], 2 * Globals::dirY[order[i]])) continue;

        Maze[current->position.x + Globals::dirX[order[i]]][current->position.y + Globals::dirY[order[i]]]->visited = true;
        Maze[current->position.x + Globals::dirX[order[i]]][current->position.y + Globals::dirY[order[i]]]->symbol = ' ';

        Maze[current->position.x + 2 * Globals::dirX[order[i]]][current->position.y + 2 * Globals::dirY[order[i]]]->visited = true;

        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        Utility::setConsoleCursorPosition(4 + current->position.y + Globals::dirY[order[i]], 2 + current->position.x + Globals::dirX[order[i]]);
        printf("%c", Globals::BLOCK_PIECE);
        Sleep(1);

        Utility::setConsoleCursorPosition(4 + current->position.y + 2 * Globals::dirY[order[i]], 2 + current->position.x + 2 * Globals::dirX[order[i]]);
        printf("%c", Globals::BLOCK_PIECE);
        Sleep(1);
        Utility::setConsoleTextColor("FOREGROUND_WHITE");

        Utility::setConsoleCursorPosition(4 + current->position.y + Globals::dirY[order[i]], 2 + current->position.x + Globals::dirX[order[i]]);
        printf(" ");
        Sleep(1);

        Utility::setConsoleCursorPosition(4 + current->position.y + 2 * Globals::dirY[order[i]], 2 + current->position.x + 2 * Globals::dirX[order[i]]);
        printf(" ");
        Sleep(1);
        joinSet(current, 2 * Globals::dirX[order[i]], 2 * Globals::dirY[order[i]]);

        return true;
      }

      return false;
    }

    void kruskal(UserInterface::Point::Point *Maze[H + 1][W + 1]){
      vector<UserInterface::Point::Point*> frontiers;
      frontiers = listAllFrontiers();

      initializeDisjointSet();

      while (frontiers.size() > 0) {
        int randomIndex = rand() % frontiers.size();
        UserInterface::Point::Point* current = frontiers.at(randomIndex);

        Utility::setConsoleCursorPosition(4 + current->position.y, 2 + current->position.x);
        printf(" ");
        Sleep(5);

        if (!breakWall(current)) frontiers.erase(frontiers.begin() + randomIndex);
      }
    }
  }

  void initializeMaze() {
    for (int i = 0; i < H; i++)
      for (int j = 0; j < W; j++) Maze[i][j] = UserInterface::Point::createPoint(i, j);
  }

  void animateRawMaze() {
    for (int i = 0; i < H; i++){
      Utility::setConsoleCursorPosition(3, 2 + i);
      for (int j = 0; j < W; j++) printf("%c", Globals::BLOCK_PIECE);
      Sleep(10);
    }
  }

  void initializeUIElements() {
    initializeMaze();

    const short X = 5;
    const short Y = 24;
    const short GAP = 6;
    
    btn1.position = { X, Y };
    strncpy(btn1.text, "Backtracking", 20);

    btn2.position = { X + (22 * 1) + (GAP * 1), Y };
    strncpy(btn2.text, "Prim", 20);

    btn3.position = { X + (22 * 2) + (GAP * 2) + 1, Y };
    strncpy(btn3.text, "Kruskal", 20);

    btn4.position = { X + (22 * 3) + (GAP * 3) + 1, Y };
    strncpy(btn4.text, "Back", 20);
  }

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    Utility::UI::animateInnerBorder(0);
    
    animateRawMaze();

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

  bool handleSolveClick(COORD cursorPosition) {
    if (UserInterface::isCursorInButton(btn1, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::BFS(Maze, start, finish, 4);

      SolvingAlgorithms::printPath(Maze, finish, 4);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn2, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::DFS(Maze, start, finish, 4);

      SolvingAlgorithms::printPath(Maze, finish, 4);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn3, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::dijkstra(Maze, start, finish, 4);

      SolvingAlgorithms::printPath(Maze, finish, 4);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btn4, cursorPosition)) {
      UserInterface::Position start = UserInterface::translateUICoordinateToMazePoint(startCursorPosition);
      UserInterface::Position finish = UserInterface::translateUICoordinateToMazePoint(finishCursorPosition);

      displayPathFinding();
      SolvingAlgorithms::aStar(Maze, start, finish, 4);

      SolvingAlgorithms::printPath(Maze, finish, 4);
      displayMazeSolved();

      Utility::UI::waitForLeftClick();

      return true;
    }

    return false;
  }

  bool setSolveEventHandler() {
    COORD cursorPosition = Utility::UI::waitForLeftClick();

    return handleSolveClick(cursorPosition);
  }

  bool isValidPosition(COORD cursorPosition) {
    if (cursorPosition.X < 4 || 
        cursorPosition.X > Globals::WIDTH - 3 || 
        cursorPosition.Y < 2 || 
        cursorPosition.Y > Globals::HEIGHT - 5) 
      return false;

    if (Maze[cursorPosition.Y - 2][cursorPosition.X - 4]->symbol == '#') return false;

    if (startCursorPosition.X == finishCursorPosition.X && startCursorPosition.Y == finishCursorPosition.Y)
      return false;

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

  bool handleClick(COORD cursorPosition) {
    if (UserInterface::isCursorInButton(btn1, cursorPosition)) {
      Utility::UI::clearButtons();
      displayGeneratingView();

      RecursiveBacktracking::recursiveBacktracking(Maze, 1, 1);

      Utility::UI::clearButtons();
      waitForStartingAndEndingPointInputs();
      displaySolveButtons();

      while (!setSolveEventHandler());

      return true;
    } else if (UserInterface::isCursorInButton(btn2, cursorPosition)) {
      Utility::UI::clearButtons();
      displayGeneratingView();

      Prim::prim(Maze, 1, 1);

      Utility::UI::clearButtons();
      waitForStartingAndEndingPointInputs();
      displaySolveButtons();

      while (!setSolveEventHandler());

      return true;
    } else if (UserInterface::isCursorInButton(btn3, cursorPosition)) {
      Utility::UI::clearButtons();
      displayGeneratingView();

      Kruskal::kruskal(Maze);

      Utility::UI::clearButtons();
      waitForStartingAndEndingPointInputs();
      displaySolveButtons();

      while (!setSolveEventHandler());

      return true;
    } else if (UserInterface::isCursorInButton(btn4, cursorPosition)) {
      return true;
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