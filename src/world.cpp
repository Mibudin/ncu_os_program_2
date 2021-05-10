#include"cell.hpp"
#include"world.hpp"


namespace gol
{
    World::World(const int width, const int height)
    {
        turn = 0;
        size[0] = width;
        size[1] = height;

        setMap();
    }

    int World::goTurn()
    {
        updateAllMap();

        return ++turn;
    }

    int World::getTurn()
    {
        return turn;
    }

    int* World::getSize()
    {
        return size;
    }

    Cell* World::getCell(const int x, const int y)
    {
        return map[y][x];
    }

    WorldMap* World::_testGetMap()
    {
        return &map;
    }

    void World::updateAllMap()
    {
        WorldMapStreet* wms;
        for(int i = 0; i < size[1]; i++)
        {
            WorldMapStreet* wms = &(map[i]);
            for(int j = 0; j < size[0]; j++)
            {
                (*wms)[j]->interact(&map, size, j, i, turn);
            }
        }

        return;
    }

    void World::setMap()
    {
        map = WorldMap(size[1], WorldMapStreet(size[0], nullptr));
        fillMap();

        return;
    }

    void World::fillMap()
    {
        WorldMapStreet* wms;
        for(int i = 0; i < size[1]; i++)
        {
            WorldMapStreet* wms = &(map[i]);
            for(int j = 0; j < size[0]; j++)
            {
                (*wms)[j] = new Cell();
            }
        }

        return;
    }
}
