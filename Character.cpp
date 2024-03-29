#include "Character.h"
#include "constants.h"
#include "Texture2D.h"


Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_face_direction = FACING_RIGHT;
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_collision_radius = 15.0f;
	if (m_texture->LoadFromFile(imagePath) == false) 
	{
		std::cout << "Failed to load background texture!!!!" << imagePath << std::endl;
	}

	m_moving_left = false;
	m_moving_right = false;

}
Character :: ~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	 if (m_face_direction == FACING_RIGHT)
	 {
		 m_texture->Render(m_position, SDL_FLIP_NONE);
	 }
	 else
	 {
		 m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	 }
}
void Character::Update(float deltaTime, SDL_Event e)
{
	AddGravity(deltaTime);
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;

	}

}
void Character::SetPosition(Vector2D new_position)
{
	 m_position = new_position;
}
Vector2D Character::GetPosition()
{
	 return m_position;
}

void Character:: MoveLeft(float deltaTime)
{
	m_face_direction = FACING_LEFT;
	m_position.x -= MOVEMENTSPEED;

}

void Character::MoveRight(float deltaTime)
{
	m_face_direction = FACING_RIGHT;
	m_position.x +=  MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_can_jump = false;
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
	
}
void Character::JUMP()
{
	//JUMP
	m_jump_force = INITIAL_JUMP_FORCE;
	m_jumping = true;
	m_can_jump = false;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

