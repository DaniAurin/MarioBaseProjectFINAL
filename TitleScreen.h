#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Character.h"
#include "LevelMap.h"
#include <vector>

#ifndef _TITLESCREEN_H
#define _TITLESCREEN_H

class Character;

class TitleScreen : GameScreen 
{
private:
    Texture2D* m_background_texture;
    bool SetUpLevel();
    void SetLevelMap();
    LevelMap* m_level_map;
    bool m_screenshake;
    float m_shake_time;
    float m_wobble;
    float m_background_yPos;

    Vector2D m_position;

    float m_single_sprite_w;
    float m_single_sprite_h;

    float m_frame_delay;
    int m_current_frame;


public:
    TitleScreen(SDL_Renderer* renderer, GameScreenManager* _screenManager);
    ~TitleScreen();
    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
    void DoScreenshake();
};
#endif