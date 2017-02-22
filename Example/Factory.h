#pragma once

#include "Entity.h"
#include "WaveManager.h"
#include <cstring>
class Factory
{	
	ObjectPool<Entity>	  entities;
	
	// The factory will store an object pool for each component type
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;
	ObjectPool<Text>	  texts;
	ObjectPool<PlayerController> controllers;
	ObjectPool<EnemyDirector> enemyDirectors;
	ObjectPool<TurretRotation> turretRotations;
	ObjectPool<Enemy> enemys;
	ObjectPool<HUD> HUDs;
	ObjectPool<EndBox> EndBoxs;
public:

	// iterators to access the entity pool
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	// for now, they're all the same size
	Factory(size_t size = 512)
								: entities(size), transforms(size), rigidbodies(size),
								  colliders(size), sprites(size), lifetimes(size),
								  cameras(size), controllers(size), texts(size), enemyDirectors(size),
									turretRotations(size), enemys(size), HUDs(size), EndBoxs(size)
	{
	}

	// What follows are specialized spawning functions
	// just observe the steps taken and replicate for your own usages

	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{w,h};
		e->transform->setLocalPosition(vec2{ x,y });	
		return e;
	}

	ObjectPool<Entity>::iterator spawnBullet(unsigned sprite, vec2 pos, vec2 dim, float ang, float impulse, unsigned faction)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		e->collider = colliders.push();

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);
		e->transform->setLocalAngle(ang);

		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{1.2f, 1.2f};

		e->rigidbody->addImpulse(e->transform->getGlobalUp() * impulse);

		e->lifetime->lifespan = 1.6f;
		
		return e;
	}

	ObjectPool<Entity>::iterator spawnHUD(unsigned font, WaveManager &Wave)
	{
		auto e = entities.push();
		e->hUD = HUDs.push();
		e->transform = transforms.push();
		e->text = texts.push();
		e->text->sprite_id = font;
		e->transform->setLocalScale(vec2{ 10,15 });
		e->transform->setLocalPosition(vec2{ 200,250 });

		
		//e->text->setString(buffer);

		return e;
	}
	//ObjectPool<Entity>::iterator spawnTurretText(float x,float y,unsigned font, int Num)
	//{
	//	auto e = entities.push();
	//	e->hUD = HUDs.push();
	//	e->transform = transforms.push();
	//	e->text = texts.push();
	//	e->text->sprite_id = font;
	//	e->transform->setLocalScale(vec2{ 10,15 });
	//	e->transform->setLocalPosition(vec2{ x,y });
	//	e->hUD->TurretNum = Num;

	//	//e->text->setString(buffer);

	//	return e;
	//}



	ObjectPool<Entity>::iterator spawnPlayer(unsigned sprite, unsigned font)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->controller = controllers.push();
		e->text = texts.push();

		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{.5f,.5f};
		e->text->setString("Player1");

		e->transform->setLocalScale(vec2{48,48});

		e->sprite->sprite_id = sprite;

		return e;
	}


	ObjectPool<Entity>::iterator spawnDir(float x, float y, bool right, bool down, bool Up, bool Left)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->transform->setLocalPosition(vec2{ x,y });
		e->collider = colliders.push();
		e->transform->setLocalScale(vec2{24,24});
		e->collider->trigger = true;
		e->enemyDirector = enemyDirectors.push();
		e->enemyDirector->down = down;
		e->enemyDirector->right = right;
		e->enemyDirector->Up = Up;
		e->enemyDirector->Left = Left;

		return e;
	}

	ObjectPool<Entity>::iterator spawnEnemy(float x, float y, unsigned sprite, int health, float Speed)
	{
		auto e = entities.push();
		e->enemy = enemys.push();
		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->enemyDirector = enemyDirectors.push();

		e->rigidbody->velocity = vec2{Speed,0};
		
		e->transform->setLocalPosition(vec2{ x,y });
		e->transform->setLocalScale(vec2{ 48,48 });
		e->enemy->health = health;
		//e->enemy->EnemyNum = Enum;
		e->sprite->sprite_id = sprite;

		return e;
	}
	ObjectPool<Entity>::iterator spawnEnd(float x, float y)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->collider = colliders.push();
		e->endBox = EndBoxs.push();

		e->transform->setLocalPosition(vec2{ x,y });
		e->transform->setLocalScale(vec2{ 48,48 });
		e->collider->trigger = true;

		return e;
	}
	

	ObjectPool<Entity>::iterator spawnAsteroid(unsigned sprite)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();

		e->transform->setLocalScale(vec2{ 48,48 });

		e->transform->setGlobalPosition(vec2::fromAngle(randRange(0, 360)*DEG2RAD)*(rand01() * 200 + 64));

		e->rigidbody->addSpin(rand01()*12-6);

		e->sprite->sprite_id = sprite;

		return e;
	}

	//ObjectPool<Entity>::iterator spawnTurret(float x, float y, unsigned sprite, float Tnum)
	//{
	//	auto e = entities.push();
	//	e->transform = transforms.push();
	//	e->sprite = sprites.push();

	//	e->transform->setLocalPosition(vec2{ x,y });
	//	e->transform->setLocalScale(vec2{ 48,48 });
	//	
	//	e->sprite->sprite_id = sprite;

	//	return e;
	//}

	ObjectPool<Entity>::iterator spawnTurretNode(float x, float y, unsigned sprite, int Tnum)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->collider = colliders.push(Collider(3.f));
		e->turretRotation = turretRotations.push();
		e->sprite = sprites.push();
		e->controller = controllers.push();
		e->controller->TurretNum = Tnum;
		e->sprite->sprite_id = sprite;
		e->transform->setLocalPosition(vec2{x,y});
		e->transform->setLocalScale(vec2{ 48,48 });
		e->sprite->angle = -1.57f;
		e->collider->trigger = true;
		
		/*
		
sfw::drawLine(x, y, x + 50, y, BLACK);
		sfw::drawLine(x, y, x, y + 50, BLACK);
		sfw::drawLine(x + 50, y, x + 50, y + 50, BLACK);
		sfw::drawLine(x, y + 50, x + 50, y + 50, BLACK);*/
		return e;
	}
};


