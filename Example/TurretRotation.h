#pragma once

#include "Base.h"
#include "PlayerController.h"

using namespace base;
class TurretRotation
{
public:
	float m_dist = 345984398;


	void FaceEnemy(Transform *T, PlayerController *O_PC, Transform *O_T, float dt)
	{
		O_PC->shotTimer -= dt;
			if (O_PC->ActivateTurret == true && dist(T->getGlobalPosition(),O_T->getGlobalPosition()) < m_dist )
			{
				m_dist = dist(T->getGlobalPosition(), O_T->getGlobalPosition());
				float TargetAngle = (O_T->getLocalPosition() - T->getLocalPosition()).angle();
				T->setLocalAngle(TargetAngle - PI / 2);

				

				if (O_PC->shotTimer <= 0)
				{
					O_PC->shotRequest = true;
					O_PC->shotTimer = O_PC->ATKspeed;
				}
				else 
				{
					O_PC->shotRequest = false;
				}

				
			}
	
	}
	void ShutDown(PlayerController*O_PC)
	{
		O_PC->shotRequest = false;
	}
	//void FindEnemy(Enemy *E, Enemy *O_E)
	//{
	//	if (E->EnemyNum > O_E->EnemyNum)
	//	{
	//		E->Picked = true;
	//	}
	//	else
	//	{
	//		O_E->Picked = true;
	//	}
	//}
		
		


};