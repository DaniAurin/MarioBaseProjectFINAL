#pragma once
#include <SDL.h>
#include "SDL2/SDL/SDL_ttf.h"
#include "Character.h"


class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void Render(int xpos, int ypos);

	
	bool LoadFont(const std::string filePath, int font_size, const std::string message, SDL_Color);

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	mutable SDL_Rect text_rect;
	TTF_Font* text_font;


};

