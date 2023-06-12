#ifndef BFS_H
#define BFS_H

#include "./userInterface.h"

namespace BFS {
  void BFS(UserInterface::Point::Point* Maze[][112], UserInterface::Position start, UserInterface::Position finish);
}

#endif