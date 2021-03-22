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
  * \file Physics.hpp
  * \author Joe Goldman
  * \brief Physics system class declaration
  *
  */

#pragma once

#include <glm/gtc/matrix_transform.hpp> // vec3

#include <vector> // vector

#include <Core/GameCommon.hpp>

namespace GenevaEngine
{
	/*!
	 *  \brief The physical state of an object in motion.
	 */
	struct MotionState
	{
		MotionState(glm::vec3 pos, glm::vec3 vel, glm::vec3 acc) :
			position(pos), velocity(vel), acceleration(acc) {}
		glm::vec3 acceleration;
		glm::vec3 velocity;
		glm::vec3 position;
	};

	/*!
	 *  \brief Physics system
	 */
	class Physics : public ASystem
	{
	public:

	private:
		std::vector<MotionState*> current_state;
		std::vector<MotionState*> previous_state;

		void InterpolateMotion(double alpha);

		// inherited members, methods, and constructors
		using ASystem::ASystem;
		void Start();
		void Update(double dt);
		void End();
		friend class GameSession;
	};
}