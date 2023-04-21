#pragma once
#include "Character.h"
class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	void Update(float deltaTime, SDL_Event e) override;
	void Render();


	void FlipRightwayUp();
	FACING m_facing_direction;

private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay;
	int m_current_frame;


};
