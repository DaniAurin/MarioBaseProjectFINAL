#pragma once
#include <iostream>
#include "Texture2D.h"
#include "constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Commons.h"
#include <string>
#include "LevelMap.h"


class Texture2D;

class Character
{

protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_face_direction;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping = false;
	bool m_can_jump = false;
	float m_jump_force = INITIAL_JUMP_FORCE;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	float m_collision_radius;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void AddGravity(float deltaTime);
	virtual void JUMP();
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	LevelMap* m_current_level_map;

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }

	float GetCollisionRadius();
};

