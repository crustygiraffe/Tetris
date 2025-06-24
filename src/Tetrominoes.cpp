#include "Tetrominoes.h"
#include <iostream>
#include "Tetris.h"
#include <cstdlib>
#include <ctime>

Tetrominoes::Tetrominoes()
	:x(4), y(0)
{
	srand(time(0));

	type = rand() % 7;

	switch (type)
	{
	case TETROMINO_O:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = O[i][j];
			}
		}
		break;
	}
	case TETROMINO_T:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = T[i][j];
			}
		}
		break;
	}
	case TETROMINO_L:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = L[i][j];
			}
		}
		break;
	}
	case TETROMINO_J:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = J[i][j];
			}
		}
		break;
	}
	case TETROMINO_I:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = I[i][j];
			}
		}
		break;
	}
	case TETROMINO_S:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = S[i][j];
			}
		}
		break;
	}
	case TETROMINO_Z:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				map[i][j] = Z[i][j];
			}
		}
		break;
	}
	}

	nextType = rand() % 7;

	this->setMap();
}

void Tetrominoes::reset()
{
	this->y = 0;
	this->x = 4;

	this->type = this->nextType;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->map[i][j] = this->next[i][j];
		}
	}
	
	this->nextType = rand() % 7;
	setMap();
}

void Tetrominoes::Fall()
{
	this->y += 1;
}

void Tetrominoes::setMap()
{


	switch (this->nextType)
	{
	case TETROMINO_O:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = O[i][j];
			}
		}
		break;
	}
	case TETROMINO_T:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = T[i][j];
			}
		}
		break;
	}
	case TETROMINO_L:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = L[i][j];
			}
		}
		break;
	}
	case TETROMINO_J:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = J[i][j];
			}
		}
		break;
	}
	case TETROMINO_I:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = I[i][j];
			}
		}
		break;
	}
	case TETROMINO_S:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = S[i][j];
			}
		}
		break;
	}
	case TETROMINO_Z:
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->next[i][j] = Z[i][j];
			}
		}
		break;
	}
	}
}