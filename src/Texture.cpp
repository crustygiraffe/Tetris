#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Texture.h"

Texture::Texture()
	:m_Texture(NULL), m_Width(0), m_Height(0)
{}

Texture::~Texture()
{
	free();
}

void Texture::loadFromFile(std::string p_filePath, SDL_Renderer*& p_renderer)
{
	free();

	SDL_Texture* newTex = NULL;
	SDL_Surface* surface = NULL;
	surface = IMG_Load(p_filePath.c_str());

	m_Width = surface->w;
	m_Height = surface->h;

	newTex = SDL_CreateTextureFromSurface(p_renderer, surface);

	m_Texture = newTex;
}

void Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* &renderer, TTF_Font* Font)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor);

    m_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

    m_Width = textSurface->w;
    m_Height = textSurface->h;
    SDL_FreeSurface(textSurface);
}

void Texture::free()
{
	if (m_Texture == NULL)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void Texture::render(int p_x, int p_y, SDL_Renderer*& p_renderer)
{
	SDL_Rect renderQuad = { p_x, p_y, m_Width, m_Height };

	SDL_RenderCopy(p_renderer, m_Texture, NULL, &renderQuad);
}

int Texture::getWidth()
{
	return m_Width;
}

int Texture::getHeight()
{
	return m_Height;
}