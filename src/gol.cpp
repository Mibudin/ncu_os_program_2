#include<stdio.h>
#include<unistd.h>
#include<thread>
#include"cell.hpp"
#include"world.hpp"
#include"thread_pool.hpp"
#include"screenio.hpp"
#include"keyio.hpp"
#include"renderer.hpp"
#include"renderee.hpp"


/**
 * Configurations
 */
#define WORLD_WIDTH  38
#define WORLD_HEIGHT 20


gol::World*    w;
gol::Screenio* sio;
gol::Keyio*    kio;
gol::Renderer* rer;


void init();



int main()
{
    init();

    w->getCell(2, 1)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(3, 2)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(1, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(2, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(3, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);

    sio->initTty();
    // std::this_thread::sleep_for(std::chrono::nanoseconds(5));

    rer->addRenderee(w);

    kio->startWait();

    std::thread* thW;
    std::thread* thR;
    std::thread* thK;

    std::chrono::steady_clock::duration dur = std::chrono::milliseconds(100);
    std::chrono::steady_clock::time_point tp;

    timer tmr;
    tmr.start();


    for(int i = 0; i < 1000; i++)
    {
        tp = std::chrono::steady_clock::now() + dur;

        thW = new std::thread(&gol::World::goTurn, w);
        thR = new std::thread(&gol::Renderer::renderAll, rer);

        if(kio->waitKeyAsync(tp))
        {
            bool nextWait = true;
            switch(kio->getLastKey())
            {
                case 'P': case 'p':
                    
                    break;

                case -1:
                default:
                    break;
            }
            if(nextWait) kio->startWait();
        }

        thW->join();  // Process turn i + 1 complete
        thR->join();  // Render turn i complete

        free(thW);
        free(thR);

        w->nextTurn();
    }

    tmr.stop();

    sio->uninitTty();

    printf("> %d\n", tmr.ms());

    return 0;
}

void init()
{
    w   = new gol::World(WORLD_WIDTH, WORLD_HEIGHT);
    sio = new gol::Screenio();
    kio = new gol::Keyio();
    rer = new gol::Renderer();
}
