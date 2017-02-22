#pragma once
#include "Entity.h"
#include "WaveManager.h"
class Enemy
{
public:
	int health = 100;
	bool MadeIt = false;
	int EnemyNum;
	bool Picked = false;
	float colorTimer = 0.2f;
	void TakeDamge(Sprite *sp, float dt)
	{
		health -= 2;
		sp->tint = RED;
		
		

		
		
	}
	void UpdateCOLOR(Sprite *sp, float dt)
	{
		colorTimer -= dt;
		if (colorTimer <= 0)
		{
			sp->tint = WHITE;
			colorTimer = 0.2f;
		}
	}
	/*void updateHealth(WaveManager &Wave)
	{
		if (Wave.Wave != 0 && Wave.WaveStarted == false)
		{
			health = (Wave.Wave * 20) + 100;
		}
		
	}*/
	bool IsDead(WaveManager &Wave)
	{
		
		if (health <= 0)
		{
			Wave.gold += (Wave.Wave + 2);
			
			return true;
		}
		else
		{
			return false;
		}
	}
	
};