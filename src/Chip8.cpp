#include "Chip8.h"
#include <stdio.h>
#include <random>
#include <boost/dynamic_bitset.hpp>

Chip8::Chip8() : rng(rd()), dis(0, 0xFF) {
    program_counter = 0x200; /// Program space starts at 0x200

    //Initialise current opcode, index register and stack pointer.
    opcode = 0;
    index_register = 0;
    stack_pointer = 0;

    const unsigned char chip8_fontset[80] =
            {
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

    //Load fontset
    for (int i = 0; i < 80; ++i) {
        memory[i] = chip8_fontset[i];
    }

    //Seed for andom gen engine.
}


void Chip8::loadGame(unsigned char *gameBuffer) {
    //TODO
    for (int i = 0; i < 80; ++i) {
        memory[i + 0x200] = gameBuffer[i];
    }
}

void Chip8::emulateCycle() {
    //Fetch
    opcode = memory[program_counter] << 8 | memory[program_counter + 1];

    int regIndex = (opcode & 0x0F00) >> 8;
    int regValue = opcode & 0x00FF;
    int regIndex2 = (opcode & 0x00F0) >> 4;
    //Decode

    switch (opcode & 0xF000) {
        //Compare against each opcode


        case 0x1000:
            program_counter = opcode & 0x0FFF;
            break;
        case 0x2000:
            stack[stack_pointer] = program_counter;
            stack_pointer++;
            program_counter = opcode & 0x0FFF;
            break;
        case 0x6000:
            general_registers[regIndex] = regValue;
            program_counter += 2;
            break;
        case 0x7000:
            general_registers[regIndex] += regValue;
            program_counter += 2;
            break;
        case 0x8000: {
            char subOpcode = opcode & 0x000f;

            if (subOpcode == 0) {
                general_registers[regIndex] = general_registers[regIndex2];
            }
            else if (subOpcode == 1) {
                //Or operation
                general_registers[regIndex] = general_registers[regIndex] | general_registers[regIndex2];
            }
            else if (subOpcode == 2) {
                //And operation
                general_registers[regIndex] = general_registers[regIndex] & general_registers[regIndex2];
            }
            else if (subOpcode == 3) {
                //XOR operation
                general_registers[regIndex] = general_registers[regIndex] ^ general_registers[regIndex2];
            }
            else if (subOpcode == 4) {
                unsigned short sumOfRegs = general_registers[regIndex] + general_registers[regIndex2];
                if (sumOfRegs > 255) {
                    general_registers[0xF] = 1;
                }
                else {
                    general_registers[0xf] = 0;
                }
                general_registers[regIndex] = sumOfRegs;
            }
            else if (subOpcode == 5) {
                int LHRegIndex = regIndex;
                int RHRegIndex = regIndex2;
                int ResultRegIndex = regIndex;

                minus(LHRegIndex, RHRegIndex, ResultRegIndex);

            }
            else if (subOpcode == 6) {
                // Get list significant bit.
                general_registers[0xF] = general_registers[regIndex] % 2;
                general_registers[regIndex] >>= 1;
            }
            else if (subOpcode == 7) {
                minus(regIndex2, regIndex, regIndex);
            }
            else if (subOpcode == 0xE) {
                // Get list significant bit.
                if (general_registers[regIndex] > 127) {
                    general_registers[0xF] = true;
                }
                else {
                    general_registers[0xF] = false;
                }
                general_registers[regIndex] <<= 1;
            }
            program_counter += 2;
        }
            break;
        case 0x9000:
            if (general_registers[regIndex] != general_registers[regIndex2]) {
                program_counter += 2;
            }
            program_counter += 2;
            break;
        case 0xA000:
            //Execute
            //ANNN sets I to the address NNN.
            //Get only address bits from the opcode.
            index_register = opcode & 0x0FFF;
            program_counter += 2;
            break;
        case 0xB000:
            program_counter = (opcode & 0x0FFF) + general_registers[0x0];
            break;
        case 0xC000:
            //TODO
            general_registers[regIndex] = dis(rng) & regValue;
            break;
        case 0xD000: {
            unsigned short x = regIndex;
            unsigned short y = regIndex2;
            unsigned short height = regValue;
            unsigned short pixels = memory[index_register + 0];

            general_registers[0xF] = 0;
            //For each column in row in gfx.
            for (int gfx_x = 0; gfx_x < 8; ++gfx_x) {
                //Line up pixel with gfx row for bitwise and check for each bit in row
                //If this is true then pixel will be cleared so set register F.
                unsigned short pixel = pixels >> gfx_x;
                //if (gfx[gfx_x + x] & pixel != 0) {
                //    general_registers[0xF] = 1;
                //}

                //Do the xor
                //gfx[gfx_x + x] ^= pixel;

            }
        }
            break;
        case 0x0000:
            //As first byte is 0 in both cases further check needed.
            if ((opcode & 0x00EE) == 0x00EE) {
                //TODO Dealing with 0x00EE

            }
            else {
                //Dealing with 0x00E0.
                //0x00E0 clears screen
                for (int i = 0; i < GFX_SIZE; ++i) {
                    //gfx[i].reset();
                }
                program_counter += 2;
            }
            break;
        default:
            printf("Unknown opcode: 0x%X\n", opcode);
    }

    //Update timers
    if (delay_timer > 0) {
        --delay_timer;
    }

    if (sound_timer > 0) {
        if (sound_timer == 1) {
            //TODO make beep happen.
            printf("BEEP!\n");
        }
        --sound_timer;
    }
}

void Chip8::minus(int LHRegIndex, int RHRegIndex, int ResultRegIndex) {
    unsigned short resultOfMinus = general_registers[LHRegIndex] - general_registers[RHRegIndex];
    if (resultOfMinus > 255) {
        general_registers[0xF] = 1;
    }
    else {
        general_registers[0xf] = 0;
    }

    general_registers[ResultRegIndex] = resultOfMinus;
}

void Chip8::setKeys() {
    //TODO
}

bool Chip8::getDrawFlag() {
    //TODO
    return true;
}


