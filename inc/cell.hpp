#pragma once
#ifndef CELL_H
#define CELL_H

#include"world.hpp"


namespace gol
{
    enum CellStatus{LIVE, DEAD};


    class Cell
    {
        // friend class World;
    public:
        CellStatus geStatus();
        CellStatus checkEnv(WorldMap* map);
        CellStatus interact(WorldMap* map);

    private:
        CellStatus status;
    };
}

#endif
