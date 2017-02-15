#pragma once

#include "Base.h"
#include "WaveManager.h"
class PlayerController
{

public:
	
	//float speed = 10, turnSpeed = 1;
	int TurretSelction = 0;
	int TurretNum;
	int NumOfTurrets =4;
	float ATKspeed = 1.5f;
	float shotTimer = ATKspeed;
	bool shotRequest = false;
	bool ActivateTurret[4] = { false,false,false,false };
	bool UpgradeTurret[4] = { false,false,false,false };
	bool ButtonPressedB = false;
	/*void poll(WaveManager &W)
	{
		if (ButtonPressedB == true)
		{
			
			ButtonPressedB = false;
		}
	}*/

	void TurretUpgrade(WaveManager &W)
	{
		if (UpgradeTurret[TurretNum] == true)
		{
			ATKspeed = 1.f;
			

		}
	}

	void TurretPlacement(base::Transform *T, base::Sprite *SP, WaveManager &W)
	{
		

		if (sfw::getKey('B') && W.Buildable == true && ActivateTurret[TurretSelction] == false)
		{
			ActivateTurret[TurretSelction] = true;
			W.gold = 0;
		}
		if (sfw::getKey('V') && W.upgradeable == true && ActivateTurret[TurretSelction] == true)
		{
			UpgradeTurret[TurretSelction] = true;
			//T->setGlobalScale(vec2{ 60, 60 });
			W.gold = 0;
		}
		


		if (ActivateTurret[TurretNum] == true && TurretNum != TurretSelction)
		{
			SP->tint = MAGENTA;
		}
		
	}
	void NodeOperator(base::Transform *T, base::Sprite *SP)
	{
		//bool pressed = false;
		if (sfw::getKey('C') )
		{
			TurretSelction += 1;
		}
	



		if (TurretSelction >= NumOfTurrets)
		{
			TurretSelction = 0;
		}

		if (TurretNum == TurretSelction)
		{
			SP->tint = RED;
		}
		else if(ActivateTurret[TurretNum] == false && TurretNum != TurretSelction)
		{
			SP->tint = BLACK;
		}

	}



};