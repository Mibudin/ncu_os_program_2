#include<stdio.h>
#include"config.hpp"
#include"textarea.hpp"
#include"screenio.hpp"


namespace gol
{
    Textarea::Textarea(World* wld)
    {
        this->wld = wld;

        this->start = (WORLD_WIDTH << 1) + 7;
        this->width = SCREEN_WIDTH - ((WORLD_WIDTH << 1) + 2 + 8);

        this->mode = SET;
    }

    void Textarea::setMode(const ModeType mode)
    {
        this->mode = mode;

        return;
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
        // Phase
        printf(CUP(6, %d) ECH(12), start + 2);
        switch(mode)
        {
            case SET: printf("Map Set Mode"); break;
            case RUN: printf("Map Run Mode"); break;
        }
        // Turn
        printf(CUP(8, %d) ECH(6), start + 8);
        printf("%d", wld->getTurn());
        // Turn Period
        printf(CUP(10, %d) ECH(6), start + 8);
        printf("%d", turnPeriod);
        // Cell Counts
        int lives = wld->getLiveCount();
        printf(CUP(12, %d) ECH(3), start + 11);
        printf("%d", lives);
        printf(CUP(13, %d) ECH(3), start + 11);
        printf("%d", WORLD_WIDTH * WORLD_HEIGHT - lives);
        // Control Guide
        switch(mode)
        {
            case SET:
                printf(CUP(15, %d) ECH(12), start + 2);
                printf("W, A, S, D:");
                printf(CUP(16, %d) ECH(12), start + 2);
                printf(" Move cursor");
                printf(CUP(17, %d) ECH(12), start + 2);
                printf("[: Set dead");
                printf(CUP(18, %d) ECH(12), start + 2);
                printf("]: Set live");
                printf(CUP(19, %d) ECH(12), start + 2);
                printf(";: Slower");
                printf(CUP(20, %d) ECH(12), start + 2);
                printf("': Faster");
                printf(CUP(21, %d) ECH(12), start + 2);
                printf("\\: Run map");
                printf(CUP(22, %d) ECH(12), start + 2);
                printf("P: Exit game");
                break;
            case RUN:
                printf(CUP(15, %d) ECH(12), start + 2);
                printf(";: Slower");
                printf(CUP(16, %d) ECH(12), start + 2);
                printf("': Faster");
                printf(CUP(17, %d) ECH(12), start + 2);
                printf("\\: Set map");
                printf(CUP(18, %d) ECH(12), start + 2);
                printf("P: Exit game");
                printf(CUP(19, %d) ECH(12), start + 2);
                printf(CUP(20, %d) ECH(12), start + 2);
                printf(CUP(21, %d) ECH(12), start + 2);
                printf(CUP(22, %d) ECH(12), start + 2);
                break;
        }

        ANSIES("");

        return;
    }

    void Textarea::renderInit()
    {
        ANSIES(DEC(0));

        // Title
        renderBar(2, TOP);
        renderSpace(3);
        renderBar(4, BUT);
        // Phase
        renderBar(5, TOP);
        renderSpace(6);
        // Turn
        renderBar(7, MID);
        renderSpace(8);
        // Turn Period
        renderBar(9, MID);
        renderSpace(10);
        // Cell Counts
        renderBar(11, MID);
        renderSpace(12);
        renderSpace(13);
        // Control Guide
        renderBar(14, MID);
        renderSpace(15);
        renderSpace(16);
        renderSpace(17);
        renderSpace(18);
        renderSpace(19);
        renderSpace(20);
        renderSpace(21);
        renderSpace(22);
        renderBar(23, BUT);

        ANSIES(DEC(B));

        // Title
        printf(CUP(3, %d), start + 2);
        printf("Game of Life");
        // Phase
        // ...
        // Turn
        printf(CUP(8, %d), start + 2);
        printf("Turn:");
        // TurnPeriod
        printf(CUP(10, %d), start + 2);
        printf("T.P.:");
        // Cell Counts
        printf(CUP(12, %d), start + 2);
        printf("Live C.:");
        printf(CUP(13, %d), start + 2);
        printf("Dead C.:");
        // Control Guide
        // ...

        this->render();

        return;
    }
}
