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

#include <glad/glad.h> // extension of GLFW
#include <GLFW/glfw3.h> // glfwWindowShouldClose

#include <vector> // vector

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	class Entity;
	class ASystem;
	class Graphics;
	class Input;
	class Physics;

	/*!
	 *  GameSession contains the control flow and initialization of all the systems.
	 */
	class GameSession
	{
	public:
		GameSession();

		bool paused = false;
		bool isRunning = true; // flag tells main when to return

		// system references
		Physics* physics = nullptr;
		Graphics* graphics = nullptr;
		Input* input = nullptr;
		Entity* kevin = nullptr; // testing jump

		void AddSystem(ASystem* system);
		void AddEntity(Entity* entity);

		// system, entity references
		std::vector<ASystem*> systems;
		std::vector<Entity*> entities;

	private:
		double Time();
		void Start();
		void GameLoop();
		void End();
		void CreateEntities();
	};
}