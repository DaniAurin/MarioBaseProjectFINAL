#include "GameScreenYouWin.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "constants.h"
#include "Collisions.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"

GameScreenYouWin::GameScreenYouWin(SDL_Renderer* renderer, GameScreenManager* _screenManager) : GameScreen(renderer, _screenManager)
{
	SetUpLevel();
	m_level_map = nullptr;
}
GameScreenYouWin::~GameScreenYouWin()
{
	m_background_texture = nullptr;

	delete mario;
	mario = nullptr;
	delete luigi;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

}
void GameScreenYouWin::Render() 
{
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	mario->Render();
	luigi->Render();
	m_pow_block->Render();

	//draw background!! >:)
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}
void GameScreenYouWin::Update(float deltaTime, SDL_Event e) 
{
	/*
	* do the screen shake!! if needed <3
	*/
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration!!
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	//updating the chara!!
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	UpdatePOWBlock();
}
void GameScreenYouWin::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (mario->IsJumping())
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}

		}
	}
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (luigi->IsJumping())
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}

		}
	}
}
void GameScreenYouWin::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}
void GameScreenYouWin::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}
bool GameScreenYouWin::SetUpLevel()
{
	SetLevelMap();

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	//set up player character
	mario = new CharacterMario(m_renderer, "Images/MarioWalking2.png", Vector2D(64, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/LuigiWalking.png", Vector2D(64, 330), m_level_map);



	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/YouWin.png"))
	{
		std::cout << "Failed to load background texture!!!!" << std::endl;
		return false;
	}
	return true;
}
