#pragma once

class WaveManager
{
public:
	bool WaveStarted = false;
	int Wave = 0;
	int Health = 10;
	float SpawnTime = 3.f;
	float SpawnTimer = SpawnTime;
	int EnemysToSpawn = 10;
	int EnemyCount = EnemysToSpawn;
	
	int gold = 800;
	int BuildCost = 800;
	bool Buildable = false;
	bool upgradeable = false;

	inline void Generate()
	{
		if (WaveStarted == true)
		{
			gold++;
		}
		
		if (gold >= 800)
		{
			gold = 800;
		}
		if (gold >= BuildCost)
		{
			Buildable = true;
		}
		if (gold >= (BuildCost / 2))
		{
			upgradeable = true;
		}
		else
		{
			Buildable = false;
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
				SpawnTime -= 0.2f;
			}
			
		}
	}

};