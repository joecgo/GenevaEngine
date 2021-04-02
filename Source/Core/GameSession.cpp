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
#include <Gameplay/CharacterStates.hpp>

namespace GenevaEngine
{
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
		// define these for each entity
		b2BodyDef bodyDef;
		b2FixtureDef fixtureDef;
		b2PolygonShape shapeDef;
		MultiBody* multiBody = nullptr;

		// create ground
		bodyDef.position.Set(0.0f, -10.0f);
		shapeDef.SetAsBox(50.0f, 10.0f);
		fixtureDef.density = 0; // 0 density is static
		multiBody = new MultiBody();
		multiBody->AddBody(bodyDef, true);
		multiBody->SetPolygonShape(shapeDef, fixtureDef);
		multiBody->SetWorld(GetPhysics()->GetWorld());
		Entity* ground = new Entity(this, "ground");
		ground->AddMultiBody(multiBody);
		ground->SetRenderColor(2);

		// create dynamic boxes
		Entity* box = nullptr;
		for (size_t i = 0; i < 50; i++)
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(0.0f, (float)i * 5.0f);
			shapeDef.SetAsBox(1.0f, 1.0f);
			fixtureDef.density = 0.01f; // super low density for "foam-like" behavior
			fixtureDef.friction = 0.3f;
			multiBody = new MultiBody();
			multiBody->AddBody(bodyDef, true);
			multiBody->SetPolygonShape(shapeDef, fixtureDef);
			multiBody->SetWorld(GetPhysics()->GetWorld());
			box = new Entity(this, "box");
			box->AddMultiBody(multiBody);
			box->SetRenderColor(3);
		}

		// create hero. It is a bigger box! so heroic...
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(15.0f, 5.0f);
		shapeDef.SetAsBox(3.0f, 3.0f);
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 5.0f;
		multiBody = new MultiBody();
		multiBody->AddBody(bodyDef, true);
		multiBody->SetPolygonShape(shapeDef, fixtureDef);
		multiBody->SetWorld(GetPhysics()->GetWorld());
		Entity* hero = new Entity(this, "hero");
		hero->AddMultiBody(multiBody);
		hero->SetRenderColor(5);
		m_input->GetPlayerController()->Possess(hero);
		hero->AddFSM(new Grounded());
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