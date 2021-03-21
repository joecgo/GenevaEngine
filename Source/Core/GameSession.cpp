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
		new Entity(this, glm::vec3(5.0f, -2.0f, 0.0f), glm::vec3(5.0f, 5.0f, 5.0f),
			"kevin", "greyShader");
		new Entity(this, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			"backpack", "textureShader");
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
		while (!glfwWindowShouldClose(graphics->window))
		{
			// Delta time updated
			UpdateTime();

			// Input system updated
			input->Update();

			// Entities updated
			for (Entity* entity : entities)
				entity->Update();

			// Graphics system updated
			graphics->Update();
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
	 *  Time tick, called once per frame
	 */
	void GameSession::UpdateTime()
	{
		// per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
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
}