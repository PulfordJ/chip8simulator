#ifndef D_Chip8_H
#define D_Chip8_H
#include <random>

static const int GFX_WIDTH = 64;
static const int GFX_HEIGHT = 32;
static const int GFX_SIZE = GFX_WIDTH * GFX_HEIGHT;

#include <string>
#include <boost/dynamic_bitset.hpp>

class Chip8 {
public:
  Chip8();
  void loadGame(unsigned char * gameBuffer);
  void emulateCycle();
  void setKeys();
  bool getDrawFlag();
  int DoSomething(std::string);
  
//TODO consider making private.
public:
  /* data */
  unsigned short opcode;
  unsigned char memory[4096];
  unsigned char general_registers[16];
  unsigned short index_register;
  unsigned short program_counter;

  //TODO http://stackoverflow.com/questions/12133950/creating-vector-of-boost-dynamic-bitset-in-c
  boost::dynamic_bitset<> gfx[GFX_HEIGHT];
  unsigned char delay_timer;
  unsigned char sound_timer;

  unsigned short stack[16];
  unsigned short stack_pointer;

  unsigned char key[16];


  void minus(int LHRegIndex, int RHRegIndex, int ResultRegIndex);
private:
  std::random_device rd;     // only used once to initialise (seed) engine
  std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)
  std::uniform_int_distribution<unsigned short> dis;


};

#endif // D_Chip8_H
