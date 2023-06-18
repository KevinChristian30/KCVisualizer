#ifndef BFS_CPP
#define BFS_CPP

#include <stdio.h>
#include <vector>

#include "../headers/utility.h"
#include "../headers/userInterface.h"
#include "../headers/globals.h"

using namespace std;

namespace SolvingAlgorithms {
  void colorFrontiers(vector <UserInterface::Point::Point*> frontiers, const char* color) {
    Utility::setConsoleTextColor(color);
    
    for (size_t i = 0; i < frontiers.size(); i++) {
      Utility::setConsoleCursorPosition(frontiers[i]->position.y + 4, frontiers[i]->position.x + 2);
    
      printf("%c", Globals::BLOCK_PIECE);
    }
  }

  void BFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish) {
    for (int i = 0; i < 21; i++) for (int j = 0; j < 111; j++) 
      Maze[i][j]->visited = false;
    
    vector <UserInterface::Point::Point*> queue;
    queue.push_back(Maze[start.y][start.x]);
    
    while (queue.size() > 0) {
      if (Maze[finish.y][finish.x]->visited) break;

      colorFrontiers(queue, "FOREGROUND_PURPLE");
      Sleep(10);
      
      UserInterface::Point::Point* current = queue.at(0);

      current->visited = true;

      Utility::setConsoleTextColor("FOREGROUND_BLUE");
      Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
      printf("%c", Globals::BLOCK_PIECE);

      for (int i = 0; i < 4; i++) {
        if (Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->symbol == ' ' &&
            Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->visited == false
            ){
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->prev = Maze[current->position.x][current->position.y];

              queue.push_back(Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]);
            }
      }

      queue.erase(queue.begin());
    }
  }

  void DFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish) {
    for (int i = 0; i < 21; i++) for (int j = 0; j < 111; j++) 
      Maze[i][j]->visited = false;

    vector <UserInterface::Point::Point*> Stack;
    Stack.push_back(Maze[start.y][start.x]);

    while (Stack.size() > 0) {
      if (Maze[finish.y][finish.x]->visited) break;

      UserInterface::Point::Point* current = Stack.at(Stack.size() - 1);
      Stack.erase(Stack.begin() + Stack.size() - 1);

      current->visited = true;

      colorFrontiers(Stack, "FOREGROUND_PURPLE");

      Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
      Utility::setConsoleTextColor("FOREGROUND_GREEN");
      printf("%c", Globals::BLOCK_PIECE);
      Sleep(10);

      for (int i = 0; i < 4; i++) {
        if (Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->symbol == ' ' &&
            Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->visited == false
            ) {
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->prev = Maze[current->position.x][current->position.y];

              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->cost = Maze[current->position.x][current->position.y]->cost + 1;

              Stack.push_back(Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]);
            }
      }

      Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
      Utility::setConsoleTextColor("FOREGROUND_BLUE");
      printf("%c", Globals::BLOCK_PIECE);
    }
  }

  void dijkstra(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish) {
    for (int i = 0; i < 21; i++) for (int j = 0; j < 111; j++) 
      Maze[i][j]->visited = false;
    
    vector <UserInterface::Point::Point*> queue;
    queue.push_back(Maze[start.y][start.x]);
    Maze[start.y][start.x]->cost = 0;

    while (queue.size() > 0) {
      if (Maze[finish.y][finish.x]->visited) break;

      colorFrontiers(queue, "FOREGROUND_PURPLE");
      Sleep(10);

      UserInterface::Point::Point* current = queue.at(0);
      int currentIndex = 0;
      for (int i = 0; i < queue.size(); i++) {
        if (queue[i]->cost > current->cost) continue;

        current = queue[i];
        currentIndex = i;
      }
      queue.erase(queue.begin() + currentIndex);

      current->visited = true;

      Utility::setConsoleTextColor("FOREGROUND_BLUE");
      Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
      printf("%c", Globals::BLOCK_PIECE);
      
      for (int i = 0; i < 4; i++) {
        if (Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->symbol == ' ' &&
            1 + Maze[current->position.x][current->position.y]->cost < 
            Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->cost
            ){
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->prev = Maze[current->position.x][current->position.y];
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->cost = Maze[current->position.x][current->position.y]->cost;

              queue.push_back(Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]);
            }
      }
    }
  }

  void aStar(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish) {
    for (int i = 0; i < 21; i++) for (int j = 0; j < 111; j++) 
      Maze[i][j]->visited = false;
    
    vector <UserInterface::Point::Point*> queue;
    queue.push_back(Maze[start.y][start.x]);
    Maze[start.y][start.x]->cost = 0;

    while (queue.size() > 0){
      if (Maze[finish.y][finish.x]->visited) break;

      colorFrontiers(queue, "FOREGROUND_PURPLE");
      Sleep(10);

      UserInterface::Point::Point* current = queue.at(0);
      int currentIndex = 0;
      for (int i = 0; i < queue.size(); i++) {
        int currentDistance = UserInterface::Point::calculateDistance(current, finish);
        int iThDistance = UserInterface::Point::calculateDistance(queue[i], finish);

        if (iThDistance > currentDistance) continue;

        current = queue[i];
        currentIndex = i;
      }
      queue.erase(queue.begin() + currentIndex);

      current->visited = true;

      Utility::setConsoleTextColor("FOREGROUND_BLUE");
      Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
      printf("%c", Globals::BLOCK_PIECE);
      
      for (int i = 0; i < 4; i++) {
        if (Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->symbol == ' ' &&
            1 + Maze[current->position.x][current->position.y]->cost < 
            Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->cost
            ){
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->prev = Maze[current->position.x][current->position.y];
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->cost = Maze[current->position.x][current->position.y]->cost;

              queue.push_back(Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]);
            }
      }
    }
  }
}

#endif