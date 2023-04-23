#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Character.h"
#include "LevelMap.h"
#include <vector>

#ifndef _GAMESCREENYOUWIN_H
#define _GAMESCREENYOUWIN_H

class Character;
class PowBlock;

class GameScreenYouWin : GameScreen
{
private:
    Texture2D* m_background_texture;
    bool SetUpLevel();
    CharacterMario* mario;
    CharacterLuigi* luigi;
    void SetLevelMap();
    LevelMap* m_level_map;
    PowBlock* m_pow_block;
    bool m_screenshake;
    float m_shake_time;
    float m_wobble;
    float m_background_yPos;


public:
    GameScreenYouWin(SDL_Renderer* renderer, GameScreenManager* _screenManager);
    ~GameScreenYouWin();
    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
    void UpdatePOWBlock();
    void DoScreenshake();
};
#endif