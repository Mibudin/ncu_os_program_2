#pragma once
#ifndef KEYIO_H
#define KEYIO_H


#define CTRL(k) ((k) & 0x1f)


namespace gol
{
    class Keyio
    {
    public:
        int blockWaitKey();
        void blockWaitKey(int key);
        int getLastKey();

    private:
        int lastKey;
    };
}

#endif
