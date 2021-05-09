#include"cell.hpp"
#include"world.hpp"


namespace gol
{
    World::World(int width, int height)
    {
        size = std::pair<int, int>(
            width  >= 1 ? width  : 1,
            height >= 1 ? height : 1);
    }

    World::World(std::pair<int, int> _size)
    {
        size = std::pair<int, int>(
            _size.first  >= 1 ? _size.first  : 1,
            _size.second >= 1 ? _size.second : 1);
    }

    std::pair<int, int> World::getSize()
    {
        return size;
    }

    Cell* World::getCell(int x, int y)
    {
        return map[y][x];
    }
}
