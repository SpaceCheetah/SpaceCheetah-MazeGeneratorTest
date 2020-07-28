#include "generator.h"
#include "global.h"
#include "random.h"
#include "loc.h"
#include <array>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace global;

constexpr array<array<uint8_t, 4>, 24> getDirectionsCombutations()
{
	array<array<uint8_t, 4>, 24> directionsTemp{};
	int index{ 0 };
	constexpr array<uint8_t, 4> directions{ north, east, south, west };
	for (uint8_t first : directions)
	{
		array<uint8_t, 4> row{ first };
		for (uint8_t second : directions)
		{
			if (second == first) continue;
			row[1] = second;
			for (uint8_t third : directions)
			{
				if ((third == first) || (third == second)) continue;
				row[2] = third;
				for (uint8_t fourth : directions)
				{
					if ((fourth == first) || (fourth == second) || (fourth == third)) continue;
					row[3] = fourth;
					directionsTemp[index++] = row;
				}
			}
		}
	}
	return directionsTemp;
}
constexpr array<array<uint8_t, 4>, 24> directions{ getDirectionsCombutations() };
maze_pointer generator::genMaze(int width, int height)
{
	vector<uint8_t>* grid = new vector<uint8_t>(((size_t)width) * height);
	vector<loc> path{ {random::next_int(width - 1), random::next_int(height - 1)} };
	while (!path.empty())
	{
	cont_while:
		for (uint8_t direction : directions[random::next_int23()])
		{
			loc next{ path.back() };
			uint8_t opposite{ 0 };
			switch (direction)
			{
			case north:
				--next.y;
				opposite = south;
				break;
			case east:
				++next.x;
				opposite = west;
				break;
			case south:
				++next.y;
				opposite = north;
				break;
			case west:
				--next.x;
				opposite = east;
				break;
			}
			if (next.x >= 0 && next.y >= 0 && next.x < width && next.y < height && (*grid)[next.index(width)] == 0)
			{
				(*grid)[path.back().index(width)] |= direction;
				(*grid)[next.index(width)] |= opposite;
				path.push_back(next);
				goto cont_while; //Simulating the continue(label) language construct from java. Also skips the condition, as we know it's true.
			}
		}
		path.pop_back();
	}
	return { shared_ptr<vector<uint8_t>>(grid), width, height };
}