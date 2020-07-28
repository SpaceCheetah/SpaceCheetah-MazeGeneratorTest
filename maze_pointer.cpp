#include "maze_pointer.h"
#include "io.h"
#include "generator.h"

maze_pointer::maze_pointer(std::shared_ptr<std::vector<uint8_t>> maze, int width, int height) :maze{ maze }, width{ width }, height{ height }
{
}

maze_pointer::maze_pointer(std::string path, int widthD, int heightD)
{
	maze_pointer maze_p{ io::read(path) };
	if (!maze_p.is_valid() || maze_p.width != widthD || maze_p.height != heightD)
	{
		maze_p = generator::genMaze(widthD, heightD);
		io::write(maze_p, path);
	}
	maze = maze_p.maze;
	width = maze_p.width;
	height = maze_p.height;
}

maze_pointer::maze_pointer() : maze(std::shared_ptr<std::vector<uint8_t>>{ nullptr }), width{ 0 }, height{ 0 } {}

uint8_t maze_pointer::operator[](size_t index)
{
	return (*maze)[index];
}

int maze_pointer::getWidth()
{
	return width;
}

int maze_pointer::getHeight()
{
	return height;
}

std::vector<uint8_t>& maze_pointer::getMaze()
{
	return *maze;
}

bool maze_pointer::is_valid()
{
	return bool{ maze };
}
