#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Character.h"
#include "constants.h"
#include "Collisions.h"
#include "CharacterMario.h"
#include "FlyingKoopa.h"
#include "CharacterLuigi.h"
#include "PowBlock.h"
#include "Coin.h"
#include "GameScreenYouWin.h"




GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* _screenManager) : GameScreen(renderer, _screenManager)
{

	SetUpLevel();
	m_level_map = nullptr;
	koopa_spawn_countdown = SPAWN_RATE;
	coinsRemaining = 5;
	mScore = 0;

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

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	m_enemies.clear();
	m_coins.clear();
	for (int i = 0; i < m_fkoopa.size(); i++)
	{
		delete m_fkoopa[i];
	}
	m_fkoopa.clear();

}
bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	//set up player character
	mario = new CharacterMario(m_renderer, "Images/MarioWalking2.png", Vector2D(64, 330), m_level_map);
	luigi = new CharacterLuigi(m_renderer, "Images/LuigiWalking.png", Vector2D(64, 330), m_level_map);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	CreateKoopa(Vector2D(170, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(240, 32), FACING_LEFT, KOOPA_SPEED);
	CreateFlyingKoopa(Vector2D(170, 20), FACING_RIGHT, KOOPA_SPEED);
	CreateFlyingKoopa(Vector2D(240, 20), FACING_LEFT, KOOPA_SPEED);
	CreateCoin(Vector2D(240, 32));
	CreateCoin(Vector2D(150, 32));
	CreateCoin(Vector2D(325, 32));
	CreateCoin(Vector2D(70, 32));
	CreateCoin(Vector2D(205, 32));



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
	//draw fkoopa
	for (int i = 0; i < m_fkoopa.size(); i++)
	{
		m_fkoopa[i]->Render();
	}
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
	//drawing coin
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

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
	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);
	UpdateFlyingKoopa(deltaTime, e);

	UpdateCoin(deltaTime, e);

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
				                       { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					                   { 0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					                   { 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
				                   	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                  	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                 	   { 1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
				                 	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                 	   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
				                   	   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

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
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (luigi->IsJumping())
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}

		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.5f)) 
					m_enemies[i]->SetAlive(false);
				
			}
			//now do the update

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						mario->SetAlive(false);
						mario->SetPosition(Vector2D(500, 1000));
					}

				}
			}
			if (Collisions::Instance()->Circle(m_enemies[i], luigi))
			{
				if (m_enemies[i]->GetInjured())
				{
					m_enemies[i]->SetAlive(false);
				}
				else
				{
					luigi->SetAlive(false);
					luigi->SetPosition(Vector2D(500, 1000));
				}

			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}

}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{

	Koopa* characterKoopa = new Koopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed);
	m_enemies.push_back(characterKoopa);
}

void GameScreenLevel1::UpdateCoin(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(m_coins[i], mario))
			{
				m_coins[i]->SetAlive(false);
				coinsRemaining--;
				mScore += 10;
			}
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
			if (Collisions::Instance()->Circle(m_coins[i], luigi))
			{
				m_coins[i]->SetAlive(false);
				coinsRemaining--;
				mScore += 10;
			}
			if (!m_coins[i]->GetAlive())
			{
				coinIndexToDelete = i;
			}
		}
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}

	if (coinsRemaining == 0)
	{
		GameScreen::screenManager->ChangeScreen(SCREEN_LEVEL2);
	}


}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	Coin* characterCoin = new Coin(m_renderer, "Images/Coin.png", m_level_map, position);
	m_coins.push_back(characterCoin);
}

void GameScreenLevel1::UpdateFlyingKoopa(float deltaTime, SDL_Event e)
{
	if (!m_fkoopa.empty())
	{
		int fkoopaIndexToDelete = -1;
		for (unsigned int i = 0; i < m_fkoopa.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_fkoopa[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_fkoopa[i]->GetPosition().x < (float)(-m_fkoopa[i]->GetCollisionBox().width * 0.5f) || m_fkoopa[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_fkoopa[i]->GetCollisionBox().width * 0.5f))
					m_fkoopa[i]->SetAlive(false);

			}
			//now do the update

			m_fkoopa[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_fkoopa[i]->GetPosition().y > 300.0f || m_fkoopa[i]->GetPosition().y <= 64.0f) && (m_fkoopa[i]->
				GetPosition().x < 64.0f || m_fkoopa[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_fkoopa[i], mario))
				{
						mario->SetAlive(false);
						mario->SetPosition(Vector2D(500, 1000));

				}
                if (Collisions::Instance()->Circle(m_fkoopa[i], luigi))
				{
					luigi->SetAlive(false);
					luigi->SetPosition(Vector2D(500, 1000));

				}
			}


			//if the enemy is no longer alive then schedule it for deletion
			if (!m_fkoopa[i]->GetAlive())
			{
				fkoopaIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (fkoopaIndexToDelete != -1)
		{
			m_fkoopa.erase(m_fkoopa.begin() + fkoopaIndexToDelete);
		}
	}
}
void GameScreenLevel1::CreateFlyingKoopa(Vector2D position, FACING direction, float speed)
{
	FlyingKoopa* characterFkoopa = new FlyingKoopa(m_renderer, "Images/flyingkoopa3.png", m_level_map, position, direction, speed);
	m_fkoopa.push_back(characterFkoopa);

}
