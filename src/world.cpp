#include<stdio.h>
#include<thread>
#include"cell.hpp"
#include"world.hpp"
#include"screenio.hpp"


namespace gol
{
    // Forward declarations
    World* World::w;


    World::World(const int width, const int height)
    {
        turn = 0;
        size[0] = width;
        size[1] = height;

        setMap();
    }

    int World::goTurn()
    {
        // updateAllMap();
        updateAllCells();
        // updateAllCellsPar();

        // return ++turn;
        return turn + 1;
    }

    int World::nextTurn()
    {
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

    void World::updateAllCells()
    {
        for(int i = 0; i < size[0] * size[1]; i++)
        {
            updateACell(i);
        }

        return;
    }

    void World::updateAllCellsPar()
    {
        w = this;
        // threadPool.parallelize_loop(0, size[0] * size[1] - 1, updateACellIStatic, 1);

        return;
    }

    void World::updateACellIStatic(const int i)
    {
        int* size = w->size;
        w->updateACell(i % size[1], i / size[1]);

        return;
    }

    void World::updateACell(const int i)
    {
        updateACell(i % size[1], i / size[1]);

        return;
    }

    void World::updateACell(const int x, const int y)
    {
        map[y][x]->interact(&map, size, x, y, turn);

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

    bool World::needRender()
    {
        return true;
    }

    void World::render()
    {
        ANSIES(SCP CUP(3, 5));
        
        WorldMapStreet* wms;
        for(int i = 0; i < size[1]; i++)
        {
            
            WorldMapStreet* wms = &(map[i]);
            for(int j = 0; j < size[0]; j++)
            {
                switch((*wms)[j]->getStatus()[turn & 1])
                {
                    case DEAD: printf(". "); break;
                    case LIVE: printf("O "); break;
                }
            }
            ANSIES("\n" CHA(5));
        }

        // WorldMapStreet* wms;
        // for(int i = 0; i < size[1]; i++)
        // {
            
        //     WorldMapStreet* wms = &(map[i]);
        //     for(int j = 0; j < size[0]; j++)
        //     {
        //         (*wms)[j]->render(j, i, turn);
        //     }
        // }

        return;
    }
}
