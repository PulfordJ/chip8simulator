#include "Chip8.h"

void Chip8::loadGame(std::string) {
	//TODO
}

void Chip8::emulateCycle() {
	//Fetch
	opcode = memory[program_counter] << 8 | memory[program_counter + 1];
	//Decode
	if (opcode >= 0xA000 || opcode <= 0xAFFF) {
	  //Execute
	  //ANNN sets I to the address NNN.
	  //Get only address bits from the opcode.
	  index_register = opcode & 0x0FFF;
	  program_counter += 2;
	}
	//TOO
}

void Chip8::setKeys() {
	//TODO
}

bool Chip8::getDrawFlag() {
	//TODO
	return true;
}


