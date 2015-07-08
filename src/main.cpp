#include "Chip8.h"

Chip8 chip8;

int main(int argc, char **argv) 
{
	//setupGraphics
	//setupInput
	//
	//
	//Potentially this, but hopefully all in constructor.
	//chip8.initialize();
	chip8.loadGame("pong");

	for(;;)
	{
		chip8.emulateCycle();

		//If draw flag set, update screen.
		if (myChip8.getDrawFlag()){
			drawGraphics();
		}

		// Store key press state.
		Chip8.setkeys();
	}
	return 0;
}
