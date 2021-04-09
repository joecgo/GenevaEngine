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
  * \file Physics.cpp
  * \author Joe Goldman
  * \brief Physics system class definition
  *
  **/

#include <Physics/Physics.hpp>

namespace GenevaEngine
{
	/*!
	 *  Starts the physics system, before game loop.
	 */
	void Physics::Start()
	{
	}

	/*!
	 *  Ends the physics system. when game loop is done
	 */
	void Physics::End()
	{
	}

	/*!
	 *  Updates the physics system
	 *
	 *      \param [in] dt
	 */
	void Physics::Update(double dt)
	{
		m_world.Step((float)dt, k_velocity_iterations, k_position_iterations);
	}

	/*!
	 *  Returns the box2d world
	 *
	 *      \return The world.
	 */
	b2World* Physics::GetWorld()
	{
		return &(m_world);
	}
}