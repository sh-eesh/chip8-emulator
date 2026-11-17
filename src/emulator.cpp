#include "emulator.hpp"

#include <fstream>

// Fonts to be used by programs
const uint8_t fontset[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void Emulator::initialize()
{
    // Reset memory and registers
    for (int i = 0; i < 4096; i++)
    {
        memory[i] = 0;
    }

    for (int i = 0; i < 16; i++)
    {
        V[i] = 0;
    }

    // Reset CPU state
    I = 0;
    PC = 0x200;

    // Reset stack
    SP = 0;

    for (int i = 0; i < 16; i++)
    {
        stack[i] = 0;
    }

    // Reset timers
    delayTimer = 0;
    soundTimer = 0;

    // Load fontset into memory
    for (int i = 0; i < 80; i++)
    {
        memory[i] = fontset[i];
    }
}

bool Emulator::loadROM(const char *fileName)
{
    // Open ROM in binary mode and postion file ptr at the end
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);

    // Check file opened or not
    if (!file.is_open())
    {
        return false;
    }

    // Get the size of the ROM in bytes
    std::streamsize size = file.tellg();

    // Check if ROM fits in memory
    if (size <= 0 || size > 4096 - 0x200)
    {
        file.close();
        return false;
    }

    // Move file ptr at the beginning
    file.seekg(0, std::ios::beg);

    // Read ROM and copy it to memory from location 0x200
    file.read(reinterpret_cast<char *>(&memory[0x200]), size);

    // Check if read was successful
    if (!file)
    {
        file.close();
        return false;
    }

    // Close the file
    file.close();

    return true;
}
