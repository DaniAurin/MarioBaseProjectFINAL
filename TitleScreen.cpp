#include "TitleScreen.h"
#include "GameScreen.h"
#include "Character.h"
#include "constants.h"


TitleScreen::TitleScreen(SDL_Renderer* renderer, GameScreenManager* _screenManager) : GameScreen(renderer, _screenManager)
{
	SetUpLevel();
	m_level_map = nullptr;
	Vector2D start_Position = m_position;

	m_single_sprite_w = m_background_texture->GetWidth() / 3;
	m_single_sprite_h = m_background_texture->GetHeight();


	m_current_frame = 0;
	m_frame_delay = FRAME_DELAY;
}
TitleScreen::~TitleScreen()
{
	m_background_texture = nullptr;

}
void TitleScreen::Render()
{
	int left = m_current_frame * m_single_sprite_w;

	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite} (IMPORTANT!)
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0,m_single_sprite_w, m_single_sprite_h };
	//determines where its drawn from 
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_background_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);

}
void TitleScreen::Update(float deltaTime, SDL_Event e)
{

	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = FRAME_DELAY;
		m_current_frame++;

		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			GameScreen::screenManager->ChangeScreen(SCREEN_LEVEL1);
			break;
		case SDLK_q:
			exit(3);
			break;
		}
		break;
	}
}
void TitleScreen::DoScreenshake()
{

}
void TitleScreen::SetLevelMap()
{

}
bool TitleScreen::SetUpLevel()
{
	SetLevelMap();

	m_screenshake = false;
	m_background_yPos = 0.0f;

	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/TitleScreen.png"))
	{
		std::cout << "Failed to load background texture!!!!" << std::endl;
		return false;
	}
	return true;
}