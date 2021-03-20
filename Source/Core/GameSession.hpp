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
#include <Core/GameCommon.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>

#include <iostream> // cout, endl

#include <Graphics/Shader.hpp>
#include <Graphics/Camera.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Model.hpp>
#include <Graphics/Color.hpp>
#include <vector> // vector

namespace GenevaEngine
{
	class Entity;
	class ASystem;

	/*!
	 *  GameSession contains the control flow and initialization of all the systems.
	 */
	class GameSession
	{
	public:
		GameSession();

		bool IsRunning() { return isRunning_; }
		static float GetDeltaTime() { return deltaTime_; }
		void AddSystem(ASystem* system);
		void AddEntity(Entity* entity);

	private:
		// TODO?: Move time-related stuff to its own system
		static float deltaTime_; // time between current frame and last frame
		static float lastFrame_;

		bool isRunning_ = true;

		std::vector<ASystem*> systems_;
		std::vector<Entity*> entities_;

		void CreateEntities();
		void Start();
		void GameLoop();
		void End();
		void UpdateTime();
	};
}