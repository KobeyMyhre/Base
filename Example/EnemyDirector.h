#pragma once

#include "base.h"

using namespace base;

class EnemyDirector
{
public:
	bool right = true, down = false;
	bool Up = false, Left = false;
	//Rigidbody rbody;
	float speed = 50;

	void direct(Rigidbody *o_rb)
	{
		//if (dot(o_rb->velocity.normal(), vec2{ 1,0 }) >= .9f)
//			o_rb->velocity = vec2{ -100,0 };

		//if (dot(o_rb->velocity.normal(), vec2{ 0, -1 }) >= .9f)
//			o_rb->velocity = vec2{ 0, 100 };

		if (right == true)
		{
			o_rb->velocity = vec2{ speed, 0 };
			//o_rb->addForce(vec2{ 1,0 });
		}
		if (down == true)
		{
			o_rb->velocity = vec2{ 0,-speed };
			//o_rb->addForce(vec2{ 0,1 });
		}
		if (Up == true)
		{
			o_rb->velocity = vec2{ 0, speed };
			//o_rb->addForce(vec2{ 1,0 });
		}
		if (Left == true)
		{
			o_rb->velocity = vec2{ -speed,0 };
			//o_rb->addForce(vec2{ 0,1 });
		}
	}
};

//
//inline void EnemyDirDownResolution(EnemyDirector *ed, Rigidbody *rb)
//{
//
//	if (enemyD.right == true)
//	{
//		enemyD.down = true;
//		enemyD.right = false;
//	}
//
//}
