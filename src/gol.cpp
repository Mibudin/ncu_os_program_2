#include<stdio.h>
#include"cell.hpp"
#include"world.hpp"
#include"thread_pool.hpp"
#include"screenio.hpp"


void _testPrintMap(gol::World* w);


int main()
{
    // 84 * 24
    // gol::World* w = new gol::World(2, 3);
    // std::pair<int, int> s = w->getSize();
    // s.first = 1;
    // printf("> %d\n", w->getSize().first);

    // gol::World* w = new gol::World(20, 20);
    // w->getCell(2, 1)->_testSetStatus(gol::CellStatus::LIVE, 0);
    // w->getCell(3, 2)->_testSetStatus(gol::CellStatus::LIVE, 0);
    // w->getCell(1, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    // w->getCell(2, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    // w->getCell(3, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);

    // _testPrintMap(w);

    // // timer tmr;
    // // tmr.stop();
    // for(int i = 0; i < 10; i++)
    // {
    //     w->goTurn();

    //     _testPrintMap(w);
    // }
    // // tmr.stop();

    // // _testPrintMap(w);

    // // printf("> %d\n", tmr.ms());

    gol::ScreenIO sio;
    sio.initTty();
    // ANSIES(CUP(7, 7));
    // ANSIES(CSI "7;7f");
    // ANSIES(CHA(7));
    ANSIES(CUP(7,8));
    // ANSIES(DSR);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    sio.uninitTty();

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
