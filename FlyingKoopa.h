#pragma once
#include "Character.h"
class FlyingKoopa :
	public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	FACING m_facing_direction;
	float m_movement_speed;

	float m_frame_delay;
	int m_current_frame;

public: 
	FlyingKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~FlyingKoopa();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};

