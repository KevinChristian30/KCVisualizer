#ifndef BFS_H
#define BFS_H

#include "./userInterface.h"

namespace SolvingAlgorithms {
  void BFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish);

  void DFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish);

  void dijkstra(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish);

  void aStar(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish);

  void printPath(UserInterface::Point::Point* Maze[][112], UserInterface::Position finish);
}

#endif