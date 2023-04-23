#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer, GameScreenManager* _screenManager)
{
	screenManager = _screenManager;
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}
