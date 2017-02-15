#pragma once

#include "Base.h"
#include "EnemyDirector.h"
#include "PlayerController.h"
#include "TurretRotation.h"
#include "Enemy.h"
#include "Hud.h"
using namespace base;


class Entity
{
public:
	ObjectPool<Transform>::iterator transform;
	ObjectPool<Rigidbody>::iterator rigidbody;
	ObjectPool<Collider>::iterator  collider;
	ObjectPool<Lifetime>::iterator lifetime;
	ObjectPool<Sprite>::iterator sprite;
	ObjectPool<Camera>::iterator camera;
	ObjectPool<Text>::iterator text;
	ObjectPool<EnemyDirector>::iterator enemyDirector;
	ObjectPool<TurretRotation>::iterator turretRotation;
	ObjectPool<Enemy>::iterator enemy;
	ObjectPool<HUD>::iterator hUD;
	// example of a component in this project
	ObjectPool<PlayerController>::iterator controller;

	void onFree()
	{
		transform.free();
		rigidbody.free();
		collider.free();
		lifetime.free();
		sprite.free();
		camera.free();
		text.free();
		enemyDirector.free();
		controller.free();
		turretRotation.free();
		enemy.free();
		hUD.free();
	}
};