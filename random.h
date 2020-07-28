#pragma once
namespace random
{
	///<summary>
	///Get a random number from low to high, inclusive.
	///</summary>
	int next_int(int low, int high);
	///<summary>
	///Equivalent to next_int(0, high), but slightly faster as there's less math.
	///</summary>
	int next_int(int high);
	///<summary>
	///Analog to next_int(23); I made it since that was the most common use, and I wanted to reduce it as much as possible removing all unneccesary variables.
	///</summary>
	int next_int23();
}