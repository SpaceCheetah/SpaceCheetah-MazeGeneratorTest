#include "io.h"
#include "global.h"
#include <fstream>
#include <filesystem>

using namespace std;
void io::write(maze_pointer grid, string path)
{
    uint8_t current = 0;
    vector<char> toWrite(sizeof(int) * 2);
    int width{ grid.getWidth() };
    int height{ grid.getHeight() };
    memcpy(&toWrite[0], &width, sizeof(int));
    memcpy(&toWrite[sizeof(int)], &height, sizeof(int));
    size_t i = 0;
    for (; i != grid.getMaze().size(); i++)
    {
        switch (i % 4)
        {
        case 0:
            if (grid[i] & global::east) current |= 128;
            if (grid[i] & global::south) current |= 64;
            break;
        case 1:
            if (grid[i] & global::east) current |= 32;
            if (grid[i] & global::south) current |= 16;
            break;
        case 2:
            if (grid[i] & global::east) current |= 8;
            if (grid[i] & global::south) current |= 4;
            break;
        case 3:
            if (grid[i] & global::east) current |= 2;
            if (grid[i] & global::south) current |= 1;
            toWrite.push_back(current);
            current = 0;
        }
    }
    if ((i % 4) != 3) toWrite.push_back(current);
    ofstream out{ path, ios::out | ios::binary };
    out.write(&toWrite[0], toWrite.size());
    out.close();
}
maze_pointer io::read(string path)
{
    if (!filesystem::exists(path)) return {};
    uintmax_t size = filesystem::file_size(path);
    ifstream in{ path, ios::in | ios::binary };
    vector<char> read(size);
    in.read(&read[0], size);
    in.close();
    int width{ 0 };
    int height{ 0 };
    memcpy(&width, &read[0], sizeof(int));
    memcpy(&height, &read[sizeof(int)], sizeof(int));
    read.erase(read.begin(), read.begin() + 2 * sizeof(int));
    vector<uint8_t>* grid = new vector<uint8_t>(width * height);
    for (size_t i{ 0 }; i != grid->size(); i++)
    {
        switch (i % 4)
        {
        case 0:
            if (read[i / 4] & 128) (*grid)[i] |= global::east;
            if (read[i / 4] & 64) (*grid)[i] |= global::south;
            break;
        case 1:
            if (read[i / 4] & 32) (*grid)[i] |= global::east;
            if (read[i / 4] & 16) (*grid)[i] |= global::south;
            break;
        case 2:
            if (read[i / 4] & 8) (*grid)[i] |= global::east;
            if (read[i / 4] & 4) (*grid)[i] |= global::south;
            break;
        case 3:
            if (read[i / 4] & 2) (*grid)[i] |= global::east;
            if (read[i / 4] & 1) (*grid)[i] |= global::south;
        }
    }

    return { shared_ptr<vector<uint8_t>> (grid), width, height };
}