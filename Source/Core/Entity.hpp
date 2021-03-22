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
  * \file Entity.hpp
  * \author Joe Goldman
  * \brief Entity class declaration
  *
  */

#pragma once

#include <glm/glm.hpp> // vec3

#include <string> // string

#include <Graphics/Shader.hpp>
#include <Graphics/Model.hpp>
#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief The physical state of an object in motion.
	 */
	struct MotionState
	{
		glm::vec3 acceleration;
		glm::vec3 velocity;
		glm::vec3 position;
	};

	/*!
	 *  \brief An object that populates the game. Like an actor or game object.
	 */
	class Entity
	{
	public:
		Entity(GameSession* gs, glm::vec3 pos, glm::vec3 scale, string model_name,
			string shader_name = "textureShader");

		// TODO: store these things in components that are attached to the Entity
		// Model Component
		Model* model = nullptr;
		std::string model_name = 0;
		// Render Component
		Shader* shader = nullptr;
		std::string shader_name = 0;
		// Transform Component
		glm::vec3 startPosition = glm::vec3();
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 Position();
		// Physics Component
		bool use_gravity = true;
		float mass = 10.0f;
		glm::vec3 impulse = glm::vec3();
		MotionState interpolated_state;
		MotionState current_state;
		MotionState previous_state;

	private:
		GameSession* gamesession;

		void Start();
		void FixedUpdate(double alpha); // update on fixed time-steps
		void Update(double dt);		 // update on every frame
		void End();

		friend class GameSession;
	};
}