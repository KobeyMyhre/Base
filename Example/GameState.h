#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"
#include "WaveManager.h"

/*
	The gamestate represents a discrete container of all that is 
	necessary to drive the game experience.

	A factory object is used to manage the creation and deletion of
	objects in the simulation.

	The game state updates the entities within the factory using
	a series of 'systems.'
*/

class GameState : public BaseState
{
	Factory factory;
	WaveManager Wave;
	unsigned spr_space,spr_enemy, spr_font,spr_TurretNode, spr_bullet;
	ObjectPool<Entity>::iterator currentCamera;
	

public:
	virtual void init()
	{
		
		spr_space = sfw::loadTextureMap("../res/Map.png");
		spr_enemy = sfw::loadTextureMap("../res/Enemy.png");
		spr_TurretNode = sfw::loadTextureMap("../res/dickasshole.png");
		spr_bullet = sfw::loadTextureMap("../res/Bullets.png");
		
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
	}

	virtual void play()
	{
		
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->camera->offset = vec2{ 400,300 };
		//currentCamera->camera->scale = vec2{2,2};

		// call some spawning functions!
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);
		factory.spawnHUD(spr_font, Wave);

		factory.spawnTurretNode(-70, -10,spr_TurretNode,0);
		factory.spawnTurretNode(-150, 120, spr_TurretNode, 1);
		factory.spawnTurretNode(-220, 0, spr_TurretNode, 2);
		factory.spawnTurretNode(-70, 120, spr_TurretNode, 3);
		

		//factory.spawnEnemy(-500, 50, spr_enemy);
		factory.spawnEnd(300, -40);
		factory.spawnDir(50, 50, false, true);
		factory.spawnDir(25, -75, true, false);
		//factory.spawnTurretNode(-50, -10, spr_TurretNode);

		//factory.spawnPlayer(spr_ship, spr_font);
		//factory.spawnAsteroid(spr_roid);
		//factory.spawnAsteroid(spr_roid);
		//factory.spawnAsteroid(spr_roid);
		//factory.spawnAsteroid(spr_roid);
	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()
	{
		
		float dt = sfw::getDeltaTime();
		
		Wave.SpawnTimer -= dt;
		if(Wave.WaveStarted == true)
		{
			if (Wave.SpawnTimer <= 0 && Wave.EnemyCount >=0)
			{
				factory.spawnEnemy(-500, 50, spr_enemy, (Wave.Wave * 20 + 80));
				Wave.EnemyCount--;
				Wave.SpawnTimer = Wave.SpawnTime;
				
			}
		}
		

		Wave.Generate();
		Wave.StartWave();
		// maybe spawn some asteroids here.

		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference
			
			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			if (e.enemy && e.enemy->IsDead(Wave))
			{
				del = true;
			}

			if (e.controller)
			{
				e.controller->TurretUpgrade(Wave);
			}
			

			if (e.text && e.hUD)
			{
				e.hUD->update(*e.text, Wave);
				//e.hUD->updateTurretText(*e.text, &e.controller);
			}

			/*if (e.transform && e.rigidbody && e.sprite && e.collider)
			{
				e.rigidbody->Pathing(&e.transform, dt);
			}*/

			if (e.transform && e.sprite && e.controller)
			{
				e.controller->NodeOperator(&e.transform, &e.sprite);
				e.controller->TurretPlacement(&e.transform, &e.sprite, Wave);

				//if (e.controller->SpawnTurret)
				//{
				//	for each(auto &e in factory)
				//		if(e.controller->TurretNum /*&& turret node hasn't been used yet*/)
				//		{
				//			e.controller.activate();
				//			//e.transform->getGlobalPosition();
				//			//factory.spawnTurret();
				//			break;
				//		}
				//	
				//}
			}
				


			// controller update
			if (e.transform && e.controller)
			{
				//e.controller->poll(Wave);
				if (e.controller->shotRequest) // controller requested a bullet fire
				{
		
					factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition()  + e.transform->getGlobalUp()*48,
											vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
				}
			}
			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
		}


		// Physics system!
		// You'll want to extend this with custom collision responses

		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);

						if (it->collider->trigger || bit->collider->trigger)
						{
							if (it->enemyDirector && bit->rigidbody && bit->enemyDirector)
								it->enemyDirector->direct(&bit->rigidbody);
							if (bit->enemyDirector && it->rigidbody && it->enemyDirector)
								bit->enemyDirector->direct(&it->rigidbody);

							if (it->controller && bit->rigidbody && !bit->lifetime)
							{
								it->turretRotation->FaceEnemy(&it->transform, &it->controller, &bit->transform,dt);
							}
							if (bit->controller && it->rigidbody && !it->lifetime)
							{
								bit->turretRotation->FaceEnemy(&bit->transform, &bit->controller, &it->transform,dt);
							}


							if (it->endBox && bit->enemy)
							{
								it->endBox->end(Wave, &bit->enemy);
							}

							//base::EnemyDirDownResolution(cd, &it->transform, &it->rigidbody);
							//base::EnemyDirRightResolution(cd, &it->transform, &it->rigidbody);
						}

						else
						{
							// if true, get the penetration and normal from the convex hulls
							//auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
							// if there was a collision,
							if (cd.result())
							{
								if (it->rigidbody && bit->enemy && !it->enemy )
								{
									bit->enemy->TakeDamge();
								}
								if (bit->rigidbody && it->enemy && !bit->enemy)
								{
									it->enemy->TakeDamge();
								}

								
								// condition for dynamic resolution
								//if (it->rigidbody && bit->rigidbody)
								//	base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
								//// condition for static resolution
								//else if (it->rigidbody && !bit->rigidbody)							
								//	base::StaticResolution(cd, &it->transform, &it->rigidbody);					
							}
						}
					}
				}

	}


	virtual void draw()	
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
			if (e.transform && e.sprite)
			{
				e.sprite->draw(&e.transform, cam);
			}
		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);


#ifdef _DEBUG
		for each(auto &e in factory)
			if (e.transform)
				e.transform->draw(cam);

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);
#endif
	}
};