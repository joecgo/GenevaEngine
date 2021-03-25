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
		kevin = new Entity(this,
			glm::vec3(0.0f, 13.0f, 0.0f),
			glm::vec3(5.0f, 5.0f, 5.0f),
			"kevin", "TextureShader");
		kevin->rect_collider = glm::vec2(1.0f, 6.0f);
		kevin->collider_offset = glm::vec3(0, 3.5f, 0);

		Entity* backpack = new Entity(this,
			glm::vec3(0.0f, 45.0f, 0.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			"backpack", "TextureShader");
		backpack->rect_collider = glm::vec2(1.0f, 4.0f);
		backpack->collider_offset = glm::vec3(0, 1.5f, 0);

		Entity* floor = new Entity(this,
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(30.0f, 1.0f, 1.0f),
			"cube", "SingleColorShader");
		floor->stationary = true;
		floor->rect_collider = glm::vec2(30.0f, 1.0f);
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
		double cooldown = 0;
		int KeyState_SPACE = 0; // for kevin testing

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

			// test kevin's reflexes
			if (KeyState_SPACE == 0 && glfwGetKey(graphics->window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				kevin->impulse = glm::vec3(0.0f, 300.0f, 0.0f);
				KeyState_SPACE = 1;
				std::cout << "JUMP" << std::endl;
				cooldown = currentTime + 1.0;
			}
			if (KeyState_SPACE == 1 && cooldown < currentTime)
				KeyState_SPACE = 0;

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
			physics->InterpolateMotion((float)alpha);	// Physics (between time steps)
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
}