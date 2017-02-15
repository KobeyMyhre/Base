#pragma once

#include "Base.h"
#include "PlayerController.h"

using namespace base;
class TurretRotation
{
public:

	void FaceEnemy(Transform *T, PlayerController *O_PC, Transform *O_T, float dt)
	{
		O_PC->shotTimer -= dt;
			if (O_PC->ActivateTurret[O_PC->TurretNum] == true)
			{
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
			else
			{
				T->setLocalAngle(0);
				O_PC->shotRequest = false;
			}
		}
		
		


};