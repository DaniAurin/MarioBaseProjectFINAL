#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenYouWin.h"
#include "TitleScreen.h"

class GameScreen;

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_current_screen = nullptr;
	m_renderer = renderer;
	ChangeScreen(startScreen);
}
GameScreenManager:: ~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;

}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}
void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}
	TitleScreen* temptitlescreen;
	GameScreenLevel1* tempScreen;
	GameScreenYouWin* tempScreenLevel2;
	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer, this);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		tempScreenLevel2 = new GameScreenYouWin(m_renderer, this);
		m_current_screen = (GameScreen*)tempScreenLevel2;
		tempScreenLevel2 = nullptr;
		break;
	case SCREEN_INTRO:
		temptitlescreen = new TitleScreen(m_renderer, this);
		m_current_screen = (GameScreen*)temptitlescreen;
		temptitlescreen = nullptr;
		break;
	}

}