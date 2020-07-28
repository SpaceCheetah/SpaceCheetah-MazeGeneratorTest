#pragma once
#include <vector>
#include "maze_pointer.h"
namespace generator
{
    ///<summary>
    ///Generates a maze_pointer pointing to a maze of the specified size.
    ///</summary>
    maze_pointer genMaze(int width, int height);
}