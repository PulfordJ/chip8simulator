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


void Chip8::loadGame(unsigned char * gameBuffer) {
	//TODO
	for (int i = 0; i < 80; ++i){
	  memory[i + 0x200] = gameBuffer[i];
	}
}

void Chip8::emulateCycle() {
	//Fetch
	opcode = memory[program_counter] << 8 | memory[program_counter + 1];
	//Decode

	switch(opcode & 0xF000)
	{
		//Compare against each opcode
		case 0xA000:
			//Execute
	  		//ANNN sets I to the address NNN.
	  		//Get only address bits from the opcode.
	  		index_register = opcode & 0x0FFF;
	  		program_counter += 2;
			break;

		case 0x1000:
			program_counter = opcode & 0x0FFF;
			break;
		case 0x2000:
			stack[stack_pointer] = program_counter;
			stack_pointer++;
			program_counter = opcode & 0x0FFF;
			break;

		case 0x0000:
			//As first byte is 0 in both cases further check needed.
			if ((opcode & 0x00EE) ==  0x00EE){
				//TODO Dealing with 0x00EE

			}
			else {
				//Dealing with 0x00E0.
				//0x00E0 clears screen
				for (int i = 0; i < GFX_SIZE; ++i) {
					gfx[i] = 0;
				}
				program_counter += 2;
			}
			break;
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


