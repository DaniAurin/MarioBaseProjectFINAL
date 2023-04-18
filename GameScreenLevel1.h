#pragma once
#include "GameScreen.h"
#include "Commons.h"
#include "Koopa.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Character.h"
#include "LevelMap.h"
#include <vector>
#include "Coin.h"
#include "FlyingKoopa.h"
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
    bool m_screenshake;
    float m_shake_time;
    float m_wobble;
    float m_background_yPos;
    float koopa_spawn_countdown;

    void UpdateEnemies(float deltaTime, SDL_Event e);
    void CreateKoopa(Vector2D position, FACING direction, float speed);
    void UpdateCoin(float deltaTime, SDL_Event e);
    void CreateCoin(Vector2D position);
    void UpdateFlyingKoopa(float deltaTime, SDL_Event e);
    void CreateFlyingKoopa(Vector2D position, FACING direction, float speed);
    std::vector<FlyingKoopa*> m_fkoopa;
    std::vector<Koopa*> m_enemies;
    std::vector<Coin*> m_coins;
    int coinsRemaining;
    int mScore;

public:
    GameScreenLevel1(SDL_Renderer* renderer);
    ~GameScreenLevel1();
    void Render() override;
    void Update(float deltaTime, SDL_Event e) override;
    void UpdatePOWBlock();
    void DoScreenshake();
};
#endif