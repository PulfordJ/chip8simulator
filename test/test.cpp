#include <Chip8.h>
#include "HelloWorld.h"
#include "gtest/gtest.h"

TEST(InstructionTest, ANNNexecution) {
    Chip8 chip8;

    unsigned char game[2] = {0xA2, 0xF0};
    chip8.loadGame(game);
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x2F0, chip8.index_register);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}


TEST(InstructionTest, 0NNNexecution) {
    FAIL();
}

TEST(InstructionTest, 00E0execution) {
    Chip8 chip8;
    //TODO clearing gfx should really be tested
    // after an instruction that alters gfx

    unsigned char game[2] = {0x00, 0xE0};
    chip8.loadGame(game);
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();



    for (int i = 0; i < GFX_SIZE; i++) {
        EXPECT_EQ(0, chip8.gfx[i]);
        EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
    }

    //TODO clearing gfx should really be tested
    // after an instruction that alters gfx
    FAIL();

}

TEST(InstructionTest, 1NNNexecution) {
    Chip8 chip8;

    unsigned char game[2] = {0x10, 0xE0};
    chip8.loadGame(game);
    chip8.emulateCycle();

    EXPECT_EQ(0x0E0, chip8.program_counter);
}

TEST(InstructionTest, 2NNNexecution) {
    Chip8 chip8;

    unsigned char game[4] = {0x20, 0xF0};
    chip8.loadGame(game);

    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x0F0, chip8.program_counter);
    EXPECT_EQ(1, chip8.stack_pointer);
    EXPECT_EQ(program_counter_before_cycle, chip8.stack[chip8.stack_pointer-1]);
}

TEST(InstructionTest, 3XNNexecution) {
    FAIL();
}

TEST(InstructionTest, 4XNNexecution) {
    FAIL();
}

TEST(InstructionTest, 5XY0execution) {
    FAIL();
}

TEST(InstructionTest, 6XNNexecution) {
    Chip8 chip8;

    unsigned char game[2] = {0x61, 0xC0};
    chip8.loadGame(game);
    chip8.emulateCycle();

    EXPECT_EQ(0xC0, chip8.general_registers[0x6]);
}
