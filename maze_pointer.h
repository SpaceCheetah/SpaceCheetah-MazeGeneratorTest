#pragma once
#include <vector>
#include <memory>
#include <string>
class maze_pointer
{
	std::shared_ptr<std::vector<uint8_t>> maze;
	int width, height;
public:
	///<summary>
	///Used by generator to create the maze pointer it returns.
	///</summary>
	maze_pointer(std::shared_ptr<std::vector<uint8_t>> maze, int width, int height);
	///<summary>
	///Load a maze pointer from a file. If that file doesn't exist, save a new one with the specified dimensions.
	///If the loaded maze is the wrong size, it deletes that one and generates a new one.
	///</summary>
	maze_pointer(std::string path, int width, int height);
	///<summary>
	///Constructs a blank maze pointer. is_valid() will return false.
	///</summary>
	maze_pointer();
	///<summary>
	///Gets the node at the specified index. Generally get the index with loc.
	///</summary>
	uint8_t operator[](size_t index);
	///<summary>
	///Gets the width of the maze.
	///</summary>
	int getWidth();
	///<summary>
	///Gets the height of the maze.
	///</summary>
	int getHeight();
	///<summary>
	///Get a reference to the vector representation of the maze.
	///</summary>
	std::vector<uint8_t>& getMaze();
	///<summary>
	///Returns true if this maze pointer was created with anything other then the blank constructor.
	///</summary>
	bool is_valid();
};

