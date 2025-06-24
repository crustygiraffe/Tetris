#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class RenderWindow
{
public:
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	SDL_Renderer* renderer;

public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	void cleanUp();
	void clear();
	void display();

private:
	SDL_Window* window;
};