#include "Tetris.h"
#include "RenderWindow.h"

int main(int argc, char* args[])
{
	RenderWindow window("TETRIS", 680, 700);

	Tetris(window);

	return 0;
}