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
  * \file GameSession.hpp
  * \author Joe Goldman
  * \brief GameSession class declaration. GameSession contains the control flow and
  * initialization of all the systems.
  *
  */

#pragma once

#define MS_PER_FRAME 0.033333333 // 60fps: 0.01666666

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // glfwWindowShouldClose

#include <vector> // vector
#include <windows.h> // Sleep

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	class Entity;
	class ASystem;
	class Graphics;
	class Input;

	/*!
	 *  GameSession contains the control flow and initialization of all the systems.
	 */
	class GameSession
	{
	public:
		GameSession();

		// clock stuff
		bool isRunning = true; // flag tells main when to return

		// system references
		Graphics* graphics = nullptr;
		Input* input = nullptr;

		void AddSystem(ASystem* system);
		void AddEntity(Entity* entity);

	private:
		// system and entity references
		std::vector<ASystem*> systems;
		std::vector<Entity*> entities;

		void Start();
		void GameLoop();
		void End();
		void CreateEntities();
	};
}