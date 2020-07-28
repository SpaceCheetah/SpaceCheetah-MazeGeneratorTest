#pragma once
#include <vector>
#include "maze_pointer.h"
namespace io
{
	///<summary>
	///Writes a maze pointer to the specified file.
	///</summary>
	void write(maze_pointer grid, std::string path);
	///<summary>
	///Reads a maze pointer from the specified file. If the file does not exist, returns a maze pointer that will return false for is_valid().
	///</summary>
	maze_pointer read(std::string path);
}