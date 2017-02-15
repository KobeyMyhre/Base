#pragma once

#include "Base.h"
#include "WaveManager.h"
class PlayerController
{

public:
	
	float speed = 10, turnSpeed = 1;
	int TurretSelction = 0;
	int TurretNum;
	int NumOfTurrets =4;
	float shotTimer = 1.f;
	bool shotRequest = false;
	bool ActivateTurret[4] = { false,false,false,false };
	bool ButtonPressedB = false;
	/*void poll(WaveManager &W)
	{
		if (ButtonPressedB == true)
		{
			
			ButtonPressedB = false;
		}
	}*/

	void TurretPlacement(base::Transform *T, base::Sprite *SP, WaveManager &W)
	{
		

		if (sfw::getKey('B') && W.Buildable == true )
		{
			ActivateTurret[TurretSelction] = true;
			W.gold = 0;
		}
		
		


		if (ActivateTurret[TurretNum] == true && TurretNum != TurretSelction)
		{
			SP->tint = WHITE;
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
			SP->tint = GREEN;
		}
		else if(ActivateTurret[TurretNum] == false && TurretNum != TurretSelction)
		{
			SP->tint = BLACK;
		}

	}



};