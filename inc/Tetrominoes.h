#pragma once

enum tetromino_types
{
	TETROMINO_O = 0,
	TETROMINO_T = 1,
	TETROMINO_L = 2,
	TETROMINO_J = 3,
	TETROMINO_I = 4,
	TETROMINO_S = 5,
	TETROMINO_Z = 6
};

class Tetrominoes
{
public:
	int type = 0;
	int nextType = 0;

	int next[4][4] = { { 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 } };

	Tetrominoes();

	void Fall();

	int map[4][4] = { { 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 } };

	int x = 0;
	int y = 0;

	void reset();

	void setMap();

private:
	int O[4][4] = { { 0, 0, 0, 0 },
					{ 0, 2, 2, 0 },
					{ 0, 2, 2, 0 },
					{ 0, 0, 0, 0 } };

	int T[4][4] = { { 0, 0, 3, 0 },
					{ 0, 3, 3, 0 },
					{ 0, 0, 3, 0 },
					{ 0, 0, 0, 0 } };

	int L[4][4] = { { 0, 4, 0, 0 },
					{ 0, 4, 0, 0 },
					{ 0, 4, 4, 0 },
					{ 0, 0, 0, 0 } };

	int J[4][4] = { { 0, 0, 5, 0 },
					{ 0, 0, 5, 0 },
					{ 0, 5, 5, 0 },
					{ 0, 0, 0, 0 } };

	int I[4][4] = { { 0, 0, 6, 0 },
					{ 0, 0, 6, 0 },
					{ 0, 0, 6, 0 },
					{ 0, 0, 6, 0 } };

	int S[4][4] = { { 0, 0, 0, 0 },
					{ 0, 0, 7, 7 },
					{ 0, 7, 7, 0 },
					{ 0, 0, 0, 0 } };

	int Z[4][4] = { { 0, 0, 0, 0 },
					{ 8, 8, 0, 0 },
					{ 0, 8, 8, 0 },
					{ 0, 0, 0, 0 } };
};