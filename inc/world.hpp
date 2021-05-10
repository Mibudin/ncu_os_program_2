#pragma once
#ifndef WORLD_H
#define WORLD_H

#include<vector>
#include"cell.hpp"
#include"thread_pool.hpp"


namespace gol
{
    // Forward declarations
    class Cell;


    typedef std::vector<Cell*> WorldMapStreet;
    typedef std::vector<WorldMapStreet> WorldMap;


    class World
    {
    public:
        World(const int width, const int height);
        World(const std::pair<int, int> _size);
        int goTurn();
        int getTurn();
        int* getSize();
        Cell* getCell(const int x, const int y);
        WorldMap* _testGetMap();

    private:
        static World* w;
        thread_pool threadPool;
        int turn;
        int size[2];
        WorldMap map;  // map[y][x]
        void updateAllMap();
        void updateAllCells();
        void updateAllCellsPar();
        static void updateACellIStatic(const int i);
        void updateACell(const int i);
        void updateACell(const int x, const int y);
        void setMap();
        void fillMap();
    };
}

#endif
