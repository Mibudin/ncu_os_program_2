#include<stdio.h>
#include<unistd.h>
#include<thread>
#include"cell.hpp"
#include"world.hpp"
// #include"thread_pool.hpp"
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

#define TURN_PERIOD    200
#define TURN_MAX      1000


void init();
void setMap(const int turn);
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

// timer tmr;


int main()
{
    init();

    setMap(0);
    
    // tmr.start();
    loop();
    // tmr.stop();

    deinit();

    // printf("> %d\n", tmr.ms());

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

void setMap(const int turn)
{
    rer->renderAll();

    bool nextWait = true;
    bool rerender = false;
    bool goDeinit = false;
    char c;
    int x = 0, y = 0;
    int t = turn & 1;

    ANSIES(CUP(3, 6) CUS);

    while(nextWait && kio->blockWaitKey())
    {
        switch(c = kio->getLastKey())
        {
            case 'W': case 'w':
                if(y > 0){ANSIES(CUU(1)); y--;}
                break;
            
            case 'S': case 's':
                if(y < WORLD_HEIGHT - 1){ANSIES(CUD(1)); y++;}
                break;

            case 'A': case 'a':
                if(x > 0){ANSIES(CUB(2)); x--;}
                break;

            case 'D': case 'd':
                if(x < WORLD_WIDTH - 1){ANSIES(CUF(2)); x++;}
                break;

            case '[':
                w->getCell(x, y)->setStatus(gol::CellStatus::DEAD, t);
                rerender = true;
                break;

            case ']':
                w->getCell(x, y)->setStatus(gol::CellStatus::LIVE, t);
                rerender = true;
                break;

            case '\\':
                nextWait = false;
                break;
            
            case 'P': case 'p':
                nextWait = false;
                goDeinit = true;
                break;

            case -1: default:
                // printf("> %d\n", c);
                break;
        }

        if(rerender)
        {
            ANSIES(CUH SCP);
            rer->renderAll();
            rerender = false;
            ANSIES(RCP CUS);
        }
    }

    ANSIES(CUH);

    if(goDeinit) deinit();

    return;
}

void loop()
{
    bool contLoop = true;
    bool backSet = false;
    bool goDeinit = false;

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
                case '\\':
                    backSet = true;
                    nextWait = false;
                    break;

                case 'P': case 'p':
                    goDeinit = true;
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
        if(backSet)
        {
            backSet = false;
            setMap(w->getTurn());
            w->backTurn();

            kio->startWait();
        }

        w->nextTurn();
    }

    if(goDeinit) deinit();

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

    exit(0);
    return;
}
