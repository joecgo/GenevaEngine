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

namespace GenevaEngine
{
	/*!
	 *  Constructor. Initialize and start core systems
	 */
	GameSession::GameSession()
	{
		physics = new Physics(this);
		input = new Input(this);
		graphics = new Graphics(this);
		CreateEntities();
		Start();
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

		// create ground
		bodyDef.position.Set(0.0f, -10.0f);
		shapeDef.SetAsBox(50.0f, 10.0f);
		fixtureDef.density = 0; // 0 density is static
		new Entity(this, bodyDef, fixtureDef, shapeDef, "ground");

		// create dynamic boxes
		for (size_t i = 0; i < 100; i++)
		{
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(0.0f, (float)i * 5.0f);
			shapeDef.SetAsBox(1.0f, 1.0f);
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			new Entity(this, bodyDef, fixtureDef, shapeDef, "box");
		}
	}

	/*!
	 *  Starts the core systems and enter game loop
	 */
	void GameSession::Start()
	{
		// start systems
		for (ASystem* system : systems)
			system->Start();

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
		double dt = 0.01;
		double currentTime = Time();
		double accumulator = 0.0;

		while (!glfwWindowShouldClose(graphics->window))
		{
			// time calculations
			double newTime = Time();
			double frameTime = newTime - currentTime;
			if (frameTime > 0.25)
				frameTime = 0.25;
			currentTime = newTime;
			accumulator += frameTime;

			//// -----------------------------------------------------
			/// Game Loop Execution
			// -------------------------------------------------------

			input->Update(frameTime); 					// Input

			// fixed update loop
			while (accumulator >= dt)
			{
				physics->Update(dt);					// Physics (fixed update)
				for (Entity* entity : entities)			// Game Logic (fixed update)
					entity->FixedUpdate(dt);

				accumulator -= dt;
			}

			const double alpha = accumulator / dt;
			for (Entity* entity : entities)				// Game Logic
				entity->Update(frameTime);
			graphics->Update(frameTime); 				// Render
			while (paused) { newTime = Time(); };		// Pausing

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
		for (ASystem* system : systems)
			system->End();

		// delete entities
		for (Entity* entity : entities)
			delete entity;

		// delete systems
		for (ASystem* system : systems)
			delete system;

		// public flag for closing down the program in main()
		isRunning = false;
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
	void GameSession::AddSystem(ASystem* system)
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
		return &(physics->world);
	}
}