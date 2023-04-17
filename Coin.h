#pragma once
#include "Character.h"
class Coin :
	public Character
{
public:
	Coin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_Position);
	~Coin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool CoinCollectedYN() {return m_coinCollect;}

private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay;
	int m_current_frame;

	bool m_coinCollect;
};

