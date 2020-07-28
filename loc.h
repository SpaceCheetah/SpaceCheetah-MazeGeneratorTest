#pragma once
class loc
{
public:
	int x, y;
	loc(int x, int y);
	///<summary>
	///Gets the index for this loc of a maze with the specified width.
	///</summary>
	size_t index(int width) const;
};