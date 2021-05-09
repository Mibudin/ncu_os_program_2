#include<stdio.h>
#include"cell.hpp"
#include"world.hpp"


int main()
{
    gol::World* w = new gol::World(2, 3);
    std::pair<int, int> s = w->getSize();
    s.first = 1;
    printf("> %d\n", w->getSize().first);

    return 0;
}
