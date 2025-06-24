#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <string>

using namespace std;

#include "Tetris.h"
#include "RenderWindow.h"

enum MenuSelections
{
	PLAY = 1,
	SETTINGS = 2,
	QUIT = 3
};

int Speed = 20;
int speedCounter = 0;
bool pieceHitFloor = false;
bool gameOver = false;
bool menu = true;
int score = 0;
int level = 1;
int levelLines = 0;
int totalLines = 0;
int menuSelection = 1;
int gameOverSelection = 1;

SDL_Color black = { 0, 0, 0 };
SDL_Color white = { 255, 255, 255 };

int nextBox[6][6] = { 
					 { 1, 1, 1, 1, 1, 1 },
					 { 1, 0, 0, 0, 0, 1 },
					 { 1, 0, 0, 0, 0, 1 },
					 { 1, 0, 0, 0, 0, 1 },
					 { 1, 0, 0, 0, 0, 1 },
					 { 1, 1, 1, 1, 1, 1 } };

void rotate()
{
	int tempMap[4][4];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempMap[i][j] = mainPiece.map[i][j];
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mainPiece.map[i][j] = tempMap[j][(0 - i) + 3];
		}
	}
}

void gridReset()
{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (mainPiece.map[j][i] != 0)
				{
					grid[mainPiece.y + j][mainPiece.x + i] = 0;
				}
			}
		}
}


void shiftGrid(int line)
{
	int tempGrid[21][12];

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			tempGrid[i][j] = grid[i][j];
		}
	}

	for (int i = line; i > 0; i--)
	{
		for (int j = 0; j < 12; j++)
		{
			grid[i][j] = tempGrid[i - 1][j];
		}
	}
}

void checkLine()
{
	int linesCompleted = 0;
	for (int i = 0; i < 20; i++)
	{
		if ((grid[i][1] != 0) && (grid[i][2] != 0) && (grid[i][3] != 0) && (grid[i][4] != 0) && (grid[i][5] != 0) && (grid[i][6] != 0) && (grid[i][7] != 0) && (grid[i][8] != 0) && (grid[i][9] != 0) && (grid[i][10] != 0))
		{
			totalLines++;
			levelLines++;
			linesCompleted++;
			for (int j = 1; j < 11; j++)
			{
				grid[i][j] = 0;
			}
			shiftGrid(i);
		}
	}
	if (linesCompleted == 1)
		score += (100 * level);
	else if (linesCompleted == 2)
		score += (300 * level);
	else if (linesCompleted == 3)
		score += (500 * level);
	else if (linesCompleted == 4)
		score += (800 * level);
}

void resetGame(RenderWindow &window)
{
	score = 0;
	totalLines = 0;
	level = 1;
	levelLines = 0;
	Speed = 20;
	speedCounter = 0;
	scoreValText.loadFromRenderedText(std::to_string(score), white, window.renderer, pixelFont);
	lvlValText.loadFromRenderedText(std::to_string(level), white, window.renderer, pixelFont);
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			grid[i][j] = cleanGrid[i][j];
		}
	}
}

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		std::cout << "SDL_Init has failed. Error: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_Init has failed. Error: " << IMG_GetError() << std::endl;
	if(TTF_Init() == -1)
		std::cout << "TTF_Init has failed. Error: " << TTF_GetError() << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Mixer_Init has failed. Error: " << Mix_GetError() << std::endl;
}

void loadTextures(RenderWindow &window)
{
	squareWhite.loadFromFile("res/gfx/square_white.png", window.renderer);
	squareYellow.loadFromFile("res/gfx/square_yellow.png", window.renderer);
	squarePurple.loadFromFile("res/gfx/square_purple.png", window.renderer);
	squareOrange.loadFromFile("res/gfx/square_orange.png", window.renderer);
	squareBlue.loadFromFile("res/gfx/square_blue.png", window.renderer);
	squareCyan.loadFromFile("res/gfx/square_cyan.png", window.renderer);
	squareGreen.loadFromFile("res/gfx/square_green.png", window.renderer);
	squareRed.loadFromFile("res/gfx/square_red.png", window.renderer);
	MenuLogo.loadFromFile("res/gfx/tetrisLogo.png", window.renderer);
	blackScreen.loadFromFile("res/gfx/blackScreen.png", window.renderer);
	blackPanel.loadFromFile("res/gfx/blackScreen.png", window.renderer);
	blackPanel.setAlpha(200);

	pixelFont = TTF_OpenFont("res/ttf/slkscr.ttf", 30);
	scoreText.loadFromRenderedText("SCORE:", white, window.renderer, pixelFont);
	scoreValText.loadFromRenderedText(std::to_string(score), white, window.renderer, pixelFont);
	lvlText.loadFromRenderedText("LEVEL:", white, window.renderer, pixelFont);
	lvlValText.loadFromRenderedText(std::to_string(level), white, window.renderer, pixelFont);
	gameOverScoreText.loadFromRenderedText("SCORE:", white, window.renderer, pixelFont);
	gameOverScoreValText.loadFromRenderedText(std::to_string(score), white, window.renderer, pixelFont);
	gameOverLevelText.loadFromRenderedText("LEVEL:", white, window.renderer, pixelFont);
	gameOverLevelValText.loadFromRenderedText(std::to_string(level), white, window.renderer, pixelFont);
	gameOverLinesText.loadFromRenderedText("TOTAL LINES:", white, window.renderer, pixelFont);
	gameOverLinesValText.loadFromRenderedText(std::to_string(totalLines), white, window.renderer, pixelFont);
	playText.loadFromRenderedText("PLAY", white, window.renderer, pixelFont);
	settingsText.loadFromRenderedText("SETTINGS", white, window.renderer, pixelFont);
	quitText.loadFromRenderedText("QUIT", white, window.renderer, pixelFont);
	restartText.loadFromRenderedText("RESTART", white, window.renderer, pixelFont);
	gameBackToMenuText.loadFromRenderedText("BACK TO MENU", white, window.renderer, pixelFont);

	bigPixelFont = TTF_OpenFont("res/ttf/slkscr.ttf", 100);
	gameOverText.loadFromRenderedText("GAME OVER", white, window.renderer, bigPixelFont);

	tetrisMusic = Mix_LoadMUS("res/sfx/tetrisSong.wav");
	if (tetrisMusic == NULL)
	{
		std::cout << "Music no work. This is why: " << Mix_GetError();
	}
}

