#include<stdio.h>
#include<unistd.h>
#include<thread>
#include<mutex>
#include<condition_variable>
#include"cell.hpp"
#include"world.hpp"
#include"thread_pool.hpp"
#include"screenio.hpp"
#include"keyio.hpp"
#include"renderer.hpp"
#include"renderee.hpp"


void _testPrintMap(gol::World* w);


gol::World* w = new gol::World(38, 20);
gol::Screenio* sio = new gol::Screenio();
gol::Keyio* kio = new gol::Keyio();
gol::Renderer* rer = new gol::Renderer();

std::mutex m1, m2;
std::condition_variable cv1, cv2;


void _testGoTurn()
{
    // std::unique_lock<std::mutex> lock(m1);

    // for(int i = 0; i < 100; i++)
    {
        // m1.lock();
        // cv1.wait(lock);

        w->goTurn();  // Process i + 1

        // m1.unlock();
        // std::this_thread::sleep_for(std::chrono::nanoseconds(5));
        // cv1.notify_all();
        // std::this_thread::sleep_for(std::chrono::nanoseconds(5));
        // m1.lock();
    }

    return;
}

void _testRenderAll()
{
    // std::unique_lock<std::mutex> lock(m2);

    // for(int i = 0; i < 100; i++)
    {
        // m2.lock();
        // cv2.wait(lock);

        rer->renderAll();  // Render i

        // m2.unlock();
        // std::this_thread::sleep_for(std::chrono::nanoseconds(5));
        // cv2.notify_all();
        // std::this_thread::sleep_for(std::chrono::nanoseconds(5));
        // m2.lock();
    }

    return;
}


int main()
{
    w->getCell(2, 1)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(3, 2)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(1, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(2, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);
    w->getCell(3, 3)->_testSetStatus(gol::CellStatus::LIVE, 0);

    sio->initTty();

    rer->addRenderee(w);

    // rer->renderAll();
    // thread_pool tp(2);

    timer tmr;
    tmr.start();


    // std::this_thread::sleep_for(std::chrono::nanoseconds(5));

    for(int i = 0; i < 1000; i++)
    {
        std::thread th1(&gol::World::goTurn, w);
        std::thread th2(&gol::Renderer::renderAll, rer);
        // std::thread th3();
        th1.join();
        th2.join();
        w->nextTurn();

        // w->goTurn();
        // rer->renderAll();
        // w->nextTurn();

        // tp.push_task(_testGoTurn);
        // tp.push_task(_testRenderAll);

        // tp.wait_for_tasks();

        // w->nextTurn();



        // cv1.notify_all();
        // cv2.notify_all();

        // {
        //     std::unique_lock<std::mutex> lock(m1);
        //     cv1.wait(lock);
        // }
        // {
        //     std::unique_lock<std::mutex> lock(m2);
        //     cv2.wait(lock);
        // }

        // w->nextTurn();

        // th1.join();
        // th2.join();
        // w->nextTurn();

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // w->goTurn();
        // w->nextTurn();

        // rer->renderAll();
    }
    // th1.join();
    // th2.join();
    tmr.stop();

    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    // kio->blockWaitKey(' ');
    sio->uninitTty();
    printf("> %d\n", tmr.ms());

    return 0;
}

// void _testPrintMap(gol::World* w)
// {
//     gol::WorldMap* wm = w->_testGetMap();
//     int* size = w->getSize();
//     int turn = w->getTurn();

//     printf("> %d\n", turn);
//     gol::WorldMapStreet* wms;
//     for(int i = 0; i < size[1]; i++)
//     {
//         gol::WorldMapStreet* wms = &((*wm)[i]);
//         for(int j = 0; j < size[0]; j++)
//         {
//             printf("%c ", (*wms)[j]->getStatus()[turn & 1] == gol::CellStatus::LIVE ? 'O' : '.');
//         }
//         printf("\n");
//     }
//     printf("\n");

//     return;
// }
