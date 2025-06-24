#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "RenderWindow.h"
#include "Texture.h"
#include "Tetrominoes.h"

static Texture squareWhite;
static Texture squareYellow;
static Texture squarePurple;
static Texture squareOrange;
static Texture squareBlue;
static Texture squareCyan;
static Texture squareGreen;
static Texture squareRed;
static Texture scoreText;
static Texture scoreValText;
static Texture lvlText;
static Texture lvlValText;
static Texture MenuLogo;
static Texture blackScreen;
static Texture blackPanel;
static Texture gameOverText;
static Texture playText;
static Texture settingsText;
static Texture quitText;
static Texture restartText;
static Texture gameBackToMenuText;
static Texture gameOverScoreText;
static Texture gameOverScoreValText;
static Texture gameOverLevelText;
static Texture gameOverLevelValText;
static Texture gameOverLinesText;
static Texture gameOverLinesValText;

static Tetrominoes mainPiece;

static TTF_Font* pixelFont = NULL;
static TTF_Font* bigPixelFont = NULL;

static Mix_Music* tetrisMusic = NULL;

static int grid[21][12] = {
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}
};

static int cleanGrid[21][12] = {
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
		{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}
};

bool static doesPieceFit(int px, int py, bool rotate)
{
	int tempMap[4][4];

	if (rotate)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				tempMap[i][j] = mainPiece.map[j][(0 - i) + 3];
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				tempMap[i][j] = mainPiece.map[i][j];
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tempMap[j][i] != 0)
			{
				if (grid[py + j][px + i] != 0)
				{
					return false;
				}
			}
		}
	}


	return true;
}

void Tetris(RenderWindow &window);

void init();