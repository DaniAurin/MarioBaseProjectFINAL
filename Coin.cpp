#include "Coin.h"
#include "Character.h"
#include "constants.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_Position) : Character(renderer, imagePath, start_Position, map)
{
	m_position = start_Position;

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	m_coinCollect = false;

	m_current_frame = 0;
	m_frame_delay = FRAME_DELAY;
}
Coin::~Coin()
{

}

void Coin::Render()
{
	int left = m_current_frame * m_single_sprite_w;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite} (IMPORTANT!)
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0,m_single_sprite_w, m_single_sprite_h };
	//determines where its drawn from 
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}
void Coin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = FRAME_DELAY;
		m_current_frame++;

		if (m_current_frame > 3)
		{
			m_current_frame = 0;
		}
	}
}