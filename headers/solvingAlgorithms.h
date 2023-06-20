#ifndef BFS_H
#define BFS_H

#include "./userInterface.h"

namespace SolvingAlgorithms {
  void BFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish, int printOffsetX);

  void DFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish, int printOffsetX);

  void dijkstra(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish, int printOffsetX);

  void aStar(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish, int printOffsetX);

  void printPath(UserInterface::Point::Point* Maze[][112], UserInterface::Position finish, int printOffsetX);

  void TSP(UserInterface::Point::Point* Maze[][112]);
}

#endif