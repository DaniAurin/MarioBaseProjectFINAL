#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "Collisions.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"



GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;

	delete mario;
	mario = nullptr;
	delete luigi;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

}
bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	//set up player character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) 
	{
		std::cout << "Failed to load background texture!!!!" << std::endl;
		return false;
	}
	return true;
}

void GameScreenLevel1::Render()
{
	m_background_texture->Render(Vector2D(0,0), SDL_FLIP_NONE);
	mario->Render();
	luigi->Render();
	m_pow_block->Render();

	//draw background!! >:)
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
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

	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Circle Hit!";
	}

	UpdatePOWBlock();

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
				                       { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					                   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
				                   	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                  	   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
				                 	   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
				                 	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                 	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                   	   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::UpdatePOWBlock()
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
}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

}