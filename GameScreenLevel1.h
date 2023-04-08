#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Character.h"
#include "LevelMap.h"
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

class Character; 
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
    Texture2D* m_background_texture;
    bool SetUpLevel();
    CharacterMario* mario;
    CharacterLuigi* luigi;
    void SetLevelMap();
    LevelMap* m_level_map;
    PowBlock* m_pow_block;
public:
    GameScreenLevel1(SDL_Renderer* renderer);
    ~GameScreenLevel1();
    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
    void UpdatePOWBlock();
};
#endif