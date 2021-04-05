/****************************************************************************
 * Copyright (C) 2021 by Joe Goldman	                                    *
 *                                                                          *
 * This file is part of GenevaEngine.                                       *
 *                                                                          *
 *   GenevaEngine is a custom C++ engine built for the purposes of 			*
 *	 learning and fun. You can reach me at joecgo@gmail.com. 				*
 *                                                                          *
 ****************************************************************************/

 /**
  * \file GameSession.cpp
  * \author Joe Goldman
  * \brief GameSession class definition. The GameSession creates, stores, starts, updates, and
  * ends all game systems and entities.
  *
  **/

#include <Core/GameCommon.hpp>
#include <Gameplay/SingleShapeBehavior.hpp>
#include <Physics/Construct.hpp>
#include <Physics/SingleShape.hpp>

namespace GenevaEngine
{
	// declare static variables
	double GameSession::FrameTime = 0.01;

	/*!
	 *  Constructor. Initialize and start core systems
	 */
	GameSession::GameSession()
	{
		m_physics = new Physics(this);
		m_input = new Input(this);
		m_graphics = new Graphics(this);

		Start();
	}

	Physics* GameSession::GetPhysics()
	{
		return m_physics;
	}

	Input* GameSession::GetInput()
	{
		return m_input;
	}

	Graphics* GameSession::GetGraphics()
	{
		return m_graphics;
	}

	/*!
	 *  Temporary way to create the entities for testing stuff out
	 *  TODO: create entities from a scene file instead of like this
	 */
	void GameSession::CreateEntities()
	{
		// get world from physics system
		b2World* world = GetPhysics()->GetWorld();

		// create construct
		SingleShape* ground = new SingleShape(world);
		ground->BodyDef.position.Set(0.0f, -10.0f);
		ground->BodyDef.type = b2_staticBody;
		ground->FixtureDef.density = 0.0f;
		ground->Shape.SetAsBox(50.0f, 10.0f);
		// create entity
		Entity* ground_entity = new Entity(this, "box");
		ground_entity->AddConstruct(ground);
		ground_entity->SetRenderColor(2);

		// create construct
		SingleShape* hero = new SingleShape(world);
		hero->BodyDef.position.Set(5.0f, 5.0f);
		hero->BodyDef.type = b2_dynamicBody;
		hero->FixtureDef.density = 1.0f;
		hero->FixtureDef.friction = 5.0f;
		hero->Shape.SetAsBox(3.0f, 3.0f);
		hero->EnableBehavior();
		// create entity
		Entity* hero_entity = new Entity(this, "hero");
		hero_entity->AddConstruct(hero);
		hero_entity->SetRenderColor(5);
		GetInput()->GetPlayerController()->Possess(hero_entity);

		// create dynamic boxes
		for (size_t i = 0; i < 50; i++)
		{
			// create  construct
			SingleShape* box = new SingleShape(world);
			box->BodyDef.position.Set(0, i * 5.0f);
			box->BodyDef.type = b2_dynamicBody;
			box->FixtureDef.density = 0.01f;
			box->FixtureDef.friction = 0.3f;
			box->Shape.SetAsBox(1.0f, 1.0f);
			// create entity
			Entity* box_entity = new Entity(this, "box");
			box_entity->AddConstruct(box);
			box_entity->SetRenderColor(3);
		}
	}

	/*!
	 *  Starts the core systems and enter game loop
	 */
	void GameSession::Start()
	{
		// start systems
		m_graphics->Start();
		m_physics->Start();
		m_input->Start();

		CreateEntities();

		// start entities
		for (Entity* entity : entities)
			entity->Start();

		GameLoop();
	}

	/*!
	 *  Main game loop for updating systems and entities
	 */
	void GameSession::GameLoop()
	{
		// initialize time variables
		float dt = 0.01f;
		double currentTime = Time();
		double accumulator = 0.0;

		while (!glfwWindowShouldClose(m_graphics->m_window))
		{
			// time calculations
			double newTime = Time();
			FrameTime = newTime - currentTime;
			if (FrameTime > 0.25)
				FrameTime = 0.25;
			currentTime = newTime;
			accumulator += FrameTime;

			//// -----------------------------------------------------
			/// Game Loop Execution
			// -------------------------------------------------------

			m_input->Update(FrameTime); 					// Input

			// fixed update loop
			while (accumulator >= dt)
			{
				m_physics->Update(dt);					// Physics (fixed update)
				for (Entity* entity : entities)			// Game Logic (fixed update)
					entity->FixedUpdate(dt);

				accumulator -= dt;
			}

			const double alpha = accumulator / dt;
			for (Entity* entity : entities)				// Game Logic
				entity->Update(FrameTime);
			m_graphics->Update(FrameTime); 				// Render
			while (Paused) { newTime = Time(); };		// Pausing

			//// -----------------------------------------------------
			/// Game Loop Execution
			// -------------------------------------------------------

			currentTime = newTime;
		}

		End();
	}

	/*!
	 *  Ends the game session. deletes systems from memory.
	 */
	void GameSession::End()
	{
		// end entities
		for (Entity* entity : entities)
			entity->End();

		// end systems
		for (System* system : systems)
			system->End();

		// delete entities
		for (Entity* entity : entities)
			delete entity;

		// delete systems
		for (System* system : systems)
			delete system;

		// public flag for closing down the program in main()
		IsRunning = false;
	}

	/*!
	 *  Adds an entity to GameSession's array of entity
	 *
	 *      \param [in,out] entity
	 */
	void GameSession::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	/*!
	 *  Adds a System to GameSession's array of Systems
	 *
	 *      \param [in,out] system
	 */
	void GameSession::AddSystem(System* system)
	{
		systems.push_back(system);
	}

	/*!
	 *  returns the time in seconds
	 *
	 *      \return returns the time in seconds
	 */
	double GameSession::Time()
	{
		return glfwGetTime();
	}

	b2World* GameSession::GetWorld()
	{
		return &(m_physics->m_world);
	}
}