#include "Chip8.h"
#include <stdio.h>

Chip8::Chip8() {
	program_counter	= 0x200; /// Program space starts at 0x200

	//Initialise current opcode, index register and stack pointer.
	opcode = 0; 
	index_register = 0;
	stack_pointer = 0;

	//Load fontset
	for (int i = 0; i < 80; ++i){
		//TODO memory[i] = chip8_fontset[i];
	}

	

}


void Chip8::loadGame(int * gameBuffer) {
	//TODO
	for (int i = 0; i < 80; ++i){
	  memory[i + 0x200] = gameBuffer[i];
	}
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

	switch(opcode & 0x0FFF)
	{
		//Compare against each opcode
		case 0xA000:
			//Execute
	  		//ANNN sets I to the address NNN.
	  		//Get only address bits from the opcode.
	  		index_register = opcode & 0x0FFF;
	  		program_counter += 2;
			break;
		//TODO need inner switch to handle 0x00E0 and 0x00EE 
		//As first four bits are 00 in both cases.
		default:
			printf("Unknown opcode: 0x%X\n", opcode);
	}
	
	//Update timers
	if (delay_timer > 0){
		--delay_timer;
	}

	if (sound_timer > 0) {
		if (sound_timer == 1)  {
			//TODO make beep happen.
			printf("BEEP!\n");
		}
		--sound_timer;
	}
}

void Chip8::setKeys() {
	//TODO
}

bool Chip8::getDrawFlag() {
	//TODO
	return true;
}


