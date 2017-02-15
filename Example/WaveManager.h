#pragma once
class WaveManager
{
public:
	
	float SpawnTime = 1.f;
	float SpawnTimer = SpawnTime;

	int gold = 500;
	int BuildCost = 500;
	bool Buildable = false;

	inline void Generate()
	{
		gold++;
		if (gold >= 500)
		{
			gold = 500;
		}
		if (gold >= BuildCost)
		{
			Buildable = true;
		}
		else
		{
			Buildable = false;
		}
	}

};