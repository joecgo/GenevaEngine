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

#include <Core/GameSession.hpp>
#include <Levels/IncludeAllLevels.hpp>
#include <Graphics/Graphics.hpp>
#include <Physics/Physics.hpp>
#include <Input/Input.hpp>
#include <Core/Entity.hpp>

namespace GenevaEngine
{
	// declare static variables
	double GameSession::FrameTime = 0.01;
	float GameSession::TimeStep = 0.01f;

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
	 *  Starts the core systems and enter game loop
	 */
	void GameSession::Start()
	{
		// start systems
		m_graphics->Start();
		m_physics->Start();
		m_input->Start();

		// Load level
		// TODO: level loading should be done at run-time with a config file
		HardBoxBehaviorDemo::Load(*this);
		//WebDemo::Load(*this);

		// start entities
		for (Entity* entity : m_entities)
			entity->Start();

		GameLoop();
	}

	/*!
	 *  Main game loop for updating systems and entities
	 */
	void GameSession::GameLoop()
	{
		// initialize time variables
		double currentTime = Time();
		double accumulator = 0.0;

		while (!WindowIsClosed())
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

			m_input->Update(FrameTime); 				// Input

			// fixed time-step update loop
			while (accumulator >= TimeStep)
			{
				m_physics->Update(TimeStep);			// Physics (fixed update)
				for (Entity* entity : m_entities)		// Entities and their Constructs
					entity->FixedUpdate(TimeStep);

				accumulator -= TimeStep;
			}

			// render update
			const double alpha = accumulator / TimeStep;
			for (Entity* entity : m_entities)			// Entities and their Constructs
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
		for (Entity* entity : m_entities)
			entity->End();

		// end systems
		for (System* system : m_systems)
			system->End();

		// delete entities
		for (Entity* entity : m_entities)
			delete entity;

		// delete systems
		for (System* system : m_systems)
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
		m_entities.push_back(entity);
	}

	/*!
	 *  Adds a System to GameSession's array of Systems
	 *
	 *      \param [in,out] system
	 */
	void GameSession::AddSystem(System* system)
	{
		m_systems.push_back(system);
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

	bool GameSession::WindowIsClosed()
	{
		return glfwWindowShouldClose(m_graphics->m_window);
	}
}