#pragma once
#ifndef CELL_H
#define CELL_H

#include"world.hpp"


// #define CELL_LIVE(status) ((status) & 1 == 1)
// #define CELL_DEAD(status) ((status) & 1 == 0)


namespace gol
{
    const int neighbors[8][2] =
        {{-1, -1}, {-1,  0}, {-1,  1},
         { 0, -1},           { 0,  1},
         { 1, -1}, { 1,  0}, { 1,  1}};

    enum CellStatus : int
    {
        DEAD = 0, LIVE = 1
    };


    class Cell
    {
        // friend class World;
    public:
        Cell();
        CellStatus* getStatus();
        void _testSetStatus(CellStatus _status, const int t);
        CellStatus interact(const WorldMap* map, const int size[2], const int x, const int y, const int turn);

    private:
        CellStatus status[2];
        int checkEnv(const WorldMap* map, const int size[2], const int x, const int y, const int t);
        CellStatus liveOrDie(const int liveCellCount, const int t);
    };
}

#endif
