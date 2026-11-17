#include "emulator.hpp"

#include <iostream>

int main()
{
    Emulator emulator;

    emulator.initialize();

    if (emulator.loadROM("roms/Sierpinski.ch8"))
    {
        std::cout << "ROM loaded successfully!\n";
    }
    else
    {
        std::cout << "Failed to load ROM!\n";
    }

    return 0;
}
