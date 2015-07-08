#ifndef D_Chip8_H
#define D_Chip8_H

#include <string>

class Chip8 {
public:
  Chip8(){};
  void loadGame(std::string);
  void emulateCycle();
  void setKeys();
  bool getDrawFlag();
  int DoSomething(std::string);
  
private:
  /* data */
  unsigned short opcode;
  unsigned char memory[4096];
  unsigned char general_registers[16];
  unsigned short index_register;
  unsigned short program_counter; 

  unsigned char gfx[64 * 32];
  unsigned char delay_timer;
  unsigned char sound_timer;

  unsigned short stack[16];
  unsigned short stack_pointer;

  unsigned char key[16];


};

#endif // D_Chip8_H
