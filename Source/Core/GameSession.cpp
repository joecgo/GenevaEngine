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
  * \brief GameSession class definition. A GameSession contains the control flow and
  * initialization of all the systems.
  *
  **/

#include <Core/GameSession.hpp>

namespace GenevaEngine
{
	/*!
	 *  Constructor. Initialize core systems
	 */
	GameSession::GameSession()
	{
		deltaTime_ = 0.0f;
		lastFrame_ = 0.0f;

		systems_.push_back(new Input());
		systems_.push_back(new Graphics());

		Start();
		GameLoop();
	}

	/*!
	 *  Starts the game session.
	 */
	void GameSession::Start()
	{
		for (ASystem* system : systems_)
			system->Start();
	}

	/*!
	 *  Main game loop for updating systems
	 */
	void GameSession::GameLoop()
	{
		while (!glfwWindowShouldClose(Graphics::window))
		{
			// per-frame time logic
			// --------------------
			float currentFrame = (float)glfwGetTime();
			deltaTime_ = currentFrame - lastFrame_;
			lastFrame_ = currentFrame;

			for (ASystem* system : systems_)
				system->Update();
		}

		End();
	}

	void GameSession::End()
	{
		for (ASystem* system : systems_)
			system->End();

		for (ASystem* system : systems_)
			delete system;

		isRunning_ = false;
	}
}