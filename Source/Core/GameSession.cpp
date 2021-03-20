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
	// define static variables
	float GameSession::deltaTime_ = 0.0f;
	float GameSession::lastFrame_ = 0.0f;

	/*!
	 *  Constructor. Initialize and start core systems
	 */
	GameSession::GameSession()
	{
		new Input();
		new Graphics();
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
		for (ASystem* system : systems_)
			system->Start();

		// start entities
		for (Entity* entity : entities_)
			entity->Start();

		GameLoop();
	}

	/*!
	 *  Main game loop for updating systems and entities
	 */
	void GameSession::GameLoop()
	{
		while (!glfwWindowShouldClose(Graphics::window))
		{
			// TODO?: move this method to a time or physics system
			UpdateTime();

			// update systems
			for (ASystem* system : systems_)
				system->Update();

			// update entities
			for (Entity* entity : entities_)
				entity->Update();
		}

		End();
	}

	/*!
	 *  Ends the game session. deletes systems from memory.
	 */
	void GameSession::End()
	{
		// end entities
		for (Entity* entity : entities_)
			entity->End();

		// end systems
		for (ASystem* system : systems_)
			system->End();

		// delete entities
		for (Entity* entity : entities_)
			delete entity;

		// delete systems
		for (ASystem* system : systems_)
			delete system;

		// public flag for closing down the program in main()
		isRunning_ = false;
	}

	void GameSession::UpdateTime()
	{
		// per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime_ = currentFrame - lastFrame_;
		lastFrame_ = currentFrame;
	}

	void GameSession::AddEntity(Entity* entity)
	{
		entities_.push_back(entity);
	}

	void GameSession::AddSystem(ASystem* system)
	{
		systems_.push_back(system);
	}
}