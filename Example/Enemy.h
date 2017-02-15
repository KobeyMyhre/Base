#pragma once
#include "Entity.h"
#include "WaveManager.h"
class Enemy
{
public:
	int health = 100;

	void TakeDamge()
	{
		health -= 2;
		
	}
	bool IsDead(WaveManager &Wave)
	{
		if (health <= 0)
		{
			Wave.gold += 5;
			return true;
		}
		else
		{
			return false;
		}
	}
	
};