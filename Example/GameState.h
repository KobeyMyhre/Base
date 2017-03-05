#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"
#include "WaveManager.h"
#include "MenuState.h"

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
	unsigned spr_space,spr_enemy, spr_font,spr_TurretNode, spr_bullet, spr_UpgradeBullet;
	ObjectPool<Entity>::iterator currentCamera;
	

public:
	virtual void init()
	{
		
		spr_space = sfw::loadTextureMap("../res/BetterMap.png");
		spr_enemy = sfw::loadTextureMap("../res/Enemy.png");
		spr_TurretNode = sfw::loadTextureMap("../res/TurretNode.png");
		spr_bullet = sfw::loadTextureMap("../res/Bullets.png");
		spr_UpgradeBullet = sfw::loadTextureMap("../res/UpgradeBullet.png");
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

		factory.spawnTurretNode(-250, 175, spr_TurretNode, 0);
		factory.spawnTurretNode(-145, 170, spr_TurretNode, 1);
		factory.spawnTurretNode(-10, 175, spr_TurretNode, 2);

		factory.spawnTurretNode(130, 175, spr_TurretNode, 3);
		
		factory.spawnTurretNode(-70, 60, spr_TurretNode, 4);

		factory.spawnTurretNode(10, 60, spr_TurretNode, 5);
		factory.spawnTurretNode(-10, -50, spr_TurretNode, 6);
		factory.spawnTurretNode(40, -50, spr_TurretNode, 7);
		factory.spawnTurretNode(-10, -150, spr_TurretNode, 8);
		factory.spawnTurretNode(130, -150, spr_TurretNode, 9);
		factory.spawnTurretNode(250, -150, spr_TurretNode, 10);

		
		
		
		//factory.spawnTurretNode(250, -150, spr_TurretNode, 11);
		
		

		//factory.spawnEnemy(-500, 50, spr_enemy);
		factory.spawnEnd(370, -210);

		//Down
		factory.spawnDir(-170, 230, false, true,false,false);
		factory.spawnDir(100, 230, false, true, false, false);
		factory.spawnDir(-105, 0, false, true, false, false);
		factory.spawnDir(230, -100, false, true, false, false);
		//Right
		factory.spawnDir(-200, 90, true, false,false,false);
		factory.spawnDir(-100, 250, true, false, false, false);
		factory.spawnDir(-105, -240, true, false, false, false);
		factory.spawnDir(90, -80, true, false, false, false);
		factory.spawnDir(190, -240, true, false, false, false);
		//Up
		factory.spawnDir(-40, 90, false, false, true, false);
		factory.spawnDir(105, -240, false, false, true, false);
		//Left
		factory.spawnDir(100, -30, false, false, false, true);


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
	virtual size_t next() const 
	{
		if (Wave.Health <= 0)
		{
			return (size_t)Enter_Depart;
		}
		else return (size_t)AGame;
	}


	// update loop, where 'systems' exist
	virtual void step()
	{
		
		float dt = sfw::getDeltaTime();
		
		Wave.SpawnTimer -= dt;
		
		if(Wave.WaveStarted == true)
		{
			if (Wave.SpawnTimer <= 0 && Wave.EnemyCount >=0)
			{
				factory.spawnEnemy(-500, 220, spr_enemy, (Wave.Wave * 2 + 1), Wave.Wave *5.f + 50);
				Wave.EnemyCount--;
				Wave.SpawnTimer = Wave.SpawnTime;
				
			}
		}
		
		

		Wave.Generate(dt);
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

			if (e.enemy)
			{
				e.enemy->UpdateCOLOR(&e.sprite,dt);
			}

			if (e.enemyDirector )
			{
				e.enemyDirector->speed = (Wave.Wave *5.f + 50);
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
				e.controller->NodeOperator(&e.transform, &e.sprite,dt);
				e.controller->TurretPlacement(&e.transform, &e.sprite, Wave,dt);

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
				if (e.controller->shotRequest == true) // controller requested a bullet fire
				{
					e.controller->shotRequest = false;
					if (e.controller->UpgradeTurret)
					{
						factory.spawnBullet(spr_UpgradeBullet, e.transform->getGlobalPosition() + e.transform->getGlobalUp() * 48,
							vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
						
					}
					else
					{
						factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition() + e.transform->getGlobalUp() * 48,
							vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
						
					}
					
					
				}
			}
			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}

			if (e.turretRotation)
				e.turretRotation->m_dist = 34534543;
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

					/*		base::EnemyDirDownResolution(cd, &it->transform, &it->rigidbody);
							base::EnemyDirRightResolution(cd, &it->transform, &it->rigidbody);*/
						}
						

						else
						{
							// if true, get the penetration and normal from the convex hulls
							//auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
							// if there was a collision,
							//
							// KEIL LOOOK OVER HERE!!!!!!!
							//
							if (cd.result())
							{
								if (it->rigidbody && bit->enemy && !it->enemy )
								{
									bit->enemy->TakeDamge(&bit->sprite, dt, &it->lifetime);
									//it->onFree();
									//it.free();
								}
								if (bit->rigidbody && it->enemy && !bit->enemy)
								{
									it->enemy->TakeDamge(&it->sprite, dt, &bit->lifetime);
									
									//bit->onFree();
									//bit.free();
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
	/*	for each(auto &e in factory)
			if (e.transform)
				e.transform->draw(cam);

		for each(auto &e in factory)
			if (e.transform && e.collider)
				e.collider->draw(&e.transform, cam);

		for each(auto &e in factory)
			if (e.transform && e.rigidbody)
				e.rigidbody->draw(&e.transform, cam);*/
#endif
	}
};