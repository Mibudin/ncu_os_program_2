#pragma once
#ifndef TEXTAREA_H
#define TEXTAREA_H

#include"renderee.hpp"
#include"world.hpp"


namespace gol
{
    enum BarType : int
    {
        TOP, MID, BUT
    };


    class Textarea : public IRenderee
    {
    public:
        Textarea(World* w);

    private:
        World* w;
        int start;
        int width;
        void renderSpace(const int y);
        void renderBar(const int y, const BarType type);
        bool needRender();
        void render();
        void renderInit();
    };
}

#endif
