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

#define SCREEN_WIDTH    84
#define SCREEN_HEIGHT   24

#define WORLD_WIDTH     38
#define WORLD_HEIGHT    20

#define TURN_PERIOD    100
#define TURN_MAX      1000


void init();
void loop();
void deinit();


gol::World*    w;
gol::Screenio* sio;
gol::Keyio*    kio;
gol::Renderer* rer;

std::thread* thW;
std::thread* thR;
std::thread* thK;

std::chrono::steady_clock::duration dur;
std::chrono::steady_clock::time_point tp;

timer tmr;


int main()
{
    init();
    
    tmr.start();
    loop();
    tmr.stop();

    deinit();

    printf("> %d\n", tmr.ms());

    return 0;
}

void init()
{
    w   = new gol::World(WORLD_WIDTH, WORLD_HEIGHT);
    sio = new gol::Screenio();
    kio = new gol::Keyio();
    rer = new gol::Renderer();

    dur = std::chrono::milliseconds(TURN_PERIOD);

    w->setSampleMap();

    sio->initTty();

    rer->addRenderee(w);

    rer->renderInit();

    return;
}

void loop()
{
    bool contLoop = true;

    kio->startWait();

    for(int i = 0; contLoop && i < TURN_MAX; i++)
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
                    nextWait = false;
                    contLoop = false;
                    break;

                case -1: default:
                    break;
            }
            if(nextWait) kio->startWait();
        }

        thW->join();  // Process turn i + 1 complete
        thR->join();  // Render turn i complete

        free(thW); thW = nullptr;
        free(thR); thR = nullptr;

        std::this_thread::sleep_until(tp);

        // Enter other mode?

        w->nextTurn();
    }

    return;
}

void deinit()
{
    w->deinit();
    sio->deinitTty();

    free(w);
    free(sio);
    free(kio);
    free(rer);

    if(thW != nullptr) free(thW);
    if(thR != nullptr) free(thR);

    return;
}
