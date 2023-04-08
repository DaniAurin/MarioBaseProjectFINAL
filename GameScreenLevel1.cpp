#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "Collisions.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"



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

}
bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();
	//set up player character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Mario1.png")) 
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

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//updating the chara!!
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Circle Hit!";
	}
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