void Tetris(RenderWindow &window)
{
	init();
	loadTextures(window);

	SDL_Event e;

	bool gameRunning = true;

	while (gameRunning)
	{
 		this_thread::sleep_for(50ms);
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(tetrisMusic, -1);
		}
		if (!menu && !gameOver)
		{
			speedCounter++;

			if (pieceHitFloor && !gameOver)
			{
				mainPiece.reset();
				if (!doesPieceFit(mainPiece.x, mainPiece.y, false))
				{
					gameOver = true;
				}
				pieceHitFloor = false;
				checkLine();
				scoreValText.loadFromRenderedText(std::to_string(score), white, window.renderer, pixelFont);
			}

			if (levelLines >= 10)
			{
				level++;
				Speed -= 2;
				levelLines -= 10;
				lvlValText.loadFromRenderedText(std::to_string(level), white, window.renderer, pixelFont);
			}
			gridReset();
		}
		window.clear();

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				gameRunning = false;
			}

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_UP && doesPieceFit(mainPiece.x, mainPiece.y, true) && menu == false && gameOver == false)
				{
					rotate();
				}
				if (e.key.keysym.sym == SDLK_LEFT && doesPieceFit(mainPiece.x - 1, mainPiece.y, false) && menu == false && gameOver == false)
				{
					mainPiece.x -= 1;
				}
				if (e.key.keysym.sym == SDLK_RIGHT && doesPieceFit(mainPiece.x + 1, mainPiece.y, false) && menu == false && gameOver == false)
				{
					mainPiece.x += 1;
				}
				if (e.key.keysym.sym == SDLK_DOWN && doesPieceFit(mainPiece.x, mainPiece.y + 1, false) && menu == false && gameOver == false)
				{
					mainPiece.Fall();
				}
				if (e.key.keysym.sym == SDLK_SPACE && doesPieceFit(mainPiece.x, mainPiece.y + 1, false) && menu == false && gameOver == false)
				{
					while (doesPieceFit(mainPiece.x, mainPiece.y + 1, false))
					{
						mainPiece.Fall();
					}
				}
				if (e.key.keysym.sym == SDLK_DOWN && menu == true)
				{
					if (menuSelection < 3)
						menuSelection++;
				}
				if (e.key.keysym.sym == SDLK_UP && menu == true)
				{
					if (menuSelection > 1)
						menuSelection--;

				}
				if (e.key.keysym.sym == SDLK_SPACE && menu == true)
				{
					if (menuSelection == 1)
					{
						menu = false;
						resetGame(window);
					}
				}
				if (e.key.keysym.sym == SDLK_DOWN && gameOver == true)
				{
					if (gameOverSelection < 2)
						gameOverSelection++;
				}
				if (e.key.keysym.sym == SDLK_UP && gameOver == true)
				{
					if (gameOverSelection > 1)
						gameOverSelection--;

				}
				if (e.key.keysym.sym == SDLK_SPACE && gameOver == true)
				{
					if (gameOverSelection == 1)
					{
						resetGame(window);
						gameOver = false;
					}
					if (gameOverSelection == 2)
					{
						gameOver = false;
						menu = true;
					}
				}
			}
		}

		if (!gameOver && !menu)
		{

			if (speedCounter == Speed)
			{
				if (doesPieceFit(mainPiece.x, mainPiece.y + 1, false))
				{
					mainPiece.Fall();
				}
				else
				{
					pieceHitFloor = true;
				}
				speedCounter = 0;
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (mainPiece.map[j][i] != 0)
					{
						grid[mainPiece.y + j][mainPiece.x + i] = mainPiece.map[j][i];
					}
				}
			}
		}

		blackScreen.render(0, 0, window.renderer);

		if (menu)
		{
			MenuLogo.render(205, 50, window.renderer);
			
			if(menuSelection == 1)
			{
				playText.loadFromRenderedText(">PLAY", white, window.renderer, pixelFont);
				settingsText.loadFromRenderedText("SETTINGS", white, window.renderer, pixelFont);
				quitText.loadFromRenderedText("QUIT", white, window.renderer, pixelFont);
			}
			else if (menuSelection == 2)
			{
				playText.loadFromRenderedText("PLAY", white, window.renderer, pixelFont);
				settingsText.loadFromRenderedText(">SETTINGS", white, window.renderer, pixelFont);
				quitText.loadFromRenderedText("QUIT", white, window.renderer, pixelFont);
			}
			else if (menuSelection == 3)
			{
				playText.loadFromRenderedText("PLAY", white, window.renderer, pixelFont);
				settingsText.loadFromRenderedText("SETTINGS", white, window.renderer, pixelFont);
				quitText.loadFromRenderedText(">QUIT", white, window.renderer, pixelFont);
			}

			playText.render((680 - playText.getWidth()) / 2, 300, window.renderer);
			settingsText.render((680 - settingsText.getWidth()) / 2, 400, window.renderer);
			quitText.render((680 - quitText.getWidth()) / 2, 500, window.renderer);
		}
		else if (!menu)
		{
			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 12; j++)
				{
					if (grid[i][j] != 0)
					{
						switch (grid[i][j])
						{
						case 2:
							squareYellow.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 3:
							squarePurple.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 4:
							squareOrange.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 5:
							squareBlue.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 6:
							squareCyan.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 7:
							squareGreen.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 8:
							squareRed.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						case 9:
							squareWhite.render(120 + (30 * j), 30 + (30 * i), window.renderer);
							break;
						}
					}
				}
			}

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (nextBox[i][j] != 0)
					{
						squareWhite.render(490 + (30 * j), 60 + (30 * i), window.renderer);
					}
				}
			}

			scoreText.render(7, 30, window.renderer);
			scoreValText.render(7, 60, window.renderer);
			lvlText.render(7, 130, window.renderer);
			lvlValText.render(7, 160, window.renderer);

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (mainPiece.next[i][j] != 0)
					{
						switch (mainPiece.next[i][j])
						{
						case 2:
							squareYellow.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						case 3:
							squarePurple.render(520 + (30 * j),90 + (30 * i), window.renderer);
							break;
						case 4:
							squareOrange.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						case 5:
							squareBlue.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						case 6:
							squareCyan.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						case 7:
							squareGreen.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						case 8:
							squareRed.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						case 9:
							squareWhite.render(520 + (30 * j), 90 + (30 * i), window.renderer);
							break;
						}
					}
				}
			}
		}
		
		if (!menu && gameOver)
		{
			blackPanel.render((680 - blackPanel.getWidth()) / 2, (700 - blackPanel.getHeight()) / 2, window.renderer);
			gameOverText.render((680 - gameOverText.getWidth()) / 2, 30, window.renderer);

			gameOverScoreValText.loadFromRenderedText(std::to_string(score), white, window.renderer, pixelFont);
			gameOverLevelValText.loadFromRenderedText(std::to_string(level), white, window.renderer, pixelFont);
			gameOverLinesValText.loadFromRenderedText(std::to_string(totalLines), white, window.renderer, pixelFont);

			gameOverScoreText.render((680 - gameOverScoreText.getWidth()) / 10, 170, window.renderer);
			gameOverLevelText.render((680 - gameOverLevelText.getWidth()) / 2, 170, window.renderer);
			gameOverLinesText.render(425, 170, window.renderer);
			gameOverScoreValText.render((680 - gameOverScoreValText.getWidth()) / 10, 230, window.renderer);
			gameOverLevelValText.render((680 - gameOverLevelValText.getWidth()) / 2, 230, window.renderer);
			gameOverLinesValText.render(475, 230, window.renderer);

			if (gameOverSelection == 1)
			{
				restartText.loadFromRenderedText(">RESTART", white, window.renderer, pixelFont);
				gameBackToMenuText.loadFromRenderedText("BACK TO MENU", white, window.renderer, pixelFont);
			}
			else if (gameOverSelection == 2)
			{
				restartText.loadFromRenderedText("RESTART", white, window.renderer, pixelFont);
			    gameBackToMenuText.loadFromRenderedText(">BACK TO MENU", white, window.renderer, pixelFont);
			}

			restartText.render((680 - playText.getWidth()) / 2, 400, window.renderer);
			gameBackToMenuText.render((680 - settingsText.getWidth()) / 2, 500, window.renderer);
		}


		window.display();
	}

	window.cleanUp();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}