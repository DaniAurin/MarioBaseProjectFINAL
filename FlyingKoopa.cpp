#include "FlyingKoopa.h"

FlyingKoopa::FlyingKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_current_frame = 0;
	m_frame_delay = KOOPA_F_DELAY;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}
FlyingKoopa::~FlyingKoopa()
{

}
void FlyingKoopa::Render() 
{
	int left = m_current_frame * m_single_sprite_w;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite} (IMPORTANT!)
	SDL_Rect portion_of_sprite = { m_single_sprite_w* m_current_frame, 0,m_single_sprite_w, m_single_sprite_h};
	//determines where its drawn from 
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h};

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}
void FlyingKoopa::Update(float deltaTime, SDL_Event e)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = KOOPA_F_DELAY;
		m_current_frame++;

		if (m_current_frame > 1)
		{
			m_current_frame = 0;
		}
	}

	if (m_position.x + m_single_sprite_w > SCREEN_WIDTH && m_facing_direction == FACING_RIGHT && m_position.y < 300.0f) {
		m_facing_direction = FACING_LEFT;
	}
	else if (m_position.x < 0 && m_facing_direction == FACING_LEFT && m_position.y < 300.0f) {
		m_facing_direction = FACING_RIGHT;
	}
	//enemy no injured so move go go!
	if (m_facing_direction == FACING_LEFT)
	{
			m_moving_left = false;
			m_moving_right = true;
			m_position.x -= KOOPA_SPEED;


	}
	else if (m_facing_direction == FACING_RIGHT)
	{
			m_moving_right = true;
			m_moving_left = false;
			m_position.x += KOOPA_SPEED;
	}
	

}
