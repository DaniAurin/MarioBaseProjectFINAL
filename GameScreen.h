#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#ifndef _GAME_SCREEN-H
#define _GAME_SCREEN_H


class GameScreen
{
protected: 
	SDL_Renderer* m_renderer;

public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif 

