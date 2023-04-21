#include "CharacterMario.h"
#include "Character.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_single_sprite_w = m_texture->GetWidth() / 4;
	m_single_sprite_h = m_texture->GetHeight();


	m_current_frame = 0;
	m_frame_delay = FRAME_DELAY;

	m_face_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (m_texture->LoadFromFile(imagePath) == false) {
		std::cerr << "Image could not be loaded from " << imagePath << std::endl;
	}
}

void CharacterMario::FlipRightwayUp()
{
	if (m_facing_direction == 0)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}

}
void CharacterMario::Render()
{
	int left = m_current_frame * m_single_sprite_w;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite} (IMPORTANT!)
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0,m_single_sprite_w, m_single_sprite_h };
	//determines where its drawn from 
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = FRAME_DELAY;
		m_current_frame++;

		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}


	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			if (m_can_jump)
			{
				JUMP();
			}
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}
	if (m_moving_left) {
		MoveLeft(deltaTime);

	}
	else if (m_moving_right) {
		MoveRight(deltaTime);
	}

	Character::Update(deltaTime, e);
}

