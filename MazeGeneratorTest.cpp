#include "maze_pointer.h"
#include "generator.h"
#include "global.h"
#include "loc.h"
#include "random.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
int main()
{
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	maze_pointer p{ "test.maze", 5, 5 };
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Duration: " << duration.count() << " seconds\n";
}