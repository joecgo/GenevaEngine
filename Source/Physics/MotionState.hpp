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
  * \file MotionState.hpp
  * \author Joe Goldman
  * \brief MotionState class declaration
  *
  */

#pragma once

#include <glm/gtc/matrix_transform.hpp> // vec3

namespace GenevaEngine
{
	/*!
	 *  \brief The physical state of an object in motion.
	 */
	struct MotionState
	{
		glm::vec3 velocity;
		glm::vec3 position;

		MotionState(glm::vec3 pos = glm::vec3(), glm::vec3 vel = glm::vec3());
		MotionState operator+(const MotionState& other);
		MotionState operator*(float scalar);
		MotionState& operator=(const MotionState& other);
	};
}