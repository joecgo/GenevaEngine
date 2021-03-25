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
  * \file MotionState.cpp
  * \author Joe Goldman
  * \brief MotionState class definition
  *
  **/

#include <Physics/MotionState.hpp>

namespace GenevaEngine
{
	MotionState::MotionState(glm::vec3 pos, glm::vec3 vel) : position(pos), velocity(vel)
	{
	}

	MotionState MotionState::operator+(const MotionState& other)
	{
		return MotionState(position + other.position, velocity + other.velocity);
	}

	MotionState MotionState::operator*(float scalar)
	{
		return MotionState(position * scalar, velocity * scalar);
	}

	MotionState& MotionState::operator=(const MotionState& other)
	{
		position = other.position;
		velocity = other.velocity;
		return *this;
	}
}