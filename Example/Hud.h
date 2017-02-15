#pragma once
#include "WaveManager.h"
#include <cstring>
#include <stdio.h>

#include "base\components\Text.h"
class HUD
{
public:

	void update(base::Text &scoreText, WaveManager &wave)
	{
		char buffer[80];
		sprintf_s(buffer, "Gold: %d", wave.gold);

		scoreText.setString(buffer);
	}
};