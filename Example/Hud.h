#pragma once
#include "WaveManager.h"
#include <cstring>
#include <stdio.h>
#include "PlayerController.h"
#include "Base.h"
using namespace base;
class HUD
{
public:
	int TurretNum;
	void update(base::Text &scoreText, WaveManager &wave)
	{
		char buffer[80];
		sprintf_s(buffer, " Gold: %d \n Wave: %d \n Health: %d ", wave.gold, wave.Wave,wave.Health);

		scoreText.setString(buffer);
	}

	//void updateTurretText(Text &scoreText, PlayerController *PC)
	//{
	//	char buffer[80];
	//	if (PC->TurretNum == TurretNum)
	//	{
	//		if (PC->ActivateTurret[PC->TurretNum] == false)
	//		{
	//			sprintf_s(buffer, "Not Active");
	//		}
	//		if (PC->ActivateTurret[PC->TurretNum] == true)
	//		{
	//			sprintf_s(buffer, "Active");
	//		}
	//		if (PC->UpgradeTurret[PC->TurretNum] == true)
	//		{
	//			sprintf_s(buffer, "Upgrade Lv. I");
	//		}

	//	}
	//	

	//	scoreText.setString(buffer);
	//}
};