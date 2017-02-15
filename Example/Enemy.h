#pragma once
#include "Entity.h"
#include "WaveManager.h"
class Enemy
{
public:
	int health = 100;
	bool MadeIt = false;
	void TakeDamge()
	{
		health -= 2;
		
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
			Wave.gold += 5;
			
			return true;
		}
		else
		{
			return false;
		}
	}
	
};