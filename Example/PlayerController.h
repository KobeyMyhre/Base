#pragma once

#include "Base.h"
#include "WaveManager.h"
class PlayerController
{

public:
	
	//float speed = 10, turnSpeed = 1;
	//bool prev, cur;
	//bool buy = false;
	//bool Upgrade = false;

	int TurretSelction = 0;
	int TurretNum;
	int NumOfTurrets = 11;
	float ATKspeed = 1.5f;
	float shotTimer = ATKspeed;
	bool shotRequest = false;
	bool ActivateTurret = false; // [8] = { false,false,false,false,false,false,false,false };
	bool UpgradeTurret = false; // [8] = { false,false,false,false ,false,false,false,false };
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
		if (UpgradeTurret == true)
		{
			ATKspeed = 1.0f;
			

		}
	}

	float BTimer = 0;
	float VTimer = 0;

	void TurretPlacement(base::Transform *T, base::Sprite *SP,  WaveManager &W,float dt)
	{
		BTimer -= dt;
		VTimer -= dt;
		//shotTimer -= dt;
		
		//if (shotTimer > 0)
		//{
		//	shotRequest = false;
		//}

		if (TurretNum == TurretSelction)
		{
			if (BTimer <= 0 && sfw::getKey('B') && W.Buildable == true && ActivateTurret == false)
		{
			ActivateTurret = true;
			W.gold -= W.BuildCost;
			BTimer = 1.f;
			 
		}
		if ( VTimer <= 0 && sfw::getKey('V') && W.upgradeable == true && ActivateTurret == true && UpgradeTurret == false)
		{
			UpgradeTurret = true;
			//T->setGlobalScale(vec2{ 60, 60 });
			W.gold -= W.UpgradeCost;
			VTimer = 1.f;
			
		}
		}
		//if (BTimer <= 0 && sfw::getKey('B') && W.Buildable == true && ActivateTurret[TurretSelction] == false)
		//{
		//	ActivateTurret[TurretSelction] = true;
		//	W.gold -= W.BuildCost;
		//	BTimer = 1.f;
		//	 
		//}
		//if ( VTimer <= 0 && sfw::getKey('V') && W.upgradeable == true && ActivateTurret[TurretSelction] == true)
		//{
		//	UpgradeTurret[TurretSelction] = true;
		//	
		//	//T->setGlobalScale(vec2{ 60, 60 });
		//	W.gold -= W.UpgradeCost;
		//	VTimer = 1.f;
		//	
		//}
		


		if (ActivateTurret == true && TurretNum != TurretSelction )
		{
			SP->tint = WHITE;
		}
		
	}

	float MTimer = 0;
	float NTimer = 0;

	void NodeOperator(base::Transform *T, base::Sprite *SP, float dt)
	{
		//bool pressed = false;
		MTimer -= dt;
		NTimer -= dt;

		if (MTimer <= 0 && sfw::getKey('M'))
		{
			TurretSelction += 1;
			MTimer = 0.5F;
		}
		if (NTimer <= 0 && sfw::getKey('N'))
		{
			TurretSelction -= 1;
			NTimer = 0.5F;
		}

		if (TurretSelction > NumOfTurrets -1)
		{
			TurretSelction = 0;
		}
		if (TurretSelction < 0)
		{
			TurretSelction = NumOfTurrets - 1;
		}



		/*if (sfw::getKey('1') )
		{
			TurretSelction = 0;
		}
		if (sfw::getKey('2'))
		{
			TurretSelction = 1;
		}
		if (sfw::getKey('3'))
		{
			TurretSelction = 2;
		}
		if (sfw::getKey('4'))
		{
			TurretSelction = 3;
		}
		if (sfw::getKey('5'))
		{
			TurretSelction = 4;
		}
		if (sfw::getKey('6'))
		{
			TurretSelction = 5;
		}
		if (sfw::getKey('7'))
		{
			TurretSelction = 6;
		}
		if (sfw::getKey('8'))
		{
			TurretSelction = 7;
		}*/
	



	/*	if (TurretSelction >= NumOfTurrets)
		{
			TurretSelction = 0;
		}*/

		

		if (TurretNum == TurretSelction)
		{
			SP->tint = CYAN;
		}
		else if(ActivateTurret == false && TurretNum != TurretSelction )
		{
			SP->tint = BLACK;
		}
		else
		{
			SP->tint = WHITE;
		}

	}



};