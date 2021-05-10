#include<stdio.h>
#include"cell.hpp"
#include"world.hpp"
#include"thread_pool.hpp"


void _testPrintMap(gol::World* w);


int main()
{
    // gol::World* w = new gol::World(2, 3);
    // std::pair<int, int> s = w->getSize();
    // s.first = 1;
    // printf("> %d\n", w->getSize().first);

    gol::World* w = new gol::World(7, 7);
    w->getCell(2, 1)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(3, 2)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(1, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(2, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(3, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);

    _testPrintMap(w);

    for(int i = 0; i < 30; i++)
    {
        w->goTurn();

        _testPrintMap(w);
    }

    return 0;
}

void _testPrintMap(gol::World* w)
{
    gol::WorldMap* wm = w->_testGetMap();
    int* size = w->getSize();
    int turn = w->getTurn();

    printf("> %d\n", turn);
    gol::WorldMapStreet* wms;
    for(int i = 0; i < size[1]; i++)
    {
        gol::WorldMapStreet* wms = &((*wm)[i]);
        for(int j = 0; j < size[0]; j++)
        {
            printf("%c ", (*wms)[j]->getStatus()[turn & 1] == gol::CellStatus::LIVE ? 'O' : '.');
        }
        printf("\n");
    }
    printf("\n");

    return;
}
