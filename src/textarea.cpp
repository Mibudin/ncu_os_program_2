#include<stdio.h>
#include"config.hpp"
#include"textarea.hpp"
#include"screenio.hpp"


namespace gol
{
    Textarea::Textarea(World* w)
    {
        this->w = w;

        this->start = (WORLD_WIDTH << 1) + 7;
        this->width = SCREEN_WIDTH - ((WORLD_WIDTH << 1) + 2 + 8);
    }

    void Textarea::renderSpace(const int y)
    {
        printf(CUP(%d, %d), y, start);
        printf(DEC_VFHN CHA(%d) DEC_VFHN, start + width + 1);

        return;
    }

    void Textarea::renderBar(const int y, const BarType type)
    {
        printf(CUP(%d, %d), y, start);
        switch(type)
        {
            case TOP: printf(DEC_VBHR CUF(%d) DEC_VBHL, width); break;
            case MID: printf(DEC_VFHR CUF(%d) DEC_VFHL, width); break;
            case BUT: printf(DEC_VTHR CUF(%d) DEC_VTHL, width); break;
        }

        printf(CHA(%d), start + 1);
        for(int i = 0; i < width; i++)
        {
            printf(DEC_VNHF);
        }

        return;
    }

    bool Textarea::needRender()
    {
        return true;
    }

    void Textarea::render()
    {
        // int width = SCREEN_WIDTH - ((WORLD_WIDTH << 1) + 2 + 8);

        // int turnPos = start + 2;
        // int tpPos = start

        // Turn
        printf(CUP(5, %d) ECH(6), start + 8);
        printf("%d", w->getTurn());
        // Turn Period
        printf(CUP(7, %d) ECH(6), start + 8);
        printf("%d", turnPeriod);
        // Cell Counts
        int lives = w->getLiveCount();
        printf(CUP(9, %d) ECH(3), start + 11);
        printf("%d", lives);
        printf(CUP(10, %d) ECH(3), start + 11);
        printf("%d", WORLD_WIDTH * WORLD_HEIGHT - lives);

        ANSIES("");

        return;
    }

    void Textarea::renderInit()
    {
        ANSIES(DEC(0));

        // Title
        renderBar(2, TOP);
        renderSpace(3);
        // Turn
        renderBar(4, MID);
        renderSpace(5);
        // Turn Period
        renderBar(6, MID);
        renderSpace(7);
        // Cell Counts
        renderBar(8, MID);
        renderSpace(9);
        renderSpace(10);
        renderBar(11, MID);

        ANSIES(DEC(B));

        // Title
        printf(CUP(3, %d), start + 2);
        printf("Game of Life");
        // Turn
        printf(CUP(5, %d), start + 2);
        printf("Turn:");
        // TurnPeriod
        printf(CUP(7, %d), start + 2);
        printf("T.P.:");
        // Cell Counts
        printf(CUP(9, %d), start + 2);
        printf("Live C.:");
        printf(CUP(10, %d), start + 2);
        printf("Dead C.:");

        this->render();

        return;
    }
}
