#include "loc.h"
loc::loc(int x, int y) :x{ x }, y{ y } {};
size_t loc::index(int width) const
{
	return ((size_t)y) * width + x;
}