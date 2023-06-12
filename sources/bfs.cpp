#ifndef BFS_CPP
#define BFS_CPP

#include <stdio.h>
#include <vector>

#include "../headers/utility.h"
#include "../headers/userInterface.h"
#include "../headers/globals.h"

using namespace std;

namespace BFS {
  void BFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish) {
    for (int i = 0; i < 21; i++) for (int j = 0; j < 111; j++) 
      Maze[i][j]->visited = false;
    
    vector <UserInterface::Point::Point*> queue;
    queue.push_back(Maze[start.y][start.x]);
    
    while (queue.size() > 0){
      if (Maze[finish.y][finish.x]->visited) break;
      
      UserInterface::Point::Point* current = queue.at(0);
      queue.erase(queue.begin());

      current->visited = true;

      Utility::setConsoleTextColor("FOREGROUND_BLUE");
      Utility::setConsoleCursorPosition(current->position.y + 4, current->position.x + 2);
      printf("%c", Globals::BLOCK);
      Sleep(5);

      for (int i = 0; i < 4; i++) {
        if (Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->symbol == ' ' &&
            Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->visited == false
            ){
              Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]->prev = Maze[current->position.x][current->position.y];

              queue.push_back(Maze[current->position.x + Globals::dirY[i]][current->position.y + Globals::dirX[i]]);
            }
      }
    }
  }
}

#endif