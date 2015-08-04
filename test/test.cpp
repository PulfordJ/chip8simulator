#include <Chip8.h>
#include "HelloWorld.h"
#include "gtest/gtest.h"



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
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0xC0, chip8.general_registers[0x01]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

TEST(InstructionTest, 6XNNexecutionV0) {
    Chip8 chip8;

    unsigned char game[2] = {0x60, 0x04};
    chip8.loadGame(game);
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x04, chip8.general_registers[0x00]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

TEST(InstructionTest, 7XNNexecution) {
    Chip8 chip8;

    unsigned char game[4] = {0x61, 0xC0, 0x71, 0x01};
    chip8.loadGame(game);
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0xC0 + 1, chip8.general_registers[0x01]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

TEST(InstructionTest, 8XY0execution) {
    Chip8 chip8;

    unsigned char game[4] = {0x61, 0xC0, 0x80, 0x10};
    chip8.loadGame(game);
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0xC0, chip8.general_registers[0x00]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

//OR
TEST(InstructionTest, 8XY1execution) {
    Chip8 chip8;

    unsigned char game[6] = {0x60, 0x02, 0x61, 0x01, 0x80, 0x11};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x03, chip8.general_registers[0x00]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

//AND
TEST(InstructionTest, 8XY2execution) {
    Chip8 chip8;

    unsigned char game[6] = {0x60, 0x02, 0x61, 0x01, 0x81, 0x02};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x00, chip8.general_registers[0x01]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

//XOR
TEST(InstructionTest, 8XY3execution) {
    Chip8 chip8;

    unsigned char game[6] = {0x60, 0x02, 0x61, 0x03, 0x81, 0x03};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x01, chip8.general_registers[0x01]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

//Add VX and VY
TEST(InstructionTest, 8XY4execution) {
    Chip8 chip8;

    unsigned char game[6] = {0x60, 0x02, 0x61, 0x03, 0x81, 0x04};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x05, chip8.general_registers[0x01]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
    EXPECT_EQ(0x00, chip8.general_registers[0xF]);
}

void instruction8XXXTest(unsigned char * game, int result_expected, int vf_carry_expected){
    Chip8 chip8;
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(result_expected, chip8.general_registers[0x01]);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
    EXPECT_EQ(vf_carry_expected, chip8.general_registers[0xF]);
}

//Add VX and VY with carry
TEST(InstructionTest, 8XY4executionWithCarry) {
    unsigned char game[6] = {0x60, 0xFF, 0x61, 0x01, 0x81, 0x04};
    int result_expected = 0x00;
    int vf_carry_expected = 0x01;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}


//Subtract VX and VY
TEST(InstructionTest, 8XY5execution) {
    unsigned char game[6] = {0x61, 0xFF, 0x60, 0x01, 0x81, 0x05};
    int result_expected = 0xFE;
    int vf_carry_expected = 0x00;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

//Subtract VX and VY with carry
TEST(InstructionTest, 8XY5executionWithCarry) {
    unsigned char game[6] = {0x61, 0xFE, 0x60, 0xFF, 0x81, 0x05};
    int result_expected = 0xFF;
    int vf_carry_expected = 0x01;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

TEST(InstructionTest, 8XY6execution) {
    unsigned char game[6] = {0x61, 0xFE, 0x60, 0x01, 0x81, 0x06};
    int result_expected = 0x7F;
    int vf_carry_expected = 0x00;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

TEST(InstructionTest, 8XY6executionWithCarry) {
    unsigned char game[6] = {0x61, 0xFF, 0x60, 0xFF, 0x81, 0x06};
    int result_expected = 0x7F;
    int vf_carry_expected = 0x01;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

TEST(InstructionTest, 8XY7execution) {
    unsigned char game[6] = {0x61, 0x05, 0x60, 0x07, 0x81, 0x07};
    int result_expected = 0x02;
    int vf_carry_expected = 0x00;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

TEST(InstructionTest, 8XY7executionWithCarry) {
    unsigned char game[6] = {0x61, 0x05, 0x60, 0x03, 0x81, 0x07};
    int result_expected = 0xFE;
    int vf_carry_expected = 0x01;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

TEST(InstructionTest, 8XYEexecution) {
    unsigned char game[6] = {0x61, 0x7F, 0x60, 0x01, 0x81, 0x0E};
    int result_expected = 0xFE;
    int vf_carry_expected = 0x00;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

TEST(InstructionTest, 8XYEexecutionWithCarry) {
    unsigned char game[6] = {0x61, 0xFF, 0x60, 0xFF, 0x81, 0x0E};
    int result_expected = 0xFE;
    int vf_carry_expected = 0x01;

    instruction8XXXTest(game, result_expected, vf_carry_expected);
}

//Add VX and VY
TEST(InstructionTest, 9XY0executionWithoutSkip) {
    Chip8 chip8;

    unsigned char game[6] = {0x60, 0x02, 0x61, 0x02, 0x91, 0x00};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

//Add VX and VY
TEST(InstructionTest, 9XY0executionWithSkip) {
    Chip8 chip8;

    unsigned char game[6] = {0x60, 0x02, 0x61, 0x03, 0x91, 0x00};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(program_counter_before_cycle + 4, chip8.program_counter);
}


TEST(InstructionTest, ANNNexecution) {
    Chip8 chip8;

    unsigned char game[2] = {0xA2, 0xF0};
    chip8.loadGame(game);
    unsigned short program_counter_before_cycle = chip8.program_counter;
    chip8.emulateCycle();

    EXPECT_EQ(0x2F0, chip8.index_register);
    EXPECT_EQ(program_counter_before_cycle + 2, chip8.program_counter);
}

TEST(InstructionTest, BNNNexecution) {
    Chip8 chip8;

    unsigned char game[4] = {0x60, 0x04, 0xB0, 0xE0};
    chip8.loadGame(game);
    chip8.emulateCycle();
    chip8.emulateCycle();

    EXPECT_EQ(0x0E0 + 0x4, chip8.program_counter);
}
