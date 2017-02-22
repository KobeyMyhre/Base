#pragma once

class WaveManager
{
public:
	bool WaveStarted = false;
	int Wave = 0;
	int Health = 10;
	float SpawnTime = 3.5f;
	float SpawnTimer = SpawnTime;
	int EnemysToSpawn = 8;
	int EnemyCount = EnemysToSpawn;
	

	

	int gold = 50;
	int BuildCost = 50;
	int UpgradeCost = 25;
	bool Buildable = false;
	bool upgradeable = false;

	inline void Generate(float dt)
	{
		/*if (WaveStarted == true)
		{
			gold++;
		}*/
		
		/*if (gold >= 1600)
		{
			gold = 1600;
		}*/
		if (gold >= BuildCost)
		{
			Buildable = true;
		}
		else
		{
			Buildable = false;
		}

		if (gold >= UpgradeCost)
		{
			upgradeable = true;
		}
		else
		{
			upgradeable = false;
		}
	
	}

	inline void StartWave()
	{
		if (sfw::getKey(' ') && WaveStarted == false)
		{
			WaveStarted = true;
			Wave++;
		}
		if (EnemyCount <= 0)
		{
			
			WaveStarted = false;
			EnemysToSpawn += 2;
			
			EnemyCount = EnemysToSpawn;
			if (SpawnTime >= 0.5f)
			{
				SpawnTime -= 0.3f;
			}
			
		}
	}

};