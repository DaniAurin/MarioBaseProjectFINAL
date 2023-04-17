#pragma once
#include "Character.h"
class Koopa :
	public Character
{

public:
	Koopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~Koopa();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; };

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_injured_time;
	bool m_injured;
	void FlipRightwayUp();
	FACING m_facing_direction;
	float m_movement_speed;



};

