#pragma once
#ifndef WORLD_H
#define WORLD_H

#include<utility>
#include<vector>
#include"cell.hpp"


namespace gol
{
    // Forward declarations
    class Cell;


    typedef std::vector<Cell*> WorldMapStreet;
    typedef std::vector<WorldMapStreet> WorldMap;


    class World
    {
    public:
        World(int _width, int _height);
        World(std::pair<int, int> _size);
        std::pair<int, int> getSize();
        Cell* getCell(int x, int y);

    private:
        std::pair<int, int> size;
        WorldMap map;
    };
}

#endif
