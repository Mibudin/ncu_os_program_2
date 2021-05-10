#include<stdio.h>
#include<thread>
#include"cell.hpp"
#include"world.hpp"


namespace gol
{
    Cell::Cell()
    {
        status[0] = DEAD;
        status[1] = DEAD;
    }

    CellStatus* Cell::getStatus()
    {
        return status;
    }

    void Cell::_testSetStatus(CellStatus _status, const int t)
    {
        status[t] = _status;

        return;
    }

    CellStatus Cell::interact(const WorldMap* map, const int size[2],
        const int x, const int y, const int turn)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        int t = turn & 1;
        int t2 = t ^ 1;
        status[t2] = liveOrDie(checkEnv(map, size, x, y, t), t);

        return status[t2];
    }

    int Cell::checkEnv(const WorldMap* map, const int size[2],
        const int x, const int y, const int t)
    {
        int liveCellCount = 0;
        int p, q;
        for(int i = 0; i < 8; i++)
        {
            p = x + neighbors[i][1];
            q = y + neighbors[i][0];

                 if(p < 0)        p += size[0];
            else if(p >= size[0]) p -= size[0];
                 if(q < 0)        q += size[1];
            else if(q >= size[1]) q -= size[1];

            liveCellCount += (*map)[q][p]->getStatus()[t] == LIVE ? 1 : 0;  // LIVE = 1
        }
        // if(liveCellCount != 0) printf("> %d, %d > %d\n", x, y, liveCellCount);
        
        return liveCellCount;
    }

    CellStatus Cell::liveOrDie(const int liveCellCount, const int t)
    {
        switch(status[t])
        {
            case DEAD:
                if(liveCellCount == 3) return LIVE;
                else                   return DEAD;
                break;
            case LIVE:
                     if(liveCellCount < 2) return DEAD;
                else if(liveCellCount > 3) return DEAD;
                else                       return LIVE;
                break;
        }
    }
}
