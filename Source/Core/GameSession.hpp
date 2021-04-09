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

#include <Physics/Box2d.hpp>
#include <Physics/Physics.hpp>
#include <Graphics/Graphics.hpp>
#include <Input/Input.hpp>

#include <vector> // vector

namespace GenevaEngine
{
	class Entity;
	class System;

	/*!
	 *  \brief GameSession contains the control flow and initialization of all the systems.
	 */
	class GameSession
	{
	public:
		GameSession();

		// Attributes
		static double FrameTime;
		bool Paused = false;
		bool IsRunning = true; // flag tells main when to return

		// getters
		Physics* GetPhysics();
		Input* GetInput();
		Graphics* GetGraphics();

		// Game loop helper
		bool WindowIsClosed();

		// systems and entities add themselves to gamesession on consturction
		void AddSystem(System* system);
		void AddEntity(Entity* entity);

		// box2d
		b2World* GetWorld();


	private:
		// system references
		Physics* m_physics = nullptr;
		Graphics* m_graphics = nullptr;
		Input* m_input = nullptr;		

		// system, entity references
		std::vector<System*> m_systems;
		std::vector<Entity*> m_entities;

		double Time();
		void Start();
		void GameLoop();
		void End();

		friend Graphics;
	};
}