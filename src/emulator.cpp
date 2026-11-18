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

uint16_t Emulator::fetch()
{
    // Read the first byte of instruction
    uint16_t instruction = memory[PC];

    // Shift it 8 bits left and combine it with second byte
    instruction = (instruction << 8) | memory[PC + 1];

    // Move to the next instruction
    PC += 2;

    return instruction;
}

uint16_t Emulator::decode(uint16_t instruction)
{
    // Extract the four hex digits
    uint16_t first = (instruction & 0xF000) >> 12;
    uint16_t second = (instruction & 0x0F00) >> 8;
    uint16_t third = (instruction & 0x00F0) >> 4;
    uint16_t fourth = instruction & 0x000F;

    return 0;
}

void Emulator::execute(uint16_t instruction)
{
    // Extract instruction type
    uint16_t first = (instruction & 0xF000) >> 12;

    // Extract register number
    uint16_t x = (instruction & 0x0F00) >> 8;

    // Extract the 8 bit value
    uint16_t nn = instruction & 0x00FF;

    // 6XNN Set VX to NN
    if (first == 0x6)
    {
        V[x] = nn;
    }
    // 7XNN Add NN to VX
    else if (first == 0x7)
    {
        V[x] += nn;
    }
    // 1NNN Jump to address NNN
    else if (first = 0x1)
    {
        // Extract 12 bit address
        uint16_t address = instruction & 0x0FFF;

        // Change program counter
        PC = address;
    }
}
