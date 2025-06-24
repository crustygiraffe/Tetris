#include "Tetris.h"
#include "RenderWindow.h"

int main(int argc, char* args[])
{
	RenderWindow window("GAME v1.0", 680, 700);

	Tetris(window);

	return 0;
}