#include "PowBlock.h"
#include "LevelMap.h"
#include <string>
#include <iostream>

using namespace std;

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/Objects/PowBlock.png";
	m_texture = new Texture2D(renderer);

	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Falied to load pow block texture: " << std::endl;
		return;
	}

	m_level_map = map;
	m_single_sprite_width = m_texture->GetWidth() / 3;
	m_single_sprite_height = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5F) - m_single_sprite_width * 0.5f, 260);
}

PowBlock::~PowBlock()
{
	m_renderer = nullptr;

	delete m_texture;
	m_texture = nullptr;

	m_level_map = nullptr;
}

void PowBlock::TakeHit()
{
	m_num_hits_left--;

	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;

		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}

void PowBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		//get the portion of the sheet we want to draw
		int left = m_single_sprite_width * (m_num_hits_left - 1);

		//				xPos,	yPos, sprite sheet width,sprite sheet height
		SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_width, m_single_sprite_height };

		//determine where to draw it
		SDL_Rect dest_rect = {
	static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_width, m_single_sprite_height
		};

		//draw the sprite
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);

	}
}