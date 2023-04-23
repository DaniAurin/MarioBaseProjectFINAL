#include "TextRenderer.h"


TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;

}
TextRenderer::~TextRenderer()
{
	m_renderer = nullptr;

}

void TextRenderer::Render(int xpos, int ypos)
{
	
	text_rect.y = xpos;
	text_rect.x = ypos;

	SDL_RenderCopy(m_renderer, m_texture, nullptr , &text_rect);

}


bool TextRenderer::LoadFont(const std::string filePath, int font_size, const std::string message, SDL_Color)
{

   	TTF_Font* text_font = TTF_OpenFont(filePath.c_str(), font_size);
	SDL_Surface* text_surface = TTF_RenderText_Solid(text_font,  message.c_str(), { 0,0,0,255 });
	SDL_Texture* m_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);
	void TTF_CloseFont(TTF_Font * text_font);
	SDL_FreeSurface(text_surface);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);

	return m_texture;

}