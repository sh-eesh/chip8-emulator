#pragma once

#include <cstdint>

class Emulator
{
private:
    // 4KB of memory
    uint8_t memory[4096];

    // 16 general purpose registers
    uint8_t V[16]{};

    // Index register
    uint16_t I = 0;

    // Program counter
    uint16_t PC = 0x200;

    // Stack
    uint16_t stack[16]{};

    // Stack pointer
    uint8_t SP = 0;

    // Timers
    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

public:
    // Initialize the emulator
    void initialize();

    // Load roms
    bool loadROM(const char *fileName);

    // Fetch instructions
    uint16_t fetch();

    // Decode instrctions
    uint16_t decode(uint16_t instruction);

    // Execute instructions
    void execute(uint16_t instruction);
};
