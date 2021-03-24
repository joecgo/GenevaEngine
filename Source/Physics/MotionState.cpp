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
	MotionState& MotionState::operator+(const MotionState& other)
	{
		position += other.position;
		velocity += other.velocity;
		return *this;
	}

	MotionState& MotionState::operator*(float scalar)
	{
		position *= scalar;
		velocity *= scalar;
		return *this;
	}

	MotionState& MotionState::operator=(const MotionState& other)
	{
		position = other.position;
		velocity = other.velocity;
		return *this;
	}
}