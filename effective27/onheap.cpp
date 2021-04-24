//
// Created by peter on 4/24/21.
//
#include "iostream"

bool onHeap(const void* address)
{
    char onTheStack;
    return address < &onTheStack;
}

void allocateSomeObjects()
{
    char* pc = new char;
    bool res = onHeap(pc);
    std::cout << res << std::endl;
    char c;
    res = onHeap(&c);
    std::cout << res << std::endl;
    static char sc;
    res = onHeap(&sc);
    std::cout << res << std::endl;
}

int main()
{
//    char c1;
//    bool res = onHeap(&c1);
//    std::cout << res << std::endl;
//    delete c1;
    allocateSomeObjects();
    return 0;
}

