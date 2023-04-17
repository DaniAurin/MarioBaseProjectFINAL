#include "Koopa.h"
#include "constants.h"
#include "Character.h"

Koopa::Koopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

Koopa::~Koopa()
{

}
void Koopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}

void Koopa::Jump()
{
	if (!m_jumping)
	{
		m_jumping = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = true;
	}
}

void Koopa::FlipRightwayUp()
{
	if (m_facing_direction == 0)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}
	m_injured = false;
	Jump();
}

void Koopa::Render()
{
	//variable holds the left pos of sprite we want drawn :)) 
	int left = 0.0f;

	//if injured move the left position to be the left position of the second image of the sprite sheet!! :) 
	if (m_injured)
		left = m_single_sprite_w;


	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite} (IMPORTANT!)
	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w, m_single_sprite_h };

	//determines where its drawn from 
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction x
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void Koopa::Update(float deltaTime, SDL_Event e)
{
	//base class calling
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
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
	else
	{
		//moving when injured
		m_moving_right = false;
		m_moving_left = false;

		//countdown
		m_injured_time == deltaTime;
		if (m_injured_time <= 0.0)
			FlipRightwayUp();
	}
}

