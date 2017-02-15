#pragma once
#include "Enemy.h"
#include "WaveManager.h"
class EndBox
{
public:
	inline void end(WaveManager &wave, Enemy *E)
	{
		if (E->MadeIt == false)
		{
			wave.Health -= 1;
			E->MadeIt = true;
		}
	}
};