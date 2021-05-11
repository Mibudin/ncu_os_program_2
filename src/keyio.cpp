#include<iostream>
#include<limits>
#include<stdio.h>
#include"keyio.hpp"


namespace gol
{
    int Keyio::blockWaitKey()
    {
        // std::cin.sync();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
        return (lastKey = getchar());
    }

    void Keyio::blockWaitKey(int key)
    {
        // std::cin.sync();
        // std::cin;
        printf("> %d", key);
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max());
        std::cin.sync();
        printf("> %d", key);
        // while(getchar() != key);
        char c;
        while(true)
        {
            std::cin.read(&c, 1);
            printf("%d ", c);
            if(c == key) break;
        };

        return;
    }

    int Keyio::getLastKey()
    {
        return lastKey;
    }
}
