#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class Texture
{
public:
	Texture();
	~Texture();
	void loadFromFile(std::string p_filePath, SDL_Renderer* &p_renderer);
	void loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* &renderer, TTF_Font* Font);
	void free();
	void setAlpha(Uint8 alpha);
	void render(int p_x, int p_y, SDL_Renderer* &p_renderer);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* m_Texture;

	int m_Width;
	int m_Height;
